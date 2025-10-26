#include "VCPlugInHeaders.h" // Visual Studio only?

// ---------------------------------------------------------------------------------------
// Interface includes:
#include "IApplication.h"
#include "IControlView.h"
#include "IPanelMgr.h"
#include "IScript.h"
#include "IScriptErrorUtils.h"
#include "IScriptRequestData.h"
#include "IStyleInfo.h"

// ---------------------------------------------------------------------------------------
// General includes:
#include "CAlert.h" // CAlert::InformationAlert(Msg);
#include "keyboarddefs.h"
#include "PMString.h"
#include "StylePanelID.h"
#include "VirtualKey.h"
#include "KBSCModifierDefs.h"

// ---------------------------------------------------------------------------------------
// Project includes:
#include "KESScriptingDefs.h"
#include "KESStyle.h"

// Set keyboard shortcut.
ErrorCode KESStyle::SetKeyboardShortcut(IScriptRequestData* iScriptRequestData, IScript* iScript)
{
	ErrorCode status = kFailure;

	do
	{
		ScriptData scriptData;
		VirtualKey virtualKey_shortCut;

		PMString pMString_key;
		if (iScriptRequestData->ExtractRequestData(p_KESCKey, scriptData) != kSuccess) break;

		if (scriptData.GetPMString(pMString_key) != kSuccess) break;

		if (pMString_key.CharCount() > 1)
		{
			if (pMString_key == "null") virtualKey_shortCut = kVirtualNullKey;
			else if (pMString_key == "F1") virtualKey_shortCut = kFunctionKey1;
			else if (pMString_key == "F2") virtualKey_shortCut = kFunctionKey2;
			else if (pMString_key == "F3") virtualKey_shortCut = kFunctionKey3;
			else if (pMString_key == "F4") virtualKey_shortCut = kFunctionKey4;
			else if (pMString_key == "F5") virtualKey_shortCut = kFunctionKey5;
			else if (pMString_key == "F6") virtualKey_shortCut = kFunctionKey6;
			else if (pMString_key == "F7") virtualKey_shortCut = kFunctionKey7;
			else if (pMString_key == "F8") virtualKey_shortCut = kFunctionKey8;
			else if (pMString_key == "F9") virtualKey_shortCut = kFunctionKey9;
			else if (pMString_key == "F10") virtualKey_shortCut = kFunctionKey10;
			else if (pMString_key == "F11") virtualKey_shortCut = kFunctionKey11;
			else if (pMString_key == "F12") virtualKey_shortCut = kFunctionKey12;
			else if (pMString_key == "Space") virtualKey_shortCut = kVirtualSpaceKey;
			else if (pMString_key == "Up") virtualKey_shortCut = kVirtualUpArrowKey;
			else if (pMString_key == "Down") virtualKey_shortCut = kVirtualDownArrowKey;
			else if (pMString_key == "Right") virtualKey_shortCut = kVirtualRightArrowKey;
			else if (pMString_key == "Left") virtualKey_shortCut = kVirtualLeftArrowKey;
			else if (pMString_key == "Home") virtualKey_shortCut = kVirtualHomeKey;
			else if (pMString_key == "End") virtualKey_shortCut = kVirtualEndKey;
			else if (pMString_key == "PageUp") virtualKey_shortCut = kVirtualPageUpKey;
			else if (pMString_key == "PageDown") virtualKey_shortCut = kVirtualPageDownKey;
			else if (pMString_key == "Clear") virtualKey_shortCut = kVirtualClearKey;
			else if (pMString_key == "PadAdd") virtualKey_shortCut = kNumericPadAdd;
			else if (pMString_key == "PadSubtract") virtualKey_shortCut = kNumericPadSubtract;
			else if (pMString_key == "PadMultiply") virtualKey_shortCut = kNumericPadMultiply;
			else if (pMString_key == "PadDivide") virtualKey_shortCut = kNumericPadDivide;
			else if (pMString_key == "PadPeriod") virtualKey_shortCut = kNumericPadPeriod;
			else if (pMString_key == "Pad0") virtualKey_shortCut = kNumericPad0;
			else if (pMString_key == "Pad1") virtualKey_shortCut = kNumericPad1;
			else if (pMString_key == "Pad2") virtualKey_shortCut = kNumericPad2;
			else if (pMString_key == "Pad3") virtualKey_shortCut = kNumericPad3;
			else if (pMString_key == "Pad4") virtualKey_shortCut = kNumericPad4;
			else if (pMString_key == "Pad5") virtualKey_shortCut = kNumericPad5;
			else if (pMString_key == "Pad6") virtualKey_shortCut = kNumericPad6;
			else if (pMString_key == "Pad7") virtualKey_shortCut = kNumericPad7;
			else if (pMString_key == "Pad8") virtualKey_shortCut = kNumericPad8;
			else if (pMString_key == "Pad9") virtualKey_shortCut = kNumericPad9;
			else
			{
				status = Utils<IScriptErrorUtils>()->
					SetOutOfRangeErrorData(iScriptRequestData, p_KESCKey, ScriptData(pMString_key));
				break;
			}
		}
		else
		{
			pMString_key.ToUpper();

			int32 bufferSize = pMString_key.CharCount() + 1; // Character count + terminator.

			wchar_t* sysCharBuffer = new wchar_t[bufferSize];

			pMString_key.GetWChar_tString(sysCharBuffer, bufferSize);

			SysChar theChar = sysCharBuffer[0];

			VirtualKey virtualKey(theChar);

			virtualKey_shortCut = virtualKey;

			delete[] sysCharBuffer;
		}

		// Get modifier argument.
		int16 modifiers = 0;
		{
			ScriptID scriptID_enumData;

			if (iScriptRequestData->ExtractRequestData(p_KESCModifier, scriptData) != kSuccess) break;

			if (scriptData.GetEnumeration(&scriptID_enumData) != kSuccess) break;

			switch (scriptID_enumData.Get())
			{
			case en_KESNo: // no
				modifiers = kNoKBSCModifier;
				break;

			case en_KESControl: // control
				modifiers = kControl; 
				break;

			case en_KESShift: // shift
				modifiers = kShift;
				break;

			case en_KESAltOrOption: // altOrOption
				modifiers = kOption;
				break;

			case en_KESControlShift: // controlShift
				modifiers = kControlShift;
				break;

			case en_KESControlAltOrOption: // controlAltOrOption
				modifiers = kControlOption;
				break;

			case en_KESShiftAltOrOption: // shiftAltOrOption
				modifiers = kShiftOption;
				break;

			case en_KESControlShiftAltOrOption: // controlShiftAltOrOption
				modifiers = kControlShiftOption;
				break;
			default:
				break;
			}
		}

		// Target Style
		PMString PMString_parentName = iScript->GetObjectInfo(iScriptRequestData->GetRequestContext())->GetName();
		if (PMString_parentName == "character style" || PMString_parentName == "paragraph style") {
			InterfacePtr<IStyleInfo> iStyleInfo(iScript, ::UseDefaultIID());
			if (!iStyleInfo) break;

			// Set keyboard shortcut.
			iStyleInfo->SetKeyboardShortcut(virtualKey_shortCut, modifiers);
		}

		// Panel redraw.
		{
			InterfacePtr<IApplication> iApplication(GetExecutionContextSession()->QueryApplication());
			if (iApplication == nil) break;

			InterfacePtr<IPanelMgr> iPanelMgr(iApplication->QueryPanelManager());

			WidgetID widgetID;
			ActionID actionID;
			if (PMString_parentName == "character style")
			{
				actionID = kCharacterStylesPanelActionID;
				widgetID = kCharStylePanelWidgetID;
			}
			else if (PMString_parentName == "paragraph style")
			{
				actionID = kParagraphStylesPanelActionID;
				widgetID = kParaStylePanelWidgetID;
			}

			bool16 result = iPanelMgr->DoesPanelExist(widgetID);
			if (result)
			{
				result = iPanelMgr->IsPanelWithMenuIDShown(actionID);
				if (result)
				{
					IControlView* iControlView = iPanelMgr->GetPanelFromWidgetID(widgetID);

					iControlView->ForceRedraw();
				}
			}
		}
		status = kSuccess;

	} while (false); // only do once

	return status; // If kSuccess is not returned, an error occurs
}
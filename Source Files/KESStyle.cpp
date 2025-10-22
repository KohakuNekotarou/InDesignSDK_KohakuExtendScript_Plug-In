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

		// Get Key.
		PMString pMString_key;
		{
			if (iScriptRequestData->ExtractRequestData(p_KESCKey, scriptData) != kSuccess) break;

			if (scriptData.GetPMString(pMString_key) != kSuccess) break;

			pMString_key.ToUpper();
		}

		int32 bufferSize = pMString_key.CharCount() + 1; // Character count + terminator.

		wchar_t* sysCharBuffer = new wchar_t[bufferSize];

		pMString_key.GetWChar_tString(sysCharBuffer, bufferSize);

		VirtualKey virtualKey(sysCharBuffer[0]);

		delete[] sysCharBuffer;

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

		InterfacePtr<IStyleInfo> iStyleInfo(iScript, ::UseDefaultIID());
		if (!iStyleInfo) break;

		// Set keyboard shortcut.
		iStyleInfo->SetKeyboardShortcut(virtualKey, modifiers);

		// Panel redraw.
		{
			InterfacePtr<IApplication> iApplication(GetExecutionContextSession()->QueryApplication());
			if (iApplication == nil) break;

			InterfacePtr<IPanelMgr> iPanelMgr(iApplication->QueryPanelManager());

			PMString PMString_name = iScript->GetObjectInfo(iScriptRequestData->GetRequestContext())->GetName();

			WidgetID widgetID;
			if (PMString_name == "character style") widgetID = kCharStylePanelWidgetID;
			else if (PMString_name == "paragraph style") widgetID = kParaStylePanelWidgetID;

			bool16 result = iPanelMgr->DoesPanelExist(widgetID);
			if (result)
			{
				IControlView* iControlView = iPanelMgr->GetPanelFromWidgetID(widgetID);

				iControlView->ForceRedraw();
			}
		}

		status = kSuccess;

	} while (false); // only do once

	return status; // If kSuccess is not returned, an error occurs
}
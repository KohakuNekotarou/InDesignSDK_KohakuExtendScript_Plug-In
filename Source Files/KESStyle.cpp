#include "VCPlugInHeaders.h"

// ---------------------------------------------------------------------------------------
// Interface includes:
#include "IApplication.h"
#include "IControlView.h"
#include "IObjectStyleInfo.h"
#include "IPanelMgr.h"
#include "IScript.h"
#include "IScriptRequestData.h"
#include "IShortcutUtils.h"
#include "IStyleInfo.h"
#include "IScriptUtils.h"

// ---------------------------------------------------------------------------------------
// General includes:
#include "CAlert.h" // CAlert::InformationAlert(Msg);
#include "GlobalTime.h"
#include "ObjStylesUIID.h"
#include "PMString.h"
#include "StylePanelID.h"
#include "TablesID.h"
#include "TabStyUIID.h"
#include "VirtualKey.h"
#include "ScriptInfo.h"

// ---------------------------------------------------------------------------------------
// Project includes:
#include "KESStyle.h"

// Set keyboard shortcut.
ErrorCode KESStyle::KeyboardShortcut(ScriptID scriptID, IScriptRequestData* iScriptRequestData, IScript* iScript)
{
	ErrorCode status = kFailure;

	do
	{
		ScriptData scriptData;
		PMString pMString_shortcut;
		if (iScriptRequestData->IsPropertyGet()) // Get
		{
			InterfacePtr<IStyleInfo> iStyleInfo(iScript, ::UseDefaultIID());
			if (iStyleInfo == nil) break;

			int16 modifiers = 0;
			VirtualKey shortcutKey = iStyleInfo->GetKeyboardShortcut(&modifiers);

			pMString_shortcut = Utils<IShortcutUtils>()->GetShortcutString(shortcutKey, modifiers);

			scriptData.SetPMString(pMString_shortcut);

			iScriptRequestData->AppendReturnData(iScript, scriptID, scriptData);
		}
		else if (iScriptRequestData->IsPropertyPut()) // Put
		{
			status = iScriptRequestData->ExtractRequestData(scriptID.Get(), scriptData);
			if (status != kSuccess) break;

			status = scriptData.GetPMString(pMString_shortcut);
			if (status != kSuccess) break;

			VirtualKey virtualKey_keyOut;
			int16 int16_modsOut;
			Utils<IShortcutUtils>()->ParseShortcutString(pMString_shortcut, &virtualKey_keyOut, &int16_modsOut);

			PMString PMString_targetStyle = iScript->GetObjectInfo(iScriptRequestData->GetRequestContext())->GetName();

			GlobalTime globalTime_TimeStamp; // TimeStamp
			globalTime_TimeStamp.CurrentTime();
			if (PMString_targetStyle == "object style")
			{
				InterfacePtr<IObjectStyleInfo> iObjectStyleInfo(iScript, ::UseDefaultIID());
				if (!iObjectStyleInfo) break;

				// Set keyboard shortcut.
				iObjectStyleInfo->SetKeyboardShortcut(virtualKey_keyOut, int16_modsOut);

				// Set timeStamp.
				if (pMString_shortcut != "") iObjectStyleInfo->SetKeyboardShortcutTimeStamp(globalTime_TimeStamp);
			}
			else if (
				PMString_targetStyle == "character style" ||
				PMString_targetStyle == "paragraph style" ||
				PMString_targetStyle == "cell style" ||
				PMString_targetStyle == "table style"
				)
			{
				InterfacePtr<IStyleInfo> iStyleInfo(iScript, ::UseDefaultIID());
				if (!iStyleInfo) break;

				// Set shortcut.
				iStyleInfo->SetKeyboardShortcut(virtualKey_keyOut, int16_modsOut);

				// Set timeStamp.
				if (pMString_shortcut != "") iStyleInfo->SetKeyboardShortcutTimeStamp(globalTime_TimeStamp);
			}

			// Panel redraw.
			{
				InterfacePtr<IApplication> iApplication(GetExecutionContextSession()->QueryApplication());
				if (iApplication == nil) break;

				InterfacePtr<IPanelMgr> iPanelMgr(iApplication->QueryPanelManager());

				WidgetID widgetID;
				ActionID actionID;
				if (PMString_targetStyle == "object style")
				{
					actionID = kObjectStylePanelActionID;
					widgetID = kObjStylesTreeViewPanelWidgetID;
				}
				else if (PMString_targetStyle == "cell style")
				{
					actionID = kCellStylesPanelActionID;
					widgetID = kTabStyUICellStylePanelWidgetID;
				}
				else if (PMString_targetStyle == "table style")
				{
					actionID = kTableStylesPanelActionID;
					widgetID = kTabStyUITableStylePanelWidgetID;
				}
				else if (PMString_targetStyle == "character style")
				{
					actionID = kCharacterStylesPanelActionID;
					widgetID = kCharStylePanelWidgetID;
				}
				else if (PMString_targetStyle == "paragraph style")
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
		}
		status = kSuccess;

	} while (false); // only do once

	return status; // If kSuccess is not returned, an error occurs
}
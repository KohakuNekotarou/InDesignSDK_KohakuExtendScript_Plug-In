#include "VCPlugInHeaders.h" // Visual Studio only?

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

		PMString pMString_shortcut;
		if (iScriptRequestData->ExtractRequestData(p_KESShortcutStr, scriptData) != kSuccess) break;

		if (scriptData.GetPMString(pMString_shortcut) != kSuccess) break;

		VirtualKey virtualKey_keyOut;
		int16 int16_modsOut;
		Utils<IShortcutUtils>()->ParseShortcutString(pMString_shortcut, &virtualKey_keyOut, &int16_modsOut);

		// Target Style
		PMString PMString_parentName = iScript->GetObjectInfo(iScriptRequestData->GetRequestContext())->GetName();

		// TimeStamp
		GlobalTime globalTime_TimeStamp;
		globalTime_TimeStamp.CurrentTime();

		if (PMString_parentName == "object style")
		{
			InterfacePtr<IObjectStyleInfo> iObjectStyleInfo(iScript, ::UseDefaultIID());
			if (!iObjectStyleInfo) break;

			// Set keyboard shortcut.
			iObjectStyleInfo->SetKeyboardShortcut(virtualKey_keyOut, int16_modsOut);

			// Set timeStamp.
			if (pMString_shortcut != "") iObjectStyleInfo->SetKeyboardShortcutTimeStamp(globalTime_TimeStamp);
		}
		else if (
			PMString_parentName == "character style" ||
			PMString_parentName == "paragraph style" ||
			PMString_parentName == "cell style" ||
			PMString_parentName == "table style"
			)
		{
			InterfacePtr<IStyleInfo> iStyleInfo(iScript, ::UseDefaultIID());
			if (!iStyleInfo) break;

			// Set shortcut.
			iStyleInfo->SetKeyboardShortcut(virtualKey_keyOut, int16_modsOut);

			// Set timeStamp.
			if(pMString_shortcut != "") iStyleInfo->SetKeyboardShortcutTimeStamp(globalTime_TimeStamp);
		}

		// Panel redraw.
		{
			InterfacePtr<IApplication> iApplication(GetExecutionContextSession()->QueryApplication());
			if (iApplication == nil) break;

			InterfacePtr<IPanelMgr> iPanelMgr(iApplication->QueryPanelManager());

			WidgetID widgetID;
			ActionID actionID;
			if (PMString_parentName == "object style")
			{
				actionID = kObjectStylePanelActionID;
				widgetID = kObjStylesTreeViewPanelWidgetID;
			}
			else if (PMString_parentName == "cell style")
			{
				actionID = kCellStylesPanelActionID;
				widgetID = kTabStyUICellStylePanelWidgetID;
			}
			else if (PMString_parentName == "table style")
			{
				actionID = kTableStylesPanelActionID;
				widgetID = kTabStyUITableStylePanelWidgetID;
			}
			else if (PMString_parentName == "character style")
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
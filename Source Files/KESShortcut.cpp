#include "VCPlugInHeaders.h"

// Interface includes:
#include "IActionManager.h"
#include "IApplication.h"
#include "IScriptErrorUtils.h"
#include "IShortcutContext.h"
#include "IShortcutManager.h"
#include "IShortcutUtils.h"

// General includes:
#include "CAlert.h" // CAlert::InformationAlert(Msg);
#include "keyboarddefs.h" // for kVirtualNullKey.

// Project includes:
#include "KESScriptingDefs.h"
#include "KESShortcut.h"

ErrorCode KESShortcut::RemoveContextShortcut(IScriptRequestData* iScriptRequestData, IScript* iScript)
{
	ErrorCode status = kFailure;

	do
	{
		ScriptData scriptData;

		// ---------------------------------------------------------------------------------------
		// Query shortcut context.
		PMString pMString_context;
		if (iScriptRequestData->ExtractRequestData(p_KESRemoveContextShortcutContextString, scriptData) != kSuccess) break;

		if (scriptData.GetPMString(pMString_context) != kSuccess) break;

		// validate.
		if (
			pMString_context != "DialogContext" &&
			pMString_context != "DefaultContext" &&
			pMString_context != "TableContext" &&
			pMString_context != "TableObjectContext" &&
			pMString_context != "KBSCContext_XMLStructureContext" &&
			pMString_context != "FullScreenContext" &&
			pMString_context != "TextContext"
			)
		{
			return Utils<IScriptErrorUtils>()->
				SetMissingRequiredParameterErrorData(iScriptRequestData, p_KESRemoveContextShortcutContextString);
		}

		// ---------------------------------------------------------------------------------------
		// Query shortcut string.
		PMString pMString_shortcut;
		if (iScriptRequestData->ExtractRequestData(p_KESRemoveContextShortcutString, scriptData) != kSuccess) break;

		if (scriptData.GetPMString(pMString_shortcut) != kSuccess) break;
		
		// ---------------------------------------------------------------------------------------
		// Parse shortcut string.
		VirtualKey virtualKey_keyOut;
		int16 int16_modsOut;
		Utils<IShortcutUtils>()->ParseShortcutString(pMString_shortcut, &virtualKey_keyOut, &int16_modsOut);

		if (virtualKey_keyOut == kVirtualNullKey)
		{
			return Utils<IScriptErrorUtils>()->
				SetMissingRequiredParameterErrorData(iScriptRequestData, p_KESRemoveContextShortcutString);
		}

		// ---------------------------------------------------------------------------------------
		// Remove shortcut.
		InterfacePtr<IApplication> iApplication(GetExecutionContextSession()->QueryApplication());
		if (iApplication == nil) break;

		InterfacePtr<IActionManager> iActionManager(iApplication->QueryActionManager());
		if (iActionManager == nil) break;

		InterfacePtr<IShortcutManager> iShortcutManager(iActionManager, ::UseDefaultIID());
		if (iShortcutManager == nil) break;

		iShortcutManager->RemoveShortcut(pMString_context, virtualKey_keyOut, int16_modsOut);

		status = kSuccess;

	} while (false); // only do once.

	return status; // If kSuccess is not returned, an error occurs.
}
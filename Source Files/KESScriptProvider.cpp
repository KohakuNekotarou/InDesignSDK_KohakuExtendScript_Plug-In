#include "VCPlugInHeaders.h"

// Implementation includes:
#include "CScriptProvider.h"

// Interface includes:
#include "IScript.h"
#include "IScriptRequestData.h"

// General includes:
#include "CAlert.h" // CAlert::InformationAlert(Msg);

// Project includes:
#include "KESScriptingDefs.h"
#include "KESID.h"
#include "KESLayout.h"
#include "KESLayoutScrollObserver.h"
#include "KESShortcut.h"
#include "KESStyle.h"

class KESScriptProvider : public CScriptProvider // Adding properties or methods to existing objects.
{
public:

	KESScriptProvider(IPMUnknown* boss) : CScriptProvider(boss) {};

	~KESScriptProvider() {}

	// This method is called if a provider can handle an method.
	// @param scriptID identifies the ID of the method to handle.
	// @param iScriptRequestData identifies an interface pointer used to extract data.
	// @param iScript identifies an interface pointer on the script object representing the parent of the application object.
	virtual ErrorCode HandleMethod(ScriptID scriptID, IScriptRequestData* iScriptRequestData, IScript* iScript);

	// This method is called if a provider can handle a property.
	virtual ErrorCode AccessProperty(ScriptID scriptID, IScriptRequestData* iScriptRequestData, IScript* iScript);
};


// CREATE_PMINTERFACE
// Binds the C++ implementation class onto its ImplementationID making the C++ code callable by the application.
CREATE_PMINTERFACE(KESScriptProvider, kKESScriptProviderImpl)

// HandleMethod
ErrorCode KESScriptProvider::HandleMethod(ScriptID scriptID, IScriptRequestData* iScriptRequestData, IScript* iScript)
{
	ErrorCode status = kFailure;

	switch (scriptID.Get())
	{
	// Match scroll zoom all layout.
	case KESScriptEvents::e_KESMatchScrollZoomAllLayout:

		status = KESLayout::MatchScrollZoomAllLayout(1, nil);
		break;

	case KESScriptEvents::e_KESToggleSplitLayout:

		status = KESLayout::ToggleSplitLayout(iScript);
		break;

	case KESScriptEvents::e_KESQueryNthLayout:

		status = KESLayout::QueryNthLayout(scriptID, iScriptRequestData, iScript);
		break;

	case KESScriptEvents::e_KESIsSplitLayoutViewShown:

		status = KESLayout::IsSplitLayoutViewShown(scriptID, iScriptRequestData, iScript);
		break;

	case KESScriptEvents::e_KESRemoveContextShortcut:

		status = KESShortcut::RemoveContextShortcut(iScriptRequestData, iScript);
		break;

	default:
		status = CScriptProvider::HandleMethod(scriptID, iScriptRequestData, iScript);
	}
    return status;
}

// AccessProperty
ErrorCode KESScriptProvider::AccessProperty(ScriptID scriptID, IScriptRequestData* iScriptRequestData, IScript* iScript)
{
	ErrorCode status = kFailure;

	switch (scriptID.Get())
	{
	case KESScriptProperties::p_KESAccessContentLocationAtFrameOriginX:

		status = KESLayout::AccessContentLocationAtFrameOrigin(scriptID, iScriptRequestData, iScript, "X");
		break;

	case KESScriptProperties::p_KESAccessContentLocationAtFrameOriginY:

		status = KESLayout::AccessContentLocationAtFrameOrigin(scriptID, iScriptRequestData, iScript, "Y");
		break;

	case KESScriptProperties::p_KESAutoMatchScrollZoomAllLayout:

		status = KESLayoutScrollObserver::AutoMatchScrollZoomAllLayout(scriptID, iScriptRequestData, iScript);
		break;

	case KESScriptProperties::p_KESKeyboardShortcutForStyle:

		status = KESStyle::KeyboardShortcut(scriptID, iScriptRequestData, iScript);
		break;

	default:
		status = CScriptProvider::AccessProperty(scriptID, iScriptRequestData, iScript);
	}
	return status;
}
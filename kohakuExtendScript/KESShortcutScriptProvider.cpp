#include "VCPlugInHeaders.h"

// Implementation includes:
#include "ScriptData.h"
#include "CScriptProvider.h"

// Interface includes:
#include "IActionManager.h"
#include "IApplication.h"
#include "IIntData.h"
#include "IScript.h"
#include "IScriptRequestData.h"
#include "IShortcutManager.h"

// General includes:
#include "CAlert.h" // CAlert::InformationAlert(Msg);

// Project includes:
#include "KESID.h"
#include "KESScriptingDefs.h"

// RepresentScriptProvider
class KESShortcutScriptProvider : public RepresentScriptProvider
{
public:

	KESShortcutScriptProvider(IPMUnknown* boss);

	virtual ~KESShortcutScriptProvider();

	//virtual ErrorCode HandleMethod(ScriptID scriptID, IScriptRequestData* iScriptRequestData, IScript* iScript);

	//virtual ErrorCode AccessProperty(ScriptID scriptID, IScriptRequestData* iScriptRequestData, IScript* iScript);

protected:

	// Get the number of child objects in a collection on the given parent.
	virtual int32 GetNumObjects(const IScriptRequestData* iScriptRequestData, IScript* iScript);

	// Append the nth child object from a collection on the given parent.
	virtual ErrorCode AppendNthObject(const IScriptRequestData* iScriptRequestData, IScript* iScript, int32 int32_n, ScriptList& scriptList);
};

// Make the implementation available to the application.
CREATE_PMINTERFACE(KESShortcutScriptProvider, kKESShortcutScriptProviderImpl)

KESShortcutScriptProvider::KESShortcutScriptProvider(IPMUnknown* boss) :
	RepresentScriptProvider(boss)
{
	// Do nothing
}

KESShortcutScriptProvider::~KESShortcutScriptProvider() {}
/*
ErrorCode KESShortcutScriptProvider::HandleMethod(ScriptID scriptID, IScriptRequestData* iScriptRequestData, IScript* iScript)
{
	ErrorCode result = kFailure;
	do
	{

	} while (false);
	return result;
}

ErrorCode KESShortcutScriptProvider::AccessProperty(ScriptID scriptID, IScriptRequestData* iScriptRequestData, IScript* iScript)
{
	ErrorCode result = kFailure;
	do
	{
	} while (false);

	return result;
}
*/
// GetNumObjects
// For example,
// app.menuActions[0].shortcuts[0]
// will process
// GetNumObjects
// AppendNthObject
// in that order.
int32 KESShortcutScriptProvider::GetNumObjects(const IScriptRequestData* iScriptRequestData, IScript* iScript)
{

	int32 int32_numObjects = 0;
	do
	{
		// ---------------------------------------------------------------------------------------
		// Get actionID.
		ScriptObject scriptObject = iScript->GetScriptObject(iScriptRequestData->GetRequestContext());

		ScriptData scriptData = scriptObject.specifierData;

		int32 int32_id;
		scriptData.GetInt32(&int32_id);

		// ---------------------------------------------------------------------------------------
		// Get actionID.
		InterfacePtr<IApplication> iApplication(GetExecutionContextSession()->QueryApplication());
		if (iApplication == nil) break;

		InterfacePtr<IActionManager> iActionManager(iApplication->QueryActionManager());
		if (iActionManager == nil) break;

		InterfacePtr<IShortcutManager> iShortcutManager(iActionManager, ::UseDefaultIID());
		if (iShortcutManager == nil) break;

		int32_numObjects = iShortcutManager->GetNumShortcutsForAction(int32_id);
	} while (false);

	return int32_numObjects;
}

// Append Nth object
ErrorCode KESShortcutScriptProvider::AppendNthObject(const IScriptRequestData* iScriptRequestData, IScript* iScript, int32 int32_n, ScriptList& scriptList)
{
	ErrorCode result = kFailure;

	do
	{
		// check input parameters
		if (iScriptRequestData == nil || iScript == nil) break;

		// create a proxy script object
		InterfacePtr<IScript> iScript_proxyScriptObject(Utils<IScriptUtils>()->CreateProxyScriptObject(
			iScriptRequestData->GetRequestContext(),
			kKESShortcutScriptObjectBoss,
			c_KESShortcutObject,
			iScript
		));
		if (iScript == nil) break;

		// query for data interfaces
		InterfacePtr<IIntData> iIntData(iScript_proxyScriptObject, ::UseDefaultIID());
		if (iIntData == nil) break;

		// set the name
		iIntData->Set(int32_n);

		// add the object to the list
		scriptList.push_back(iScript_proxyScriptObject);

		result = kSuccess;

	} while (false);

	return result;
}
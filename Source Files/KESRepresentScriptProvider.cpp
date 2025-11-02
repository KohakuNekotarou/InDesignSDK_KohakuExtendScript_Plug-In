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

// RepresentScriptProvider
class KESRepresentScriptProvider : public RepresentScriptProvider
{
public:

	KESRepresentScriptProvider(IPMUnknown* boss);

	virtual ~KESRepresentScriptProvider();

	virtual ErrorCode HandleMethod(ScriptID methodID, IScriptRequestData* data, IScript* script);

	virtual ErrorCode AccessProperty(ScriptID propID, IScriptRequestData* data, IScript* parent);

protected:

	// Get the number of child objects in a collection on the given parent.
	virtual int32 GetNumObjects(const IScriptRequestData* data, IScript* parent);

	// Append the nth child object from a collection on the given parent.
	virtual ErrorCode AppendNthObject(const IScriptRequestData* data, IScript* parent, int32 n, ScriptList& objectList);
};

// Make the implementation available to the application.
CREATE_PMINTERFACE(KESRepresentScriptProvider, kKESRepresentScriptProviderImpl)

KESRepresentScriptProvider::KESRepresentScriptProvider(IPMUnknown* boss) : RepresentScriptProvider(boss){}

KESRepresentScriptProvider::~KESRepresentScriptProvider(){}

ErrorCode KESRepresentScriptProvider::HandleMethod(ScriptID methodID, IScriptRequestData* data, IScript* script)
{
	ErrorCode result = kFailure;
	do
	{

	} while (false);
	return result;
}

ErrorCode KESRepresentScriptProvider::AccessProperty(ScriptID propID, IScriptRequestData* data, IScript* script)
{
	ErrorCode result = kFailure;
	do
	{
	} while (false);

	return result;
}

// Get num objects.
// When using firstItem() etc.
int32 KESRepresentScriptProvider::GetNumObjects(const IScriptRequestData* data, IScript* parent)
{
	int32 numObjects = 0;
	do
	{
		CAlert::InformationAlert("GetNumObject");
	} while (false);
	return numObjects;
}

ErrorCode KESRepresentScriptProvider::AppendNthObject(const IScriptRequestData* data, IScript* parent, int32 n, ScriptList& objectList)
{
	ErrorCode result = kFailure;
	do
	{
		CAlert::InformationAlert("AppendNthObject");
	} while (false);

	return result;
}
#include "VCPlugInHeaders.h"

// Interface includes:

// Implementation includes:
#include "CScript.h"
#include "KESID.h"
#include "KESScriptingDefs.h"

class KESSplitLayoutViewScript : public CScript
{
public:

	KESSplitLayoutViewScript(IPMUnknown* boss);

	virtual ~KESSplitLayoutViewScript(void);

	// Return the object's type.
	virtual ScriptID GetObjectType(const RequestContext& requestContext) const;

	// Set the object's type.
	virtual void SetObjectType(const ScriptID& scriptID, const RequestContext& requestContext);

	// Return the parent of this object in the script DOM hierarchy.
	// IDOMElement::QueryParent delegates to this method.
	// @param pMIID IN IID of interest on the parent DOM object.
	// @param requestContext is the request context
	// @return An interface pointer to the IID of interest on the parent DOM object.
	virtual IPMUnknown* QueryParent(const PMIID& pMIID, const RequestContext& requestContext) const;
};

CREATE_PMINTERFACE(KESSplitLayoutViewScript, kKESSplitLayoutViewScriptImpl)

KESSplitLayoutViewScript::KESSplitLayoutViewScript(IPMUnknown* boss) : CScript(boss) {}

KESSplitLayoutViewScript::~KESSplitLayoutViewScript(void) {}

void KESSplitLayoutViewScript::SetObjectType(const ScriptID& scriptID, const RequestContext& requestContext)
{
	ASSERT(type == c_KESSplitLayoutViewObject);
}

ScriptID KESSplitLayoutViewScript::GetObjectType(const RequestContext& requestContext) const
{
	return c_KESSplitLayoutViewObject;
}

IPMUnknown* KESSplitLayoutViewScript::QueryParent(const PMIID& iid, const RequestContext& context) const
{
	IPMUnknown* iPMUnknown_parent = nil;



	return iPMUnknown_parent;
}
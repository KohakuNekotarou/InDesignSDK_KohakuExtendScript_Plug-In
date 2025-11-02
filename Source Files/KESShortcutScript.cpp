#include "VCPlugInHeaders.h"

// Interface includes:
#include "IApplication.h"
#include "IDataBase.h"
#include "IPMUnknown.h"
#include "IStringData.h"

// General includes:
#include "CProxyScript.h" // includes IScript.h and IPMUnknown.h

// Project includes:
#include "KESID.h"
#include "KESScriptingDefs.h"
#include "KESShortcut.h"

class KESShortcutScript : public CProxyScript // For script objects that are not UID-based.
{
public:
	KESShortcutScript(IPMUnknown* boss);

	virtual ~KESShortcutScript(void);

	// Returns the database related to this object.
	// Since the Shortcut isn't persistent, we just return the application database.
	virtual IDataBase* GetDataBase(const RequestContext& requestContext) const;

	// Return information for the object specifier.
	virtual ScriptObject GetScriptObject(const RequestContext& requestContext) const;

private:
	IDataBase* fDB;
};

// Make the implementation available to the application.
CREATE_PMINTERFACE(KESShortcutScript, kKESShortcutScriptImpl)

// Constructor
KESShortcutScript::KESShortcutScript(IPMUnknown* boss) : CProxyScript(boss)
{
	// NOTE: this ScriptID must match that used in the call to 
	// IScriptUtils::CreateProxyScriptObject in KESShortcutScriptProvider::AppendNthObject.
	this->fObjectType = c_KESShortcutObject;
	this->fDB = nil;
}

// Destructor
KESShortcutScript::~KESShortcutScript(void) {}

// GetDataBase
// A safe way to determine the appropriate database for this object. Most implementations
// can simply inherit and use the default implementation { return ::GetDataBase( this ) ; }
// but some script bosses are non-persistent, and should therefore override this method.
IDataBase* KESShortcutScript::GetDataBase(const RequestContext& requestContext) const
{
	if (fDB == nil)
	{
		InterfacePtr<IApplication> iApplication(GetExecutionContextSession()->QueryApplication());
		if (iApplication != nil) const_cast<KESShortcutScript*>(this)->fDB = ::GetDataBase(iApplication);
	}
	return fDB;
}

// GetScriptObject
ScriptObject KESShortcutScript::GetScriptObject(const RequestContext& requestContext) const
{
	// identify script object by name
	PMString pMString_name = "";
	do
	{
		
	} while (false);
	return ScriptObject(ScriptData(pMString_name), GetObjectType(requestContext), kFormName);
}
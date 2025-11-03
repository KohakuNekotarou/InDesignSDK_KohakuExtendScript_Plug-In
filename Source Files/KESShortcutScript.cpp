//========================================================================================
//  
//  $File$
//  
//  Owner: Adobe Developer Technologies
//  
//  $Author$
//  
//  $DateTime$
//  
//  $Revision$
//  
//  $Change$
//  
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

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

/** Implements IScript via partial implementation CProxyScript.
 * 	The main purpose is to declare the class ScriptID.
 * 
 * 	@ingroup snippetrunner
 * 	@author Ken Sadahiro
*/
class KESShortcutScript : public CProxyScript
{
public:
	/** Constructor */
	KESShortcutScript(IPMUnknown* boss);

	/** Returns the database related to this object.
	 * 	Since the SnippetRunner isn't persistent, we just return 
	 * 	the application database.
	 */
	virtual IDataBase* GetDataBase(const RequestContext &context) const;

private:
	IDataBase* fDB;
};

/* Make the implementation available to the application.
*/
CREATE_PMINTERFACE(KESShortcutScript, kKESShortcutScriptImpl)

/* Constructor
*/
KESShortcutScript::KESShortcutScript(IPMUnknown* boss) :
	CProxyScript(boss)	
{
	// NOTE: this ScriptID must match that used in the call to 
	// IScriptUtils::CreateProxyScriptObject in SnpRunnableScriptProvider::AppendNthObject.
	fObjectType = c_KESShortcutObject;
	fDB = nil;
}

/* GetDataBase
// A safe way to determine the appropriate database for this object. Most implementations
// can simply inherit and use the default implementation { return ::GetDataBase( this ) ; }
// but some script bosses are non-persistent, and should therefore override this method.
*/
IDataBase* KESShortcutScript::GetDataBase(const RequestContext &context) const
{
	if (fDB == nil)
	{
		InterfacePtr<IApplication> app(GetExecutionContextSession()->QueryApplication());
		if (app != nil) const_cast<KESShortcutScript*>(this)->fDB = ::GetDataBase(app);
	}
	return fDB;
}
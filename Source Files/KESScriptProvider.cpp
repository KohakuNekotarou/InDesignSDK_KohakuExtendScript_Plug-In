//========================================================================================
//  
//  $File: $
//  
//  Owner: 
//  
//  $Author: $
//  
//  $DateTime: $
//  
//  $Revision: $
//  
//  $Change: $
//  
//  Copyright 1997-2012 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// Interface includes:
#include "IScript.h"
#include "IScriptRequestData.h"

// General includes:
#include "CAlert.h"
#include "CScriptProvider.h"

// Project includes:
#include "KESScriptingDefs.h"
#include "KESID.h"
#include "KESLayout.h"

// CScriptProvider
// Adding properties or methods to existing objects.
// 既存のオブジェクトにプロパティやメソッドを追加する。
class KESScriptProvider : public CScriptProvider
{
public:
	/** Constructor.
	@param boss interface ptr from boss object on which this interface is aggregated.
	*/
	KESScriptProvider(IPMUnknown* boss) : CScriptProvider(boss) {};

	/** Destructor. Does nothing.
	*/
	~KESScriptProvider() {}

	/** This method is called if a provider can handle an method.
	@param scriptID identifies the ID of the method to handle.
	@param iScriptRequestData identifies an interface pointer used to extract data.
	@param iScript identifies an interface pointer on the script object representing the parent of the application object.
	*/
	virtual ErrorCode HandleMethod(ScriptID scriptID, IScriptRequestData* iScriptRequestData, IScript* iScript);

	/** This method is called if a provider can handle a property.
	*/
	virtual ErrorCode AccessProperty(ScriptID scriptID, IScriptRequestData* iScriptRequestData, IScript* iScript);
};


/* CREATE_PMINTERFACE
Binds the C++ implementation class onto its ImplementationID 
making the C++ code callable by the application.
*/
CREATE_PMINTERFACE(KESScriptProvider, kKESScriptProviderImpl)

/* HandleMethod */
ErrorCode KESScriptProvider::HandleMethod(ScriptID scriptID, IScriptRequestData* iScriptRequestData, IScript* iScript)
{
	ErrorCode status = kFailure;

	switch (scriptID.Get())
	{
	case KESScriptEvents::e_KESMatchScrollZoomAllLayout:

		status = KESLayout::MatchScrollZoomAllLayout();
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

	default:
		status = CScriptProvider::HandleMethod(scriptID, iScriptRequestData, iScript);
	}

    return status;
}

/* AccessProperty */
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

	default:
		status = CScriptProvider::AccessProperty(scriptID, iScriptRequestData, iScript);
	}

	return status;
}
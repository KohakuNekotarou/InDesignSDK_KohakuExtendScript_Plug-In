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
#include "KESLayoutScrool.h"

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
	@param methodID identifies the ID of the method to handle.
	@param data identifies an interface pointer used to extract data.
	@param parent identifies an interface pointer on the script object representing the parent of the application object.
	*/
	virtual ErrorCode HandleMethod(ScriptID methodID, IScriptRequestData* data, IScript* parent);

	/** This method is called if a provider can handle a property.
	@param propID identifies the ID of the property to handle.
	@param data identifies an interface pointer used to extract data.
	@param parent identifies an interface pointer on the script object 		representing the parent of the application object.
	*/
	virtual ErrorCode AccessProperty(ScriptID propID, IScriptRequestData* data, IScript* parent);
};


/* CREATE_PMINTERFACE
Binds the C++ implementation class onto its ImplementationID 
making the C++ code callable by the application.
*/
CREATE_PMINTERFACE(KESScriptProvider, kKESScriptProviderImpl)


/* HandleMethod */
ErrorCode KESScriptProvider::HandleMethod(ScriptID methodID, IScriptRequestData* data, IScript* parent)
{
	ErrorCode status = kFailure;

	switch (methodID.Get())
	{
	case e_MatchScrollZoomAllLayout:
		status = KESLayoutScrool::MatchScrollZoomAllLayout();
		break;
	case e_ToggleSplitLayout:
		status = KESLayoutScrool::ToggleSplitLayout(parent);
		//status = KESLayoutScrool::ToggleSplitLayout(parent);
		break;
	default:
		status = CScriptProvider::HandleMethod(methodID, data, parent);
	}

    return status;
}

/* AccessProperty */
ErrorCode KESScriptProvider::AccessProperty(ScriptID propID, IScriptRequestData* data, IScript* parent)
{
	ErrorCode status = kFailure;

	switch (propID.Get())
	{
	case p_AccessContentLocationAtFrameOriginX:
		status = KESLayoutScrool::AccessContentLocationAtFrameOrigin(propID, data, parent, "X");
		break;

	case p_AccessContentLocationAtFrameOriginY:
		status = KESLayoutScrool::AccessContentLocationAtFrameOrigin(propID, data, parent, "Y");
		break;

	default:
		status = CScriptProvider::AccessProperty(propID, data, parent);
	}

	return status;
}
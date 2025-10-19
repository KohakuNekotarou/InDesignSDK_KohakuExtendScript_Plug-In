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
#include "IActiveContext.h"
#include "IApplication.h"
#include "IControlView.h"
#include "IDocument.h"
#include "IDocumentList.h"
#include "ILayoutViewUtils.h"
#include "ILayoutUIUtils.h"
#include "IPanelControlData.h"
#include "IPanorama.h"
#include "iPresentationList.h"
#include "IScript.h"
#include "IScriptRequestData.h"

// General includes:
#include "CAlert.h" // CAlert::InformationAlert(Msg);
#include "CObserver.h"
#include "Utils.h"

// Project includes:
#include "KESID.h"
#include "KESLayout.h"
#include "KESLayoutScrollBarObserver.h"

// CREATE_PMINTERFACE
// Binds the C++ implementation class onto its ImplementationID
// making the C++ code callable by the application.
CREATE_PMINTERFACE(KESLayoutScrollBarObserver, kKESLayoutScrollBarObserverImpl)

// Constructor.
KESLayoutScrollBarObserver::KESLayoutScrollBarObserver(IPMUnknown* boss) : CObserver(boss)
{
}

KESLayoutScrollBarObserver::~KESLayoutScrollBarObserver()
{
}

void KESLayoutScrollBarObserver::Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy)
{
	switch (protocol.Get())
	{
	case IID_IACTIVECONTEXT:
	{
		IActiveContext::ContextInfo* contextInfo = reinterpret_cast<IActiveContext::ContextInfo*>(changedBy);

		if (contextInfo->Key() == IID_ICONTROLVIEW)
		{

			do {
				InterfacePtr<IApplication> iApplication(GetExecutionContextSession()->QueryApplication());
				if (iApplication == nil) break;

				InterfacePtr<IDocumentList> iDocumentList(iApplication->QueryDocumentList());
				if (iDocumentList == nil) break;

				int32 docCount = iDocumentList->GetDocCount();
				for (int32 i = 0; i < docCount; i++)
				{
					IDocument* iDocument = iDocumentList->GetNthDoc(i);
					if (iDocument == nil) continue;

					InterfacePtr<IPresentationList> iPresentationList(iDocument, ::UseDefaultIID());
					if (iPresentationList == nil) continue;

					IDocumentPresentation* iDocumentPresentation = iPresentationList->First();
					if (iDocumentPresentation == nil) continue;

					InterfacePtr<IPanelControlData> iPanelControlData(iDocumentPresentation, ::UseDefaultIID());
					if (iPanelControlData == nil) continue;

					IControlView* iControlView = iPanelControlData->FindWidget(kLayoutWidgetBoss);
					if (iControlView == nil) continue;

					InterfacePtr<ISubject> iSubject(iControlView, ::UseDefaultIID());
					if (!iSubject) break;

					bool16 attachFlg = iSubject->IsAttached
					(ISubject::kRegularAttachment, this, IID_IPANORAMA, IID_IKESLAYOUTSCROLLBAROBSERVER);

					if (attachFlg == kTrue)
					{
						iSubject->DetachObserver
						(ISubject::kRegularAttachment, this, IID_IPANORAMA, IID_IKESLAYOUTSCROLLBAROBSERVER);
					}
				}

				// If the active view is not a SplitLayoutView in the document's initial presentation.
				{
					IActiveContext* iActiveContext = GetExecutionContextSession()->GetActiveContext();
					if (iActiveContext == nil) break;

					IDocument* iDocument = iActiveContext->GetContextDocument();
					if (iDocument == nil) break;

					InterfacePtr<IPresentationList> iPresentationList(iDocument, ::UseDefaultIID());
					if (iPresentationList == nil) break;

					IDocumentPresentation* iDocumentPresentation = iPresentationList->First();
					if (iDocumentPresentation == nil) break;

					InterfacePtr<IPanelControlData> iPanelControlData(iDocumentPresentation, ::UseDefaultIID());
					if (iPanelControlData == nil) break;

					IControlView* iControlView = iPanelControlData->FindWidget(kLayoutWidgetBoss);
					if (iControlView == nil) break;

					InterfacePtr<IControlView> iControlView_frontView(Utils<ILayoutUIUtils>()->QueryFrontView());
					if (iControlView_frontView == nil) break;

					if (iControlView_frontView == iControlView)
					{
						InterfacePtr<ISubject> iSubject(iControlView_frontView, ::UseDefaultIID());
						if (iSubject == nil) break;

						iSubject->AttachObserver
						(ISubject::kRegularAttachment, this, IID_IPANORAMA, IID_IKESLAYOUTSCROLLBAROBSERVER);
					}
				}
			} while (false);
		}
		break;
	}
	case IID_IPANORAMA:
		KESLayout::MatchScrollZoomAllLayout(0);
		break;

	default:
		break;
	}
}

void KESLayoutScrollBarObserver::LazyUpdate(ISubject* iSubject, const PMIID& protocol, const LazyNotificationData* data)
{

}

// Match scroll zoom all layout attach.
ErrorCode KESLayoutScrollBarObserver::AutoMatchScrollZoomAllLayout
	(ScriptID scriptID, IScriptRequestData* iScriptRequestData, IScript* iScript)
{
	ErrorCode status = kFailure;

	do
	{
		// Request
		ScriptData scriptData;
		if (iScriptRequestData->IsPropertyGet())
		{
			
			//iScriptRequestData->AppendReturnData(iScript, scriptID, scriptData);

			status = kSuccess;
		}
		else if (iScriptRequestData->IsPropertyPut())
		{
			status = iScriptRequestData->ExtractRequestData(scriptID.Get(), scriptData);
			if (status != kSuccess) break;

			bool16 flg;
			status = scriptData.GetBoolean(&flg);
			if (status != kSuccess) break;

			if (flg == kTrue)
			{
				IActiveContext* iActiveContext = GetExecutionContextSession()->GetActiveContext();
				if (iActiveContext == nil) break;

				InterfacePtr<ISubject> iSubject(iActiveContext, ::UseDefaultIID());
				if (iSubject == nil) break;

				InterfacePtr<IObserver> iObserver(iActiveContext, IID_IKESLAYOUTSCROLLBAROBSERVER);
				if (iObserver == nil) break;


				bool16 attachFlg = iSubject->IsAttached
				(ISubject::kRegularAttachment, iObserver, IID_IACTIVECONTEXT, IID_IKESLAYOUTSCROLLBAROBSERVER);

				if (attachFlg == kFalse)
				{
					iSubject->AttachObserver
					(ISubject::kRegularAttachment, iObserver, IID_IACTIVECONTEXT, IID_IKESLAYOUTSCROLLBAROBSERVER);
				}
			}
			else
			{
			}

			status = kSuccess;
		}

	} while (false); // only do once

	return status;
}
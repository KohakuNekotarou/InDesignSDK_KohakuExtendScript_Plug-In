#include "VCPlugInHeaders.h"

// Interface includes:
#include "IActiveContext.h"
#include "IApplication.h"
#include "IControlView.h"
#include "IDocument.h"
#include "IDocumentList.h"
#include "IGalleyUtils.h"
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

		if (contextInfo->Key() == IID_ICONTROLVIEW) this->AttachPanorama();

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

			if (flg == kTrue) // Attach
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

				KESLayoutScrollBarObserver::AttachPanorama();
			}
			else // Detach
			{
				IActiveContext* iActiveContext = GetExecutionContextSession()->GetActiveContext();
				if (iActiveContext == nil) break;

				// Detach activeContext observer.
				{
					InterfacePtr<ISubject> iSubject(iActiveContext, ::UseDefaultIID());
					if (iSubject == nil) break;

					InterfacePtr<IObserver> iObserver(iActiveContext, IID_IKESLAYOUTSCROLLBAROBSERVER);
					if (iObserver == nil) break;

					bool16 attachFlg = iSubject->IsAttached
					(ISubject::kRegularAttachment, iObserver, IID_IACTIVECONTEXT, IID_IKESLAYOUTSCROLLBAROBSERVER);

					if (attachFlg == kTrue)
					{
						iSubject->DetachObserver
							(ISubject::kRegularAttachment, iObserver, IID_IACTIVECONTEXT, IID_IKESLAYOUTSCROLLBAROBSERVER);
					}
				}

				// Detach panorama observer.
				{
					K2Vector<IControlView*> iControlView_layoutViewList;
					Utils<ILayoutViewUtils>()->GetAllLayoutViews(iControlView_layoutViewList, nil, nil);

					for (K2Vector<IControlView*>::const_iterator iter = iControlView_layoutViewList.begin();
						iter != iControlView_layoutViewList.end(); ++iter)
					{
						IControlView* iControlView = *iter;
						if (iControlView == nil) continue;

						InterfacePtr<ISubject> iSubject(iControlView, ::UseDefaultIID());
						if (!iSubject) break;

						InterfacePtr<IObserver> iObserver(iActiveContext, IID_IKESLAYOUTSCROLLBAROBSERVER);
						if (iObserver == nil) break;

						bool16 attachFlg = iSubject->IsAttached
						(ISubject::kRegularAttachment, iObserver, IID_IPANORAMA, IID_IKESLAYOUTSCROLLBAROBSERVER);

						if (attachFlg == kTrue)
						{
							iSubject->DetachObserver
								(ISubject::kRegularAttachment, iObserver, IID_IPANORAMA, IID_IKESLAYOUTSCROLLBAROBSERVER);
						}
					}
				}
			}
			status = kSuccess;
		}
	} while (false); // only do once

	return status;
}

// Attach
void KESLayoutScrollBarObserver::AttachPanorama()
{
	do {
		IActiveContext* iActiveContext = GetExecutionContextSession()->GetActiveContext();
		if (iActiveContext == nil) break;

		InterfacePtr<IObserver> iObserver(iActiveContext, IID_IKESLAYOUTSCROLLBAROBSERVER);
		if (iObserver == nil) break;

		// Detach
		{
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

				// Galley or Story view.
				if (Utils<IGalleyUtils>() && Utils<IGalleyUtils>()->InGalleyOrStory(iDocumentPresentation)) continue;

				InterfacePtr<IPanelControlData> iPanelControlData(iDocumentPresentation, ::UseDefaultIID());
				if (iPanelControlData == nil) continue;

				IControlView* iControlView = iPanelControlData->FindWidget(kLayoutWidgetBoss);
				if (iControlView == nil) continue;

				InterfacePtr<ISubject> iSubject(iControlView, ::UseDefaultIID());
				if (!iSubject) break;

				bool16 attachFlg = iSubject->IsAttached
				(ISubject::kRegularAttachment, iObserver, IID_IPANORAMA, IID_IKESLAYOUTSCROLLBAROBSERVER);

				if (attachFlg == kTrue)
				{
					iSubject->DetachObserver
					(ISubject::kRegularAttachment, iObserver, IID_IPANORAMA, IID_IKESLAYOUTSCROLLBAROBSERVER);
				}
			}
		}

		// Attach
		// If the active view is not a SplitLayoutView in the document's initial presentation.
		{
			IDocument* iDocument = iActiveContext->GetContextDocument();
			if (iDocument == nil) break;

			InterfacePtr<IPresentationList> iPresentationList(iDocument, ::UseDefaultIID());
			if (iPresentationList == nil) break;

			IDocumentPresentation* iDocumentPresentation = iPresentationList->First();
			if (iDocumentPresentation == nil) break;

			// Galley or Story view.
			if (Utils<IGalleyUtils>() && Utils<IGalleyUtils>()->InGalleyOrStory(iDocumentPresentation)) break;

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
					(ISubject::kRegularAttachment, iObserver, IID_IPANORAMA, IID_IKESLAYOUTSCROLLBAROBSERVER);
			}
		}
	} while (false); // only do once
}
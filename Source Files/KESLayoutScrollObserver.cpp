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
#include "ISubject.h"

// General includes:
#include "CAlert.h" // CAlert::InformationAlert(Msg);
#include "CObserver.h"
#include "Utils.h"

// Project includes:
#include "KESID.h"
#include "KESLayout.h"
#include "KESLayoutScrollObserver.h"

// CREATE_PMINTERFACE
// Binds the C++ implementation class onto its ImplementationID making the C++ code callable by the application.
// C++実装クラスをImplementationIDにバインドし、アプリケーションからC++コードを呼び出せるようにする。
CREATE_PMINTERFACE(KESLayoutScrollObserver, kKESLayoutScrollObserverImpl)

// Constructor.
KESLayoutScrollObserver::KESLayoutScrollObserver(IPMUnknown* boss) : CObserver(boss) {}

// Destructor
KESLayoutScrollObserver::~KESLayoutScrollObserver() {}

// Update
void KESLayoutScrollObserver::Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy)
{
	switch (protocol.Get())
	{
	// When active document change.
	case IID_IACTIVECONTEXT:
	{
		IActiveContext::ContextInfo* contextInfo = (IActiveContext::ContextInfo*)changedBy;

		if (contextInfo->Key() == IID_IDOCUMENT) this->AttachDocumentFirstLayoutPanorama();

		break;
	}
	// When scroll or scale.
	case IID_IPANORAMA:
		switch (theChange.Get())
		{
		case kScrollToMessage:
		case kScrollByMessage:
		case kScaleToMessage:
		case kScaleByMessage:

			InterfacePtr<IPanorama> iPanorama_master(theSubject, ::UseDefaultIID());
			if (iPanorama_master == nil) break;

			bool16 pageFlg;
			KESLayout::MatchScrollZoomAllLayout(pageFlg = kFalse, iPanorama_master);
		}
		break;
	}
}

void KESLayoutScrollObserver::LazyUpdate
	(ISubject* iSubject, const PMIID& protocol, const LazyNotificationData* data) {}

// Match scroll zoom all layout attach.
ErrorCode KESLayoutScrollObserver::AutoMatchScrollZoomAllLayout
	(ScriptID scriptID, IScriptRequestData* iScriptRequestData, IScript* iScript)
{
	ErrorCode status = kFailure;

	do
	{
		ScriptData scriptData;

		PMString PMString_parentName = iScript->GetObjectInfo(iScriptRequestData->GetRequestContext())->GetName();

		IActiveContext* iActiveContext = GetExecutionContextSession()->GetActiveContext();
		if (iActiveContext == nil) break;

		InterfacePtr<IObserver> iObserver(iActiveContext, IID_IKESLayoutScrollObserver);
		if (iObserver == nil) break;

		if (iScriptRequestData->IsPropertyGet()) // Get
		{
			bool16 attachFlg;

			if (PMString_parentName == "application")
			{
				InterfacePtr<ISubject> iSubject(iActiveContext, ::UseDefaultIID());
				if (iSubject == nil) break;

				attachFlg = iSubject->IsAttached
					(ISubject::kRegularAttachment, iObserver, IID_IACTIVECONTEXT, IID_IKESLayoutScrollObserver);

				scriptData.SetBoolean(attachFlg);
			}
			else if(PMString_parentName == "layout window")
			{
				InterfacePtr<IPanelControlData> iPanelControlData(iScript, ::UseDefaultIID());
				if (!iPanelControlData) break;

				IControlView* iControlView = iPanelControlData->FindWidget(kLayoutWidgetBoss);
				if (!iControlView) break;

				InterfacePtr<ISubject> iSubject(iControlView, ::UseDefaultIID());
				if (!iSubject) break;

				attachFlg = iSubject->IsAttached
					(ISubject::kRegularAttachment, iObserver, IID_IPANORAMA, IID_IKESLayoutScrollObserver);

				scriptData.SetBoolean(attachFlg);
			}

			iScriptRequestData->AppendReturnData(iScript, scriptID, scriptData);

			status = kSuccess;
		}
		else if (iScriptRequestData->IsPropertyPut()) // Set
		{
			status = iScriptRequestData->ExtractRequestData(scriptID.Get(), scriptData);
			if (status != kSuccess) break;

			bool16 flg;
			status = scriptData.GetBoolean(&flg);
			if (status != kSuccess) break;

			if (flg == kTrue) // Attach
			{
				if (PMString_parentName == "application")
				{
					InterfacePtr<ISubject> iSubject(iActiveContext, ::UseDefaultIID());
					if (iSubject == nil) break;

					bool16 attachFlg = iSubject->IsAttached
					(ISubject::kRegularAttachment, iObserver, IID_IACTIVECONTEXT, IID_IKESLayoutScrollObserver);

					if (attachFlg == kFalse)
					{
						iSubject->AttachObserver
							(ISubject::kRegularAttachment, iObserver, IID_IACTIVECONTEXT, IID_IKESLayoutScrollObserver);
					}

					KESLayoutScrollObserver::AttachDocumentFirstLayoutPanorama();
				}
				else if (PMString_parentName == "layout window")
				{
					InterfacePtr<IPanelControlData> iPanelControlData(iScript, ::UseDefaultIID());
					if (!iPanelControlData) break;

					IControlView* iControlView = iPanelControlData->FindWidget(kLayoutWidgetBoss);
					if (!iControlView) break;

					KESLayoutScrollObserver::AttachPanorama(iActiveContext, iControlView);
				}
			}
			else // Detach
			{
				if (PMString_parentName == "application")
				{
					// Detach activeContext observer.
					{
						InterfacePtr<ISubject> iSubject(iActiveContext, ::UseDefaultIID());
						if (iSubject == nil) break;

						bool16 attachFlg = iSubject->IsAttached
						(ISubject::kRegularAttachment, iObserver, IID_IACTIVECONTEXT, IID_IKESLayoutScrollObserver);

						if (attachFlg == kTrue)
						{
							iSubject->DetachObserver
							(ISubject::kRegularAttachment, iObserver, IID_IACTIVECONTEXT, IID_IKESLayoutScrollObserver);
						}
					}

					// Detach panorama observer.
					KESLayoutScrollObserver::DetachAllPanorama(iActiveContext);
				}
				else if (PMString_parentName == "layout window")
				{
					InterfacePtr<IPanelControlData> iPanelControlData(iScript, ::UseDefaultIID());
					if (!iPanelControlData) break;

					IControlView* iControlView = iPanelControlData->FindWidget(kLayoutWidgetBoss);
					if (!iControlView) break;

					InterfacePtr<ISubject> iSubject(iControlView, ::UseDefaultIID());
					if (!iSubject) break;

					bool16 attachFlg = iSubject->IsAttached
						(ISubject::kRegularAttachment, iObserver, IID_IPANORAMA, IID_IKESLayoutScrollObserver);

					if (attachFlg == kTrue)
					{
						iSubject->DetachObserver
							(ISubject::kRegularAttachment, iObserver, IID_IPANORAMA, IID_IKESLayoutScrollObserver);
					}
				}
			}
			status = kSuccess;
		}
	} while (false); // only do once

	return status;
}

// Attach
void KESLayoutScrollObserver::AttachDocumentFirstLayoutPanorama()  
{
	do
	{
		IActiveContext* iActiveContext = GetExecutionContextSession()->GetActiveContext();
		if (iActiveContext == nil) break;

		InterfacePtr<IObserver> iObserver(iActiveContext, IID_IKESLayoutScrollObserver);
		if (iObserver == nil) break;

		// Detach
		KESLayoutScrollObserver::DetachAllPanorama(iActiveContext);

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
					(ISubject::kRegularAttachment, iObserver, IID_IPANORAMA, IID_IKESLayoutScrollObserver);
			}
		}
	} while (false); // only do once.
}

// Attach panorama.
void KESLayoutScrollObserver::AttachPanorama(IActiveContext* iActiveContext, IControlView* iControlView)
{
	do
	{
		// Detach all panorama.
		KESLayoutScrollObserver::DetachAllPanorama(iActiveContext);

		InterfacePtr<IObserver> iObserver(iActiveContext, IID_IKESLayoutScrollObserver);
		if (iObserver == nil) break;

		InterfacePtr<ISubject> iSubject(iControlView, ::UseDefaultIID());
		if (iSubject == nil) break;

		bool16 attachFlg = iSubject->IsAttached
			(ISubject::kRegularAttachment, iObserver, IID_IPANORAMA, IID_IKESLayoutScrollObserver);

		if (attachFlg == kTrue) break;

		iSubject->AttachObserver
			(ISubject::kRegularAttachment, iObserver, IID_IPANORAMA, IID_IKESLayoutScrollObserver);

	} while (false); // only do once.
}

// Detach all panorama.
void KESLayoutScrollObserver::DetachAllPanorama(IActiveContext* iActiveContext)
{
	do
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

			InterfacePtr<IObserver> iObserver(iActiveContext, IID_IKESLayoutScrollObserver);
			if (iObserver == nil) break;

			bool16 attachFlg = iSubject->IsAttached
			(ISubject::kRegularAttachment, iObserver, IID_IPANORAMA, IID_IKESLayoutScrollObserver);

			if (attachFlg == kTrue)
			{
				iSubject->DetachObserver
				(ISubject::kRegularAttachment, iObserver, IID_IPANORAMA, IID_IKESLayoutScrollObserver);
			}
		}
	} while (false); // only do once.
}
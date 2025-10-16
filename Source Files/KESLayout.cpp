#include "VCPlugInHeaders.h" // Visual Studio only?
#include "KESLayout.h"

// ---------------------------------------------------------------------------------------
// Interface includes:
#include "IApplication.h"
#include "IControlView.h"
#include "IControlViewCmdData.h"
#include "ICommand.h"
#include "IDataBase.h"
#include "IDocument.h"
#include "IDocumentList.h"
#include "IDocumentPresentation.h"
#include "IHierarchy.h"
#include "ILayoutControlData.h"
#include "ILayoutCmdData.h"
#include "ILayoutUIUtils.h"
#include "ILayoutViewUtils.h"
#include "IPageList.h"
#include "IPanelControlData.h"
#include "IPanorama.h"
#include "IPresentationList.h"
#include "IScript.h"
#include "IScriptRequestData.h"
#include "IScriptUtils.h"
#include "ISpread.h"
#include "IUIDData.h"
#include "IWidgetParent.h"

// ---------------------------------------------------------------------------------------
// General includes:
#include "CAlert.h" // CAlert::InformationAlert(Msg);
#include "ScriptData.h"
#include "Utils.h"

// ---------------------------------------------------------------------------------------
// Project includes:
#include "KESLayout.h"
#include "KESScriptingDefs.h"

/* MatchScrollZoomAllLayout */
ErrorCode KESLayout::MatchScrollZoomAllLayout()
{
	ErrorCode status = kFailure;
	do
	{
		// Get front layout view
		InterfacePtr<IControlView> iControlView_frontView(Utils<ILayoutUIUtils>()->QueryFrontView());
		if (!iControlView_frontView) break;

		// Panorama handles the control of content position, scale, and scrolling within the view's display area
		InterfacePtr<IPanorama> iPanorama_frontView(iControlView_frontView, ::UseDefaultIID());
		if (!iPanorama_frontView) break;

		// Get top-left position
		PMPoint pMPoint_frontViewTopLeft = iPanorama_frontView->GetContentLocationAtFrameOrigin();

		// Get scale
		PMReal xScale = iPanorama_frontView->GetXScaleFactor();
		PMReal yScale = iPanorama_frontView->GetYScaleFactor();

		// Get frontViewPageNumber
		PMString pmString_frontViewPageNumber;
		{	
			// Get front view page UID
			UID UID_page = Utils<ILayoutUIUtils>()->GetCurrentVisiblePage();
			if (UID_page == kInvalidUID) break;

			// Get front document
			IDocument* iDocument = Utils<ILayoutUIUtils>()->GetFrontDocument();
			if (!iDocument) break;

			// Get front document pageList
			InterfacePtr<IPageList> iPageList(iDocument, ::UseDefaultIID());
			if (!iPageList) break;

			// Get front view page string
			iPageList->GetPageString(UID_page, &pmString_frontViewPageNumber);
		}

		// Get all layout views
		K2Vector<IControlView*> iControlView_layoutViewList;
		Utils<ILayoutViewUtils>()->GetAllLayoutViews(iControlView_layoutViewList, nil, nil);

		for (K2Vector<IControlView*>::const_iterator iter = iControlView_layoutViewList.begin();
			iter != iControlView_layoutViewList.end(); ++iter)
		{
			IControlView* iControlView = *iter;
			if (iControlView == nil) continue;

			InterfacePtr<IPanorama> iPanorama(iControlView, UseDefaultIID());
			if (!iPanorama) continue;

			// Set Page
			{
				InterfacePtr<ICommand> iCommand_setPage(CmdUtils::CreateCommand(kSetPageCmdBoss));

				InterfacePtr<ILayoutControlData> iLayoutControlData(iControlView, ::UseDefaultIID());
				if (!iLayoutControlData) continue;

				IDocument* iDocument = iLayoutControlData->GetDocument();
				if (!iDocument) continue;

				IDataBase* iDataBase = ::GetDataBase(iDocument);
				if (!iDataBase) continue;

				InterfacePtr<IPageList> iPageList(iDocument, ::UseDefaultIID());
				if (!iPageList) continue;

				// Given a page string, returns the UID of the page.
				UID UID_page = iPageList->PageStringToUID(pmString_frontViewPageNumber);
				if (UID_page == kInvalidUID) continue;

				UIDRef UIDRef_page(iDataBase, UID_page);

				InterfacePtr<IHierarchy> iHierarchy(UIDRef_page, ::UseDefaultIID());
				if (!iHierarchy) continue;

				InterfacePtr<ISpread> iSpread(iDataBase, iHierarchy->GetSpreadUID(), ::UseDefaultIID());

				iCommand_setPage->SetItemList(UIDList(iSpread));

				InterfacePtr<ILayoutCmdData> iLayoutCmdData(iCommand_setPage, ::UseDefaultIID());

				iLayoutCmdData->Set(::GetUIDRef(iDocument), iLayoutControlData);

				InterfacePtr<IUIDData> iUIDData(iCommand_setPage, ::UseDefaultIID());

				iUIDData->Set(UIDRef_page);

				CmdUtils::ProcessCommand(iCommand_setPage);
			}

			// Scale
			iPanorama->ScalePanorama(xScale, yScale);

			// Scroll
			iPanorama->ScrollContentLocationToFrameOrigin(pMPoint_frontViewTopLeft);

			status = kSuccess;
		}
	} while (false); // only do once

	return status; // If kSuccess is not returned, an error occurs
}

/* AccessContentLocationAtFrameOrigin
My		ScriptID scriptID,	IScriptRequestData* iScriptRequestData,	IScript* iScript
Sample	ScriptID propID,	IScriptRequestData* data,				IScript* parent

scriptID four-character identifier. defined in KESScriptingDef.h
{ // Check the scriptID
	PMString pMString_scriptID = Utils<IScriptUtils>()->GetScriptID(scriptID);
}

IScript
{ // GetName
	PMString PMString_name = iScript->GetObjectInfo(iScriptRequestData->GetRequestContext())->GetName();
}
*/
ErrorCode KESLayout::AccessContentLocationAtFrameOrigin
	(ScriptID scriptID, IScriptRequestData* iScriptRequestData, IScript* iScript, std::string flgXY)
{
	ErrorCode status = kFailure;

	do
	{
		InterfacePtr<IPanelControlData> iPanelControlData(iScript, ::UseDefaultIID());
		if (!iPanelControlData) break;

		// kLayoutWidgetBoss is a BOSS representing a layout view.
		IControlView* iControlView = iPanelControlData->FindWidget(kLayoutWidgetBoss);
		if (!iControlView) break;

		// Get put content location at frame origin.
		status = KESLayout::GetPutContentLocationAtFrameOrigin
			(scriptID, iScriptRequestData, iScript, flgXY, iControlView);

	} while (false); // only do once.

	return status; // If kSuccess is not returned, an error occurs.
}

// Toggle split layout.
ErrorCode KESLayout::ToggleSplitLayout(IScript* iScript)
{
	ErrorCode status = kFailure;

	do
	{
		InterfacePtr<IDocumentPresentation> iDocumentPresentation(iScript, ::UseDefaultIID());
		if (!iDocumentPresentation) break;

		// Toggle split layout view.
		Utils<ILayoutViewUtils>()->ToggleSplitLayoutView(iDocumentPresentation);

		status = kSuccess;

	} while (false); // only do once.

	return status; // If kSuccess is not returned, an error occurs.
}

// Query Nth layout.
ErrorCode KESLayout::QueryNthLayout(ScriptID scriptID, IScriptRequestData* iScriptRequestData, IScript* iScript)
{
	ErrorCode status = kFailure;

	do
	{
		ScriptData scriptData;

		// Get argument
		int32 int32_nthNum;
		{
			status = iScriptRequestData->ExtractRequestData(KESScriptProperties::p_KESNthLayoutIndex, scriptData);
			if (status != kSuccess) break;

			status = scriptData.GetInt32(&int32_nthNum);
			if (status != kSuccess) break;
		}

		// Get Nth IDocumentPresentation.
		IDocumentPresentation* iDocumentPresentation_nth = nil;
		{
			InterfacePtr<IDocument> iDocument(Utils<IScriptUtils>()->
				QueryDocumentFromScript(iScript, iScriptRequestData->GetRequestContext()));
			if (!iDocument) break;

			InterfacePtr<IPresentationList> iPresentationList(iDocument, ::UseDefaultIID());
			if (iPresentationList->size() == 0) break;

			iDocumentPresentation_nth = iPresentationList->At(int32_nthNum);
			if (!iDocumentPresentation_nth) break;
		}

		InterfacePtr<IScript> iScript_window(iDocumentPresentation_nth, ::UseDefaultIID());

		ScriptData scriptData_return;
		scriptData_return.SetObject(iScript_window);

		iScriptRequestData->AppendReturnData(iScript, scriptID, scriptData_return);

		status = kSuccess;

	} while (false); // only do once

	return status; // If kSuccess is not returned, an error occurs
}

// Get put content location at frame origin.
ErrorCode KESLayout::GetPutContentLocationAtFrameOrigin
	(ScriptID scriptID, IScriptRequestData* iScriptRequestData, IScript* iScript, std::string flgXY, IControlView* iControlView)
{
	ErrorCode status = kFailure;

	do
	{
		InterfacePtr<IPanorama> iPanorama(iControlView, ::UseDefaultIID());
		if (!iPanorama) break;

		// Get top-left position
		PMPoint pMPoint_viewTopLeft = iPanorama->GetContentLocationAtFrameOrigin();

		// Request
		ScriptData scriptData;
		if (iScriptRequestData->IsPropertyGet())
		{
			if (flgXY == "X")
			{
				scriptData.SetPMReal(pMPoint_viewTopLeft.X());
			}
			else if (flgXY == "Y")
			{
				scriptData.SetPMReal(pMPoint_viewTopLeft.Y());
			}

			iScriptRequestData->AppendReturnData(iScript, scriptID, scriptData);

			status = kSuccess;
		}
		else if (iScriptRequestData->IsPropertyPut())
		{
			status = iScriptRequestData->ExtractRequestData(scriptID.Get(), scriptData);
			if (status != kSuccess) break;

			PMReal pMReal_point;
			status = scriptData.GetPMReal(&pMReal_point);
			if (status != kSuccess) break;

			if (flgXY == "X")
			{
				pMPoint_viewTopLeft.X(pMReal_point);
			}
			else if (flgXY == "Y")
			{
				pMPoint_viewTopLeft.Y(pMReal_point);
			}

			// Scroll
			iPanorama->ScrollContentLocationToFrameOrigin(pMPoint_viewTopLeft);

			status = kSuccess;
		}
	} while (false); // only do once

	return status; // If kSuccess is not returned, an error occurs
}

// Is split layout view shown.
ErrorCode KESLayout::IsSplitLayoutViewShown(ScriptID scriptID, IScriptRequestData* iScriptRequestData, IScript* iScript)
{
	ErrorCode status = kFailure;

	do
	{
		InterfacePtr<IDocumentPresentation> iDocumentPresentation(iScript, ::UseDefaultIID());
		if (!iDocumentPresentation) break;

		bool16 bool16_result = Utils<ILayoutViewUtils>()->IsSplitLayoutViewShown(iDocumentPresentation);

		ScriptData scriptData;

		scriptData.SetBoolean(bool16_result);

		iScriptRequestData->AppendReturnData(iScript, scriptID, scriptData);

		status = kSuccess;
	} while (false); // only do once

	return status; // If kSuccess is not returned, an error occurs
}
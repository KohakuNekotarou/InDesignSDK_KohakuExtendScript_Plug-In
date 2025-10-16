#include "VCPlugInHeaders.h" // Visual Studio only?
#include "KESLayout.h"

// ---------------------------------------------------------------------------------------
// Interface includes:
/** IApplication
IApplication is similar to ISession,
and holds all the app-specific and UI-specific information on the current session (kSessionBoss).
���݂̃Z�b�V���� (kSessionBoss) �Ɋւ���A�v���ŗL����� UI �ŗL�̂��ׂĂ̏���ێ����܂�
The application object (kAppBoss) 
also manages and provides access to the global event loop (via its interface IEventDispatcher).
�A�v���P�[�V���� �I�u�W�F�N�g (kAppBoss) �́A
�O���[�o�� �C�x���g ���[�v�� (�C���^�[�t�F�C�X IEventDispatcher �����) �Ǘ����A�A�N�Z�X���񋟂��܂��B
*/
#include "IApplication.h"

/** IControlView
Interface responsible for determining the visual appearance of widgets. 
�E�B�W�F�b�g�̎��o�I�ȊO�ς����肷�������S���C���^�[�t�F�C�X�B
Handles drawing in various states. 
���܂��܂ȏ�Ԃł̕`����������܂��B
Also involved in hit testing and Auto attaching/detaching observers.
�q�b�g�e�X�g��I�u�U�[�o�[�̎������E�ɂ��֗^���Ă��܂��B
*/
#include "IControlView.h"

/** IControlViewCmdData
*/
#include "IControlViewCmdData.h"

/** ICommand
commands are used to modify objects that persist in an InDesign database that supports undo. 
�R�}���h�́A���ɖ߂����T�|�[�g���� InDesign �f�[�^�x�[�X�ɕێ������I�u�W�F�N�g��ύX���邽�߂Ɏg�p����܂�
*/
#include "ICommand.h"

/** IDataBase
A database is the underlying data structure used for storage of documents, preferences, books, etc.
�f�[�^�x�[�X�́A�h�L�������g�A�ݒ�A���ЂȂǂ̕ۑ��Ɏg�p������b�ƂȂ�f�[�^�\���ł��B
It handles allocation, serialization, deletion of objects in the files.
�t�@�C�����̃I�u�W�F�N�g�̊��蓖�āA�V���A�����A�폜���������܂��B
It also handles caching of objects.
�܂��A�I�u�W�F�N�g�̃L���b�V�����������܂��B
*/
#include "IDataBase.h"

/** IDocument
Represents an InDesign publication. Provides the basic file operations. 
InDesign ������\���܂��B��{�I�ȃt�@�C�������񋟂��܂��B
*/
#include "IDocument.h"

/** IDocumentList
store a list of open documents.
�J���Ă���h�L�������g�̃��X�g���i�[����܂��B
*/
#include "IDocumentList.h"

/** IDocumentPresentation
represents a view onto a document, and exists on the document presentation boss,
along with IActiveContext, to designate an InDesign document presentation.
�h�L�������g��̃r���[��\���AInDesign �h�L�������g�v���[���e�[�V�������w�肷�邽�߂�
IActiveContext�Ƌ��Ƀh�L�������g�v���[���e�[�V���� �{�X�ɑ��݂��܂��B
*/
#include "IDocumentPresentation.h"

/** IGalleyUtils
an aggregrate of many different utility functions centered around the document window and galley sub window.
�h�L�������g �E�B���h�E�ƃM�����[ �T�u �E�B���h�E�𒆐S�Ƃ������܂��܂ȃ��[�e�B���e�B�֐��̏W���̂ł��B
*/
#include "IGalleyUtils.h"

/** IHierarchy
stores a persistent, UID-based tree structure. This tree structure is used for InDesign's display hierarchy.
�i���I�� UID �x�[�X�̃c���[�\�����i�[����܂��B���̃c���[�\���́AInDesign �̕\���K�w�Ɏg�p����܂��B
*/
#include "IHierarchy.h"

/** ILayoutControlData
Data interface for the Layout Widget.
���C�A�E�g�E�B�W�F�b�g�̃f�[�^�C���^�[�t�F�[�X�B
Provides access to the spread, document, and currently installed selection.
���J���A�h�L�������g�A����ь��݃C���X�g�[������Ă���I��͈͂ւ̃A�N�Z�X��񋟂��܂��B
*/
#include "ILayoutControlData.h"

/** ILayoutCmdData
Command data interface used to pass layout data information to various commands.
���C�A�E�g�f�[�^�����e��R�}���h�ɓn�����߂̃R�}���h�f�[�^�C���^�t�F�[�X
*/
#include "ILayoutCmdData.h"

/** ILayoutUIUtils
UI Layout-related utilities
UI ���C�A�E�g�֘A�̃��[�e�B���e�B
*/
#include "ILayoutUIUtils.h"

/** ILayoutViewUtils
Layout-view related utilities
���C�A�E�g�r���[�֘A�̃��[�e�B���e�B
*/
#include "ILayoutViewUtils.h"

/** IPageList
which caches commonly needed information about pages in the document. 
�h�L�������g���̃y�[�W�Ɋւ��Ĉ�ʓI�ɕK�v�ȏ����L���b�V�����܂��B
*/
#include "IPageList.h"

/** IPanelControlData
Interface that container widgets implement.
�R���e�i�E�B�W�F�b�g����������C���^�[�t�F�[�X
*/
#include "IPanelControlData.h"

/** IPanorama
Interface used to manage views that can scroll.
�X�N���[���ł���r���[���Ǘ����邽�߂Ɏg�p�����C���^�[�t�F�C�X�B
*/
#include "IPanorama.h"

/** IPresentationList
unordered list of document presentations. 
�h�L�������g�v���[���e�[�V�����̏����t������Ă��Ȃ����X�g��ێ����܂��B
*/
#include "IPresentationList.h"

/** IScript
Added to any boss that wants to be visible as an object in the scripting architecture
and thus available to any scripting client.
�X�N���v�g�A�[�L�e�N�`���ŃI�u�W�F�N�g�Ƃ��ĕ\����
�X�N���v�g�N���C�A���g�Ŏg�p�ł���悤�ɂ���{�X�ɒǉ�����܂��B
*/
#include "IScript.h"

/** IScriptRequestData
Used to pass data into and out of a scripting request.
�X�N���v�g�v���Ƃ̊ԂŃf�[�^������肷�邽�߂Ɏg�p���܂��B
*/
#include "IScriptRequestData.h"

/** IScriptUtils
*/
#include "IScriptUtils.h"

/** ISpread
A spread is the root of all drawable page item's IHierarchies
�X�v���b�h�́A���ׂĂ̕`��\�ȃy�[�W�A�C�e����IHierarchies�̃��[�g�ł�
*/
#include "ISpread.h"

/** IUIDData
Data interface that holds onto a UIDRef that can be used to uniquely describe a persistent object.
�i���I�u�W�F�N�g����ӂɋL�q���邽�߂Ɏg�p�ł���UIDRef��ێ�����f�[�^ �C���^�[�t�F�C�X�ł��B
*/
#include "IUIDData.h"

/** IWidgetParent
Interface to allow traversing widget hierarchy.
�E�B�W�F�b�g�K�w���g���o�[�X�ł���C���^�[�t�F�C�X�B
*/
#include "IWidgetParent.h"

// ---------------------------------------------------------------------------------------
// General includes:
// CAlert
#include "CAlert.h" // CAlert::InformationAlert(Msg);

/** KeyValuePair
KeyValuePair is similar in concept to std::pair.
KeyValuePair �́A�T�O�� std::pair �Ɏ��Ă��܂��B
*/
#include "KeyValuePair.h"

/** ScriptData
Class that can hold any of the data types supported by the scripting architecture.
�X�N���v�g �A�[�L�e�N�`���ŃT�|�[�g����Ă���C�ӂ̃f�[�^�^��ێ��ł���N���X�ł��B
*/
#include "ScriptData.h"

/** Utils
This is a helper class for calling methods in interfaces on the kUtilsBoss.
kUtilsBoss �̃C���^�[�t�F�C�X�Ń��\�b�h���Ăяo�����߂̃w���p�[�N���X�ł��B
Utils<IFooUtils>()->MyFooMethod();
*/
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
	// Using ScriptListData causes errors. Is this a bug?
	ErrorCode status = kFailure;

	do
	{

		/*

		InterfacePtr<IPanelControlData> iPanelControlData(iScript, ::UseDefaultIID());
		if (!iPanelControlData) break;

		// kLayoutWidgetBoss is a BOSS representing a layout view.
		IControlView* iControlView_iScript = iPanelControlData->FindWidget(kLayoutWidgetBoss);
		if (!iControlView_iScript) break;

		InterfacePtr<IDocument> iDocument(Utils<IScriptUtils>()->
			QueryDocumentFromScript(iScript, iScriptRequestData->GetRequestContext()));

		IDataBase* iDataBase = ::GetDataBase(iDocument);
		if (!iDataBase) continue;

		K2Vector<IControlView*> iControlView_layoutViewList;
		Utils<ILayoutViewUtils>()->GetAllLayoutViews(iControlView_layoutViewList, iControlView_iScript, iDataBase);

		for (K2Vector<IControlView*>::const_iterator iter = iControlView_layoutViewList.begin();
			iter != iControlView_layoutViewList.end(); ++iter)
		{
			IControlView* iControlView = *iter;
			if (iControlView == nil) continue;

			InterfacePtr<IWidgetParent> iWidgetParent(iControlView, UseDefaultIID());
			if (!iWidgetParent) break;

			InterfacePtr<IDocumentPresentation> iDocumentPresentation((IDocumentPresentation*)iWidgetParent->
				QueryParentFor(IID_IDOCUMENTPRESENTATION));
			if (!iDocumentPresentation) break;

			if(iDocumentPresentation_iScript == iDocumentPresentation)
			{
				iControlView_target = iControlView;
				break;
			}
		}

		*/


	


		

		InterfacePtr<IPanelControlData> iPanelControlData2(iScript, ::UseDefaultIID());
		if (!iPanelControlData2) break;

		// kLayoutWidgetBoss is a BOSS representing a layout view.
		IControlView* iControlView2 = iPanelControlData2->FindWidget(kLayoutWidgetBoss);
		if (!iControlView2) break;

		InterfacePtr<IPanorama> iPanorama(iControlView2, ::UseDefaultIID());
		if (!iPanorama) continue;

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

	} while (false); // only do once

	return status; // If kSuccess is not returned, an error occurs
}

// Query Nth layout.
ErrorCode  KESLayout::QueryNthLayout(ScriptID scriptID, IScriptRequestData* iScriptRequestData, IScript* iScript)
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
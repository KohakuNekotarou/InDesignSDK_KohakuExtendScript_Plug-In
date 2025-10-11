#include "VCPlugInHeaders.h" // Visual Studio only?
#include "KESLayoutScrool.h"

#include <string>

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

// General includes:
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

/* MatchScrollZoomAllLayout */
ErrorCode KESLayoutScrool::MatchScrollZoomAllLayout()
{
	ErrorCode status = kFailure;
	do
	{
		// Get front layout view
		InterfacePtr<IControlView> iControlView_frontView(Utils<ILayoutUIUtils>()->QueryFrontView());
		if (!iControlView_frontView) return kSuccess;

		// Panorama handles the control of content position, scale, and scrolling within the view's display area
		InterfacePtr<IPanorama> iPanorama_frontView(iControlView_frontView, ::UseDefaultIID());
		if (!iPanorama_frontView) return status;

		// Get top-left position
		PMPoint pMPoint_frontViewTopLeft = iPanorama_frontView->GetContentLocationAtFrameOrigin();

		// Get scale
		PMReal xScale = iPanorama_frontView->GetXScaleFactor();
		PMReal yScale = iPanorama_frontView->GetYScaleFactor();

		// Get frontViewPageNumber
		PMString pmString_frontViewPageNumber;
		do
		{	
			// Get front page UID
			UID UID_page; 
			InterfacePtr<ILayoutControlData> iLayoutControlData(iControlView_frontView, ::UseDefaultIID());
			if (!iLayoutControlData) break;
			UID_page = iLayoutControlData->GetPage();

			// Get front document
			IDocument* iDocument = Utils<ILayoutUIUtils>()->GetFrontDocument();
			if (!iDocument) break;

			// Get front document pageList
			InterfacePtr<IPageList> iPageList(iDocument, ::UseDefaultIID());
			if (!iPageList) break;

			// Get front view page string
			iPageList->GetPageString(UID_page, &pmString_frontViewPageNumber);
		} while (false); // only do once

		// Apply all document
		do
		{
			// GetExecutionContextSession() returns a pointer to the ISession interface aggregated in the kSessionBoss
			InterfacePtr<IApplication> iApplication(GetExecutionContextSession()->QueryApplication());

			// Get document list
			InterfacePtr<IDocumentList> iDocumentList(iApplication->QueryDocumentList());

			for (int32 i = 0; i < iDocumentList->GetDocCount(); i++) {

				IDocument* iDocument = iDocumentList->GetNthDoc(i);

				// The document is presented for edit in the layout presentation.
				InterfacePtr<IPresentationList> iPresentationList(iDocument, ::UseDefaultIID());
				if (iPresentationList->size() == 0) break;

				// Iterate through an IPresentationList.
				for (IPresentationList::iterator iter = iPresentationList->begin(); iter != iPresentationList->end(); ++iter) {
					if (*iter == nil) continue;

					// Galley or Story view.
					if (Utils<IGalleyUtils>() && Utils<IGalleyUtils>()->InGalleyOrStory(*iter)) continue;

					InterfacePtr<IPanelControlData> iPanelControlData(*iter, ::UseDefaultIID());
					if (!iPanelControlData) continue;

					// kLayoutWidgetBoss is a BOSS representing a layout view.
					IControlView* iControlView = iPanelControlData->FindWidget(kLayoutWidgetBoss);
					if (!iControlView) continue;

					InterfacePtr<IPanorama> iPanorama(iControlView, UseDefaultIID());
					if (!iPanorama) continue;

					// Set Page
					{
						InterfacePtr<ICommand> iCommand_setPage(CmdUtils::CreateCommand(kSetPageCmdBoss));

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

						InterfacePtr<ILayoutControlData> iLayoutControlData(iControlView, ::UseDefaultIID());
						if (!iLayoutControlData) continue;

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
			}
		} while (false); // only do once
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
ErrorCode KESLayoutScrool::AccessContentLocationAtFrameOrigin
	(ScriptID scriptID, IScriptRequestData* iScriptRequestData, IScript* iScript, std::string flgXY)
{
	// Using ScriptListData causes errors. Is this a bug?
	ErrorCode status = kFailure;

	do
	{
		ScriptData scriptData;

		// layoutWindowScriptObject == IPanelControlData
		InterfacePtr<IPanelControlData> iPanelControlData(iScript, ::UseDefaultIID());
		if (!iPanelControlData) continue;

		// kLayoutWidgetBoss is a BOSS representing a layout view.
		IControlView* iControlView = iPanelControlData->FindWidget(kLayoutWidgetBoss);
		if (!iControlView) continue;

		InterfacePtr<IPanorama> iPanorama(iControlView, UseDefaultIID());
		if (!iPanorama) continue;

		// Get top-left position
		PMPoint pMPoint_viewTopLeft = iPanorama->GetContentLocationAtFrameOrigin();

		// Request
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
#include "VCPlugInHeaders.h" // Visual Studio only?
#include "KESLayout.h"

// ---------------------------------------------------------------------------------------
// Interface includes:
/** IApplication
IApplication is similar to ISession,
and holds all the app-specific and UI-specific information on the current session (kSessionBoss).
現在のセッション (kSessionBoss) に関するアプリ固有および UI 固有のすべての情報を保持します
The application object (kAppBoss) 
also manages and provides access to the global event loop (via its interface IEventDispatcher).
アプリケーション オブジェクト (kAppBoss) は、
グローバル イベント ループを (インターフェイス IEventDispatcher を介して) 管理し、アクセスも提供します。
*/
#include "IApplication.h"

/** IControlView
Interface responsible for determining the visual appearance of widgets. 
ウィジェットの視覚的な外観を決定する役割を担うインターフェイス。
Handles drawing in various states. 
さまざまな状態での描画を処理します。
Also involved in hit testing and Auto attaching/detaching observers.
ヒットテストやオブザーバーの自動着脱にも関与しています。
*/
#include "IControlView.h"

/** IControlViewCmdData
*/
#include "IControlViewCmdData.h"

/** ICommand
commands are used to modify objects that persist in an InDesign database that supports undo. 
コマンドは、元に戻すをサポートする InDesign データベースに保持されるオブジェクトを変更するために使用されます
*/
#include "ICommand.h"

/** IDataBase
A database is the underlying data structure used for storage of documents, preferences, books, etc.
データベースは、ドキュメント、設定、書籍などの保存に使用される基礎となるデータ構造です。
It handles allocation, serialization, deletion of objects in the files.
ファイル内のオブジェクトの割り当て、シリアル化、削除を処理します。
It also handles caching of objects.
また、オブジェクトのキャッシュも処理します。
*/
#include "IDataBase.h"

/** IDocument
Represents an InDesign publication. Provides the basic file operations. 
InDesign 文書を表します。基本的なファイル操作を提供します。
*/
#include "IDocument.h"

/** IDocumentList
store a list of open documents.
開いているドキュメントのリストが格納されます。
*/
#include "IDocumentList.h"

/** IDocumentPresentation
represents a view onto a document, and exists on the document presentation boss,
along with IActiveContext, to designate an InDesign document presentation.
ドキュメント上のビューを表し、InDesign ドキュメントプレゼンテーションを指定するために
IActiveContextと共にドキュメントプレゼンテーション ボスに存在します。
*/
#include "IDocumentPresentation.h"

/** IGalleyUtils
an aggregrate of many different utility functions centered around the document window and galley sub window.
ドキュメント ウィンドウとギャレー サブ ウィンドウを中心としたさまざまなユーティリティ関数の集合体です。
*/
#include "IGalleyUtils.h"

/** IHierarchy
stores a persistent, UID-based tree structure. This tree structure is used for InDesign's display hierarchy.
永続的な UID ベースのツリー構造が格納されます。このツリー構造は、InDesign の表示階層に使用されます。
*/
#include "IHierarchy.h"

/** ILayoutControlData
Data interface for the Layout Widget.
レイアウトウィジェットのデータインターフェース。
Provides access to the spread, document, and currently installed selection.
見開き、ドキュメント、および現在インストールされている選択範囲へのアクセスを提供します。
*/
#include "ILayoutControlData.h"

/** ILayoutCmdData
Command data interface used to pass layout data information to various commands.
レイアウトデータ情報を各種コマンドに渡すためのコマンドデータインタフェース
*/
#include "ILayoutCmdData.h"

/** ILayoutUIUtils
UI Layout-related utilities
UI レイアウト関連のユーティリティ
*/
#include "ILayoutUIUtils.h"

/** ILayoutViewUtils
Layout-view related utilities
レイアウトビュー関連のユーティリティ
*/
#include "ILayoutViewUtils.h"

/** IPageList
which caches commonly needed information about pages in the document. 
ドキュメント内のページに関して一般的に必要な情報をキャッシュします。
*/
#include "IPageList.h"

/** IPanelControlData
Interface that container widgets implement.
コンテナウィジェットが実装するインターフェース
*/
#include "IPanelControlData.h"

/** IPanorama
Interface used to manage views that can scroll.
スクロールできるビューを管理するために使用されるインターフェイス。
*/
#include "IPanorama.h"

/** IPresentationList
unordered list of document presentations. 
ドキュメントプレゼンテーションの順序付けされていないリストを保持します。
*/
#include "IPresentationList.h"

/** IScript
Added to any boss that wants to be visible as an object in the scripting architecture
and thus available to any scripting client.
スクリプトアーキテクチャでオブジェクトとして表示し
スクリプトクライアントで使用できるようにするボスに追加されます。
*/
#include "IScript.h"

/** IScriptRequestData
Used to pass data into and out of a scripting request.
スクリプト要求との間でデータをやり取りするために使用します。
*/
#include "IScriptRequestData.h"

/** IScriptUtils
*/
#include "IScriptUtils.h"

/** ISpread
A spread is the root of all drawable page item's IHierarchies
スプレッドは、すべての描画可能なページアイテムのIHierarchiesのルートです
*/
#include "ISpread.h"

/** IUIDData
Data interface that holds onto a UIDRef that can be used to uniquely describe a persistent object.
永続オブジェクトを一意に記述するために使用できるUIDRefを保持するデータ インターフェイスです。
*/
#include "IUIDData.h"

/** IWidgetParent
Interface to allow traversing widget hierarchy.
ウィジェット階層をトラバースできるインターフェイス。
*/
#include "IWidgetParent.h"

// ---------------------------------------------------------------------------------------
// General includes:
// CAlert
#include "CAlert.h" // CAlert::InformationAlert(Msg);

/** KeyValuePair
KeyValuePair is similar in concept to std::pair.
KeyValuePair は、概念が std::pair に似ています。
*/
#include "KeyValuePair.h"

/** ScriptData
Class that can hold any of the data types supported by the scripting architecture.
スクリプト アーキテクチャでサポートされている任意のデータ型を保持できるクラスです。
*/
#include "ScriptData.h"

/** Utils
This is a helper class for calling methods in interfaces on the kUtilsBoss.
kUtilsBoss のインターフェイスでメソッドを呼び出すためのヘルパークラスです。
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
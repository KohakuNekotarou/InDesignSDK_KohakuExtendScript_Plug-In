#include "VCPlugInHeaders.h" // Visual Studio only?
#include "KESLayoutScrool.h"

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

/** ILayoutControlData
Data interface for the Layout Widget.
イアウトウィジェットのデータインターフェース。
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

/** ISpread
A spread is the root of all drawable page item's IHierarchies
スプレッドは、すべての描画可能なページアイテムのIHierarchiesのルートです
*/
#include "ISpread.h"

/** IUIDData
data interface that holds onto a UIDRef that can be used to uniquely describe a persistent object.
永続オブジェクトを一意に記述するために使用できるUIDRefを保持するデータ インターフェイスです。
*/
#include "IUIDData.h"

// Constructor
KESLayoutScrool::KESLayoutScrool(ScriptID methodID, IScriptRequestData* data, IScript* parent)
	: scriptID(methodID), iScriptRequestData(data), iScript(parent) {}

// MatchScrollZoomAllLayout
ErrorCode KESLayoutScrool::MatchScrollZoomAllLayout()
{
	// Get front layout view
	InterfacePtr<IControlView> iControlView_frontView(Utils<ILayoutUIUtils>()->QueryFrontView());
	if (!iControlView_frontView) return kSuccess;

	// Get front document
	IDocument* iDocument_frontDocument = Utils<ILayoutUIUtils>()->GetFrontDocument();
	if (!iDocument_frontDocument) return kSuccess;

	// Panorama handles the control of content position, scale, and scrolling within the view's display area
	InterfacePtr<IPanorama> iPanorama_frontView(iControlView_frontView, ::UseDefaultIID());
	if (!iPanorama_frontView) return kSuccess;

	// Get top-left position
	PMPoint frontView_topLeft = iPanorama_frontView->GetContentLocationAtFrameOrigin();

	// Get scale
	PMReal xScale = iPanorama_frontView->GetXScaleFactor();
	PMReal yScale = iPanorama_frontView->GetYScaleFactor();

	// Get frontViewPageNumber
	PMString pmString_frontViewPageNumber;
	{
		// Get front view page UID
		UID UID_frontViewPag; 
		{
			InterfacePtr<ILayoutControlData> iLayoutControlData_frontView(iControlView_frontView, ::UseDefaultIID());
			if (!iLayoutControlData_frontView) return kSuccess;

			UID_frontViewPag = iLayoutControlData_frontView->GetPage();
		}

		// Get front document pageList
		InterfacePtr<IPageList> iPageList_frontDocument(iDocument_frontDocument, ::UseDefaultIID());
		if (!iPageList_frontDocument) return kSuccess;

		// Get front view page string
		iPageList_frontDocument->GetPageString(UID_frontViewPag, &pmString_frontViewPageNumber);
	}

	// GetExecutionContextSession() returns a pointer to the ISession interface aggregated in the kSessionBoss
	InterfacePtr<IApplication> iApplication(GetExecutionContextSession()->QueryApplication());

	// Get document list
	InterfacePtr<IDocumentList> iDocumentList(iApplication->QueryDocumentList());

	for (int32 i = 0; i < iDocumentList->GetDocCount(); i++) {

		IDocument* iDocument = iDocumentList->GetNthDoc(i);

		// The document is presented for edit in the layout presentation.
		InterfacePtr<IPresentationList> iPresentationList(iDocument, ::UseDefaultIID());
		if (iPresentationList->size() == 0) continue;

		// Iterate through an IPresentationList.
		for (IPresentationList::iterator iter = iPresentationList->begin(); iter != iPresentationList->end(); ++iter) {
			if (*iter == nil) continue;

			// Galley or Story view.
			if (Utils<IGalleyUtils>() && Utils<IGalleyUtils>()->InGalleyOrStory(*iter)) continue;

			InterfacePtr<IPanelControlData> iPanelControlData(*iter, ::UseDefaultIID());
			if (!iPanelControlData) continue;

			// kLayoutWidgetBoss is a BOSS representing a layout view.
			IControlView* iControlView_layoutView = iPanelControlData->FindWidget(kLayoutWidgetBoss);
			if (!iControlView_layoutView) continue;

			InterfacePtr<IPanorama> iPanorama_layoutView(iControlView_layoutView, UseDefaultIID());
			if (!iPanorama_layoutView) break;

			// Set Page
			{
				InterfacePtr<ICommand> iCommand_setPage(CmdUtils::CreateCommand(kSetPageCmdBoss));

				IDataBase* iDataBase = ::GetDataBase(iDocument);
				if (!iDataBase) break;

				InterfacePtr<IPageList> iPageList(iDocument, ::UseDefaultIID());
				if (!iPageList) break;

				// Given a page string, returns the UID of the page.
				UID UID_page = iPageList->PageStringToUID(pmString_frontViewPageNumber);
				if (UID_page == kInvalidUID) break;

				UIDRef UIDRef_page(iDataBase, UID_page);

				InterfacePtr<IHierarchy> iHierarchy(UIDRef_page, ::UseDefaultIID());
				if (!iHierarchy) break;

				InterfacePtr<ISpread> iSpread(iDataBase, iHierarchy->GetSpreadUID(), ::UseDefaultIID());

				iCommand_setPage->SetItemList(UIDList(iSpread));

				InterfacePtr<ILayoutCmdData> iLayoutCmdData(iCommand_setPage, ::UseDefaultIID());

				InterfacePtr<ILayoutControlData> iLayoutControlData(iControlView_layoutView, ::UseDefaultIID());
				if (!iLayoutControlData) break;

				iLayoutCmdData->Set(::GetUIDRef(iDocument), iLayoutControlData);

				InterfacePtr<IUIDData> iUIDData(iCommand_setPage, ::UseDefaultIID());

				iUIDData->Set(UIDRef_page);

				CmdUtils::ProcessCommand(iCommand_setPage);
			}

			// Scale
			iPanorama_layoutView->ScalePanorama(xScale, yScale);

			// Scroll
			iPanorama_layoutView->ScrollContentLocationToFrameOrigin(frontView_topLeft);

			// Completed
			break;
		}
	}

	return kSuccess; // If kSuccess is not returned, an error occurs
}
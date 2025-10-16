
#include "VCPlugInHeaders.h"

// Interface includes:
#include "IControlView.h"
#include "IDataBase.h"
#include "IDocument.h"
#include "IDocumentPresentation.h"
#include "ILayoutViewUtils.h"
#include "IPanelControlData.h"
#include "IScript.h"
#include "IScriptRequestData.h"
#include "IScriptUtils.h"
#include "IWidgetParent.h"

// General includes:
#include "CAlert.h" // CAlert::InformationAlert(Msg);
#include "K2Vector.h"
#include "PrefsScriptProvider.h"
#include "ScriptData.h"
#include "widgetid.h"

// Project includes:
#include "KESScriptingDefs.h"
#include "KESID.h"

// PrefsScriptProvider
// Subclass this to add a singleton script object and its properties to the scripting DOM.
// このクラスをサブクラス化して、シングルトンスクリプトオブジェクトとそのプロパティをスクリプティングDOMに追加する。
// A singleton script object has no plural form and does not exist within a collection.
// シングルトンスクリプトオブジェクトは複数形を持たず、コレクション内に存在しません。
class KESPrefsScriptProvider : public PrefsScriptProvider
{
public:
	/**	Constructor
	*/
	KESPrefsScriptProvider(IPMUnknown* boss);

	/**	Destructor
	 */
	~KESPrefsScriptProvider() {}

	/** Called if a provider can handle a property.
	    プロバイダーがプロパティを処理できる場合に呼び出される。
		@param scriptID identifies the ID of the property to handle.
		              処理対象のプロパティのIDを特定します。
		@param iScriptRequestData identifies an interface pointer used to extract data.
		            データを抽出するために使用されるインターフェースポインタを特定する。
		@param script identifies an interface pointer on a script object.
		              スクリプトオブジェクト上のインターフェースポインタを識別します。
	 */
	virtual ErrorCode AccessProperty(ScriptID scriptID, IScriptRequestData* iScriptRequestData, IScript* iScript);

private:

	ErrorCode AccessProperty_SplitLayoutViewObject(ScriptID scriptID, IScriptRequestData* iScriptRequestData, IScript* iScript);
};

/*	Make the implementation available to the application.
*/
CREATE_PMINTERFACE(KESPrefsScriptProvider, kKESPrefsScriptProviderImpl)

//
KESPrefsScriptProvider::KESPrefsScriptProvider(IPMUnknown* boss) : PrefsScriptProvider(boss)
{
	// Enable the base class to recognize scripting objects.
	// 基底クラスにスクリプティングオブジェクトを認識させる。
	// The based will take care of creating a proxy script object when the preference object is accessed.
	// 設定オブジェクトがアクセスされた際に、基底クラスがプロキシスクリプトオブジェクトの作成を処理する。
	DefinePreference(KESScriptClasses::c_KESSplitLayoutViewObject, KESScriptProperties::p_KESSplitLayoutViewObject);
}

//
ErrorCode KESPrefsScriptProvider::AccessProperty(ScriptID scriptID, IScriptRequestData* iScriptRequestData, IScript* iScript)
{
	ErrorCode status = kFailure;
	do {
		switch (scriptID.Get())
		{
		case KESScriptProperties::p_KESAccessContentLocationAtFrameOriginX: // かり
		{
			status = kSuccess;
			break;
		}
		default:
			status = PrefsScriptProvider::AccessProperty(scriptID, iScriptRequestData, iScript);
			break;
		}
	} while (false);

	return status;
}

//
ErrorCode KESPrefsScriptProvider::AccessProperty_SplitLayoutViewObject
	(ScriptID scriptID, IScriptRequestData* iScriptRequestData, IScript* iScript)
{
	ErrorCode status = kFailure;

	do {
		InterfacePtr<IDocumentPresentation> iDocumentPresentation_iScript(iScript, ::UseDefaultIID());
		if (!iDocumentPresentation_iScript) break;

		// Is the secondary layout widget displayed?
		if (Utils<ILayoutViewUtils>()->IsSplitLayoutViewShown(iDocumentPresentation_iScript) != kTrue)
			return kSuccess; // Error handling.




		// ----------------------------------------------------

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

		IControlView* iControlView_splitLayoutView = nil;
		for (K2Vector<IControlView*>::const_iterator iter = iControlView_layoutViewList.begin();
			iter != iControlView_layoutViewList.end(); ++iter)
		{
			IControlView* iControlView = *iter;
			if (iControlView == nil) continue;

			InterfacePtr<IWidgetParent> iWidgetParent(iControlView, ::UseDefaultIID());
			if (!iWidgetParent) break;

			InterfacePtr<IDocumentPresentation> iDocumentPresentation((IDocumentPresentation*)iWidgetParent->
				QueryParentFor(IID_IDOCUMENTPRESENTATION));
			if (!iDocumentPresentation) break;

			if (iDocumentPresentation_iScript == iDocumentPresentation)
			{
				iControlView_splitLayoutView = iControlView;
				break;
			}
		}






		InterfacePtr<IScript> iScript_splitLayoutView(iControlView_splitLayoutView, ::UseDefaultIID());








		ScriptData returnData;
		returnData.SetObject(iScript_splitLayoutView);

		iScriptRequestData->AppendReturnData(iScript, scriptID, returnData);

		status = kSuccess;

	} while (false);

	return status;
}
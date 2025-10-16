
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
// ���̃N���X���T�u�N���X�����āA�V���O���g���X�N���v�g�I�u�W�F�N�g�Ƃ��̃v���p�e�B���X�N���v�e�B���ODOM�ɒǉ�����B
// A singleton script object has no plural form and does not exist within a collection.
// �V���O���g���X�N���v�g�I�u�W�F�N�g�͕����`���������A�R���N�V�������ɑ��݂��܂���B
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
	    �v���o�C�_�[���v���p�e�B�������ł���ꍇ�ɌĂяo�����B
		@param scriptID identifies the ID of the property to handle.
		              �����Ώۂ̃v���p�e�B��ID����肵�܂��B
		@param iScriptRequestData identifies an interface pointer used to extract data.
		            �f�[�^�𒊏o���邽�߂Ɏg�p�����C���^�[�t�F�[�X�|�C���^����肷��B
		@param script identifies an interface pointer on a script object.
		              �X�N���v�g�I�u�W�F�N�g��̃C���^�[�t�F�[�X�|�C���^�����ʂ��܂��B
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
	// ���N���X�ɃX�N���v�e�B���O�I�u�W�F�N�g��F��������B
	// The based will take care of creating a proxy script object when the preference object is accessed.
	// �ݒ�I�u�W�F�N�g���A�N�Z�X���ꂽ�ۂɁA���N���X���v���L�V�X�N���v�g�I�u�W�F�N�g�̍쐬����������B
	DefinePreference(KESScriptClasses::c_KESSplitLayoutViewObject, KESScriptProperties::p_KESSplitLayoutViewObject);
}

//
ErrorCode KESPrefsScriptProvider::AccessProperty(ScriptID scriptID, IScriptRequestData* iScriptRequestData, IScript* iScript)
{
	ErrorCode status = kFailure;
	do {
		switch (scriptID.Get())
		{
		case KESScriptProperties::p_KESAccessContentLocationAtFrameOriginX: // ����
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

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
#include "KESLayout.h"

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

	// Access SplitLayoutView top-left coordinates of the layout Window.
	static ErrorCode SplitLayoutViewAccessContentLocationAtFrameOrigin
	(ScriptID scriptID, IScriptRequestData* iScriptRequestData, IScript* iScript, std::string flgXY);
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
		case KESScriptProperties::p_KESSplitLayoutViewAccessContentLocationAtFrameOriginX:
			status = this->SplitLayoutViewAccessContentLocationAtFrameOrigin(scriptID, iScriptRequestData, iScript, "X");
			break;

		case KESScriptProperties::p_KESSplitLayoutViewAccessContentLocationAtFrameOriginY:
			status = this->SplitLayoutViewAccessContentLocationAtFrameOrigin(scriptID, iScriptRequestData, iScript, "Y");
			break;
		default:
			status = PrefsScriptProvider::AccessProperty(scriptID, iScriptRequestData, iScript);
			break;
		}
	} while (false);

	return status;
}

ErrorCode KESPrefsScriptProvider::SplitLayoutViewAccessContentLocationAtFrameOrigin
(ScriptID scriptID, IScriptRequestData* iScriptRequestData, IScript* iScript, std::string flgXY)
{
	ErrorCode status = kFailure;
	do {
		// Query parent(layout window).
		InterfacePtr<IScript> iScript_parent((IScript*)iScript->
			QueryParent(IScript::kDefaultIID, iScriptRequestData->GetRequestContext()));
		if (!iScript_parent) break;

		InterfacePtr<IDocumentPresentation> iDocumentPresentation_parent(iScript_parent, ::UseDefaultIID());
		if (!iDocumentPresentation_parent) break;

		// Is the secondary layout widget displayed?
		if (Utils<ILayoutViewUtils>()->
			IsSplitLayoutViewShown(iDocumentPresentation_parent) != kTrue) break;

		// Get SplitLayoutView
		IControlView* iControlView_SplitLayout = nil;
		{
			InterfacePtr<IPanelControlData> iPanelControlData(iScript_parent, ::UseDefaultIID());
			if (!iPanelControlData) break;

			// kLayoutWidgetBoss is a BOSS representing a layout view.
			IControlView* iControlView_iScript = iPanelControlData->FindWidget(kLayoutWidgetBoss);
			if (!iControlView_iScript) break;

			InterfacePtr<IDocument> iDocument(Utils<IScriptUtils>()->
				QueryDocumentFromScript(iScript_parent, iScriptRequestData->GetRequestContext()));

			IDataBase* iDataBase = ::GetDataBase(iDocument);
			if (!iDataBase) break;

			K2Vector<IControlView*> iControlView_layoutViewList;
			Utils<ILayoutViewUtils>()->GetAllLayoutViews(iControlView_layoutViewList, iControlView_iScript, iDataBase);

			for (K2Vector<IControlView*>::const_iterator iter = iControlView_layoutViewList.begin();
				iter != iControlView_layoutViewList.end(); ++iter)
			{
				IControlView* iControlView = *iter;
				if (iControlView == nil) continue;

				InterfacePtr<IWidgetParent> iWidgetParent(iControlView, UseDefaultIID());
				if (!iWidgetParent) continue;

				InterfacePtr<IDocumentPresentation> iDocumentPresentation((IDocumentPresentation*)iWidgetParent->
					QueryParentFor(IID_IDOCUMENTPRESENTATION));
				if (!iDocumentPresentation) continue;

				if (iDocumentPresentation_parent == iDocumentPresentation)
				{
					iControlView_SplitLayout = iControlView;
					break;
				}
			}
			if (!iControlView_SplitLayout) break;
		}

		// Get put content location at frame origin.
		status = KESLayout::GetPutContentLocationAtFrameOrigin
			(scriptID, iScriptRequestData, iScript, flgXY, iControlView_SplitLayout);

	} while (false);

	return status;
}
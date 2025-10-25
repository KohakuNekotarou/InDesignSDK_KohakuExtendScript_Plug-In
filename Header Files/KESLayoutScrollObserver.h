#pragma once

// Implem includes
#include "CObserver.h"

// Layout scrollBar observer.
class KESLayoutScrollObserver : public CObserver
{
public:
	// Constructor.
	KESLayoutScrollObserver(IPMUnknown* boss);

	// Destructor.
	~KESLayoutScrollObserver();

	// Update
	// Regular notification of a change in an observed subject.
	// �ώ@�Ώۂ̕ύX�����I�ɒʒm����B
	// This method is called immediately after the change is made, it is not called on undo or redo.
	// ���̃��\�b�h�͕ύX���s��ꂽ����ɌĂяo����A���ɖ߂������A��蒼������ł͌Ăяo����Ȃ��B
	virtual void Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy);

	// LazyUpdate
	// Lazy notification of a change in an observed subject.
	// �Ď��Ώۂ̕ύX��x���ʒm����B
	// This method is called after the transaction in which the change was performed completes and after undo or redo.
	// ���̃��\�b�h�́A�ύX���s��ꂽ�g�����U�N�V�������������ɌĂяo����
	// ���ɖ߂������A��蒼�����삪�s��ꂽ��ɂ��Ăяo�����B
	void LazyUpdate(ISubject* iSubject, const PMIID& protocol, const LazyNotificationData* data);

	// Match scroll zoom all layout.
	static ErrorCode AutoMatchScrollZoomAllLayout
	(ScriptID scriptID, IScriptRequestData* iScriptRequestData, IScript* iScript);

private:
	// Attach document first layout panorama.
	static void AttachDocumentFirstLayoutPanorama();

	// Attach panorama.
	static void AttachPanorama(IActiveContext* iActiveContext, IControlView* iControlView);

	// Detach all panorama.
	static void DetachAllPanorama(IActiveContext* iActiveContext);
};
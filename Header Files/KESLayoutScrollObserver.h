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
	// 観察対象の変更を定期的に通知する。
	// This method is called immediately after the change is made, it is not called on undo or redo.
	// このメソッドは変更が行われた直後に呼び出され、元に戻す操作や、やり直し操作では呼び出されない。
	virtual void Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy);

	// LazyUpdate
	// Lazy notification of a change in an observed subject.
	// 監視対象の変更を遅延通知する。
	// This method is called after the transaction in which the change was performed completes and after undo or redo.
	// このメソッドは、変更が行われたトランザクションが完了時に呼び出され
	// 元に戻す操作や、やり直し操作が行われた後にも呼び出される。
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
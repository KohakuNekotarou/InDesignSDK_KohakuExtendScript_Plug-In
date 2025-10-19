//========================================================================================
//  
//  $File$
//  
//  Owner: Adobe Developer Technologies
#pragma once

// Interface includes
#include "ISubject.h"

// Implem includes
#include "CObserver.h"

// Layout scrollBar observer.
// Monitor the active context and attach a new observer to monitor the control bar when a new layout window is opened.
class KESLayoutScrollBarObserver : public CObserver
{
public:
	// Constructor.
	KESLayoutScrollBarObserver(IPMUnknown *boss);

	// Destructor.
	~KESLayoutScrollBarObserver();


	virtual void Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy);

	void LazyUpdate(ISubject* iSubject, const PMIID& protocol, const LazyNotificationData* data);

	// Match scroll zoom all layout attach.
	static ErrorCode AutoMatchScrollZoomAllLayout
		(ScriptID scriptID, IScriptRequestData* iScriptRequestData, IScript* iScript);
};
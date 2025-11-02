//========================================================================================
//  
//  $File: $
//  
//  Owner: 
//  
//  $Author: $
//  
//  $DateTime: $
//  
//  $Revision: $
//  
//  $Change: $
//  
//  Copyright 1997-2012 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

// Allows you to register the implementation IDs for your C++ implementations in the InDesign object model.
// InDesign オブジェクトモデル内で、C++ 実装の実装 ID を登録できるようにします。
REGISTER_PMINTERFACE(KESScriptProvider, kKESScriptProviderImpl)
REGISTER_PMINTERFACE(KESLayoutScrollObserver, kKESLayoutScrollObserverImpl)
REGISTER_PMINTERFACE(KESActionComponent, kKESActionComponentImpl)
REGISTER_PMINTERFACE(KESRepresentScriptProvider, kKESRepresentScriptProviderImpl)
REGISTER_PMINTERFACE(KESShortcutScript, kKESShortcutScriptImpl)
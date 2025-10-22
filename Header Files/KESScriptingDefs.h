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


#ifndef __KESScriptingDefs_h__
#define __KESScriptingDefs_h__

#define kCPrefs_CLSID { 0x8d448fe0, 0x8194, 0x11d3, { 0xa6, 0x53, 0x0, 0xe0, 0x98, 0x71, 0xa, 0x6f } }
DECLARE_GUID(CPrefs_CLSID, kCPrefs_CLSID);

// Note: 4-char IDs below must be unique.
// See ScriptingDefs.h for further information.

// Class ScriptIDs 
enum KESScriptClasses
{
	c_KESSplitLayoutViewObject = 'KSLO', // object
};

// Method IDs
enum KESScriptEvents
{
	e_KESMatchScrollZoomAllLayout = 'KMSL',
	e_KESToggleSplitLayout = 'KTSL',
	e_KESQueryNthLayout = 'KQNL',
	e_KESIsSplitLayoutViewShown = 'KISL',
	e_KESSetKeyboardShortcutForStyle = 'KSSS',
};


// Property IDs
enum KESScriptProperties
{
	p_KESAccessContentLocationAtFrameOriginX = 'KALX',
	p_KESAccessContentLocationAtFrameOriginY = 'KALY',
	p_KESSplitLayoutViewObject = 'KSLP',
	p_KESNthLayoutIndex = 'KNLI',
	p_KESSplitLayoutViewAccessContentLocationAtFrameOriginX = 'KSLX',
	p_KESSplitLayoutViewAccessContentLocationAtFrameOriginY = 'KSLY',
	p_KESAutoMatchScrollZoomAllLayout = 'KAML',
	p_KESCKey = 'KKEY',
	p_KESCModifier = 'KMOD',
};

enum KESScriptEnum
{
	en_KESModifier = 'KMDI',
	en_KESNo = 'KNOO',
	en_KESControl = 'KCTL',
	en_KESShift = 'KSFT',
	en_KESAltOrOption = 'KALT',
	en_KESControlShift = 'KCTS',
	en_KESControlAltOrOption = 'KCTA',
	en_KESShiftAltOrOption = 'KSFA',
	en_KESControlShiftAltOrOption = 'KCSA',
};

#endif // __KESScriptingDefs_h__

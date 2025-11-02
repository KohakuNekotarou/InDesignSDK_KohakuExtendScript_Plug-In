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


#ifndef __KESID_h__
#define __KESID_h__

#include "SDKDef.h"

// Company:
#define kKESCompanyKey	kSDKDefPlugInCompanyKey		// Company name used internally for menu paths and the like. Must be globally unique, only A-Z, 0-9, space and "_".
#define kKESCompanyValue	kSDKDefPlugInCompanyValue	// Company name displayed externally.

// Plug-in:
#define kKESPluginName	"KohakuExtendScript"			// Name of this plug-in.
#define kKESPrefixNumber	0xe204291 		// Unique prefix number for this plug-in(*Must* be obtained from Adobe Developer Support).
//#define kKESPrefixNumber	0xe9400 		// Unique prefix number for this plug-in(*Must* be obtained from Adobe Developer Support).

#define kKESVersion		kSDKDefPluginVersionString						// Version of this plug-in (for the About Box).
#define kKESAuthor		""					// Author of this plug-in (for the About Box).

// Plug-in Prefix: (please change kKESPrefixNumber above to modify the prefix.)
#define kKESPrefix		RezLong(kKESPrefixNumber)				// The unique numeric prefix for all object model IDs for this plug-in.
#define kKESStringPrefix	SDK_DEF_STRINGIZE(kKESPrefixNumber)	// The string equivalent of the unique prefix number for  this plug-in.

// Missing plug-in: (see ExtraPluginInfo resource)
#define kKESMissingPluginURLValue		kSDKDefPartnersStandardValue_enUS // URL displayed in Missing Plug-in dialog
#define kKESMissingPluginAlertValue	kSDKDefMissingPluginAlertValue // Message displayed in Missing Plug-in dialog - provide a string that instructs user how to solve their missing plug-in problem

// PluginID:
DECLARE_PMID(kPlugInIDSpace, kKESPluginID, kKESPrefix + 0)

// ClassIDs:
DECLARE_PMID(kClassIDSpace, kKESScriptProviderBoss, kKESPrefix + 0)
DECLARE_PMID(kClassIDSpace, kKESRepresentScriptProviderBoss, kKESPrefix + 1)
DECLARE_PMID(kClassIDSpace, kKESShortcutScriptObjectBoss, kKESPrefix + 2)

// InterfaceIDs:
DECLARE_PMID(kInterfaceIDSpace, IID_IKESLayoutScrollObserver, kKESPrefix + 0)

// ImplementationIDs:
// ŽÀ‘•ID
DECLARE_PMID(kImplementationIDSpace, kKESScriptProviderImpl, kKESPrefix + 0 )
DECLARE_PMID(kImplementationIDSpace, kKESLayoutScrollObserverImpl, kKESPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kKESActionComponentImpl, kKESPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kKESRepresentScriptProviderImpl, kKESPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kKESShortcutScriptImpl, kKESPrefix + 4)

// ActionIDs:
DECLARE_PMID(kActionIDSpace, kKESAboutActionID, kKESPrefix + 0)
//DECLARE_PMID(kActionIDSpace, kKESActionID, kKESPrefix + 5)

// WidgetIDs:
//DECLARE_PMID(kWidgetIDSpace, kKESTestTextWidgetID, kKESPrefix + 0)

// Script Element IDs
DECLARE_PMID(kScriptInfoIDSpace, kKESMatchScrollZoomAllLayoutMethodScriptElement, kKESPrefix + 0)
DECLARE_PMID(kScriptInfoIDSpace, kKESAccessContentLocationAtFrameOriginXPropertyScriptElement, kKESPrefix + 1)
DECLARE_PMID(kScriptInfoIDSpace, kKESAccessContentLocationAtFrameOriginYPropertyScriptElement, kKESPrefix + 2)
DECLARE_PMID(kScriptInfoIDSpace, kKESToggleSplitLayoutMethodScriptElement, kKESPrefix + 3)
DECLARE_PMID(kScriptInfoIDSpace, kKESQueryNthLayoutMethodScriptElement, kKESPrefix + 4)
DECLARE_PMID(kScriptInfoIDSpace, kKESIsSplitLayoutViewShownMethodScriptElement, kKESPrefix + 5)
DECLARE_PMID(kScriptInfoIDSpace, kKESAutoMatchScrollZoomAllLayoutPropertyScriptElement, kKESPrefix + 6)
DECLARE_PMID(kScriptInfoIDSpace, kKESKeyboardShortcutForStylePropertyScriptElement, kKESPrefix + 7)
DECLARE_PMID(kScriptInfoIDSpace, kKESRemoveContextShortcutMethodScriptElement, kKESPrefix + 8)
DECLARE_PMID(kScriptInfoIDSpace, kKESShortcutObjectScriptElement, kKESPrefix + 9)

// GUIDs for script objects:
// Visual Studio : Tools > Generate GUID
#define kKESShortcutObject_CLSID { 0xe38993cd, 0x3ab5, 0x4c66, { 0xb4, 0x24, 0xc4, 0xd6, 0x1b, 0xb1, 0x5a, 0x46 } }
#define kKESShortcutsObject_CLSID { 0xe112b5f44, 0xc265, 0x4849, { 0x83, 0x55, 0x61, 0xaf, 0x47, 0xc1, 0xd3, 0x29 } }

// "About Plug-ins" sub-menu:
#define kKESAboutMenuKey			kKESStringPrefix "kKESAboutMenuKey"
#define kKESAboutMenuPath		kSDKDefStandardAboutMenuPath kKESCompanyKey

// "Plug-ins" sub-menu:
#define kKESPluginsMenuKey 		kKESStringPrefix "kKESPluginsMenuKey"
#define kKESPluginsMenuPath		kSDKDefPlugInsStandardMenuPath kKESCompanyKey kSDKDefDelimitMenuPath kKESPluginsMenuKey

// Menu item keys:

// Other StringKeys:
#define kKESAboutBoxStringKey	kKESStringPrefix "kKESAboutBoxStringKey"
#define kKESTargetMenuPath kKESPluginsMenuPath

// Menu item positions:

// Initial data format version numbers
#define kKESFirstMajorFormatNumber  RezLong(1)
#define kKESFirstMinorFormatNumber  RezLong(0)

// Data format version numbers for the PluginVersion resource 
#define kKESCurrentMajorFormatNumber kKESFirstMajorFormatNumber
#define kKESCurrentMinorFormatNumber kKESFirstMinorFormatNumber

#endif // __KESID_h__

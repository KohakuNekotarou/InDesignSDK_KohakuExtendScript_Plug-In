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
DECLARE_PMID(kClassIDSpace, kKESScriptProviderBoss, kKESPrefix + 3)
//DECLARE_PMID(kClassIDSpace, kKESBoss, kKESPrefix + 4)
//DECLARE_PMID(kClassIDSpace, kKESBoss, kKESPrefix + 5)
//DECLARE_PMID(kClassIDSpace, kKESBoss, kKESPrefix + 6)
//DECLARE_PMID(kClassIDSpace, kKESBoss, kKESPrefix + 7)
//DECLARE_PMID(kClassIDSpace, kKESBoss, kKESPrefix + 8)
//DECLARE_PMID(kClassIDSpace, kKESBoss, kKESPrefix + 9)
//DECLARE_PMID(kClassIDSpace, kKESBoss, kKESPrefix + 10)
//DECLARE_PMID(kClassIDSpace, kKESBoss, kKESPrefix + 11)
//DECLARE_PMID(kClassIDSpace, kKESBoss, kKESPrefix + 12)
//DECLARE_PMID(kClassIDSpace, kKESBoss, kKESPrefix + 13)
//DECLARE_PMID(kClassIDSpace, kKESBoss, kKESPrefix + 14)
//DECLARE_PMID(kClassIDSpace, kKESBoss, kKESPrefix + 15)
//DECLARE_PMID(kClassIDSpace, kKESBoss, kKESPrefix + 16)
//DECLARE_PMID(kClassIDSpace, kKESBoss, kKESPrefix + 17)
//DECLARE_PMID(kClassIDSpace, kKESBoss, kKESPrefix + 18)
//DECLARE_PMID(kClassIDSpace, kKESBoss, kKESPrefix + 19)
//DECLARE_PMID(kClassIDSpace, kKESBoss, kKESPrefix + 20)
//DECLARE_PMID(kClassIDSpace, kKESBoss, kKESPrefix + 21)
//DECLARE_PMID(kClassIDSpace, kKESBoss, kKESPrefix + 22)
//DECLARE_PMID(kClassIDSpace, kKESBoss, kKESPrefix + 23)
//DECLARE_PMID(kClassIDSpace, kKESBoss, kKESPrefix + 24)
//DECLARE_PMID(kClassIDSpace, kKESBoss, kKESPrefix + 25)


// InterfaceIDs:
//DECLARE_PMID(kInterfaceIDSpace, IID_IKESINTERFACE, kKESPrefix + 0)
//DECLARE_PMID(kInterfaceIDSpace, IID_IKESINTERFACE, kKESPrefix + 1)
//DECLARE_PMID(kInterfaceIDSpace, IID_IKESINTERFACE, kKESPrefix + 2)
//DECLARE_PMID(kInterfaceIDSpace, IID_IKESINTERFACE, kKESPrefix + 3)
//DECLARE_PMID(kInterfaceIDSpace, IID_IKESINTERFACE, kKESPrefix + 4)
//DECLARE_PMID(kInterfaceIDSpace, IID_IKESINTERFACE, kKESPrefix + 5)
//DECLARE_PMID(kInterfaceIDSpace, IID_IKESINTERFACE, kKESPrefix + 6)
//DECLARE_PMID(kInterfaceIDSpace, IID_IKESINTERFACE, kKESPrefix + 7)
//DECLARE_PMID(kInterfaceIDSpace, IID_IKESINTERFACE, kKESPrefix + 8)
//DECLARE_PMID(kInterfaceIDSpace, IID_IKESINTERFACE, kKESPrefix + 9)
//DECLARE_PMID(kInterfaceIDSpace, IID_IKESINTERFACE, kKESPrefix + 10)
//DECLARE_PMID(kInterfaceIDSpace, IID_IKESINTERFACE, kKESPrefix + 11)
//DECLARE_PMID(kInterfaceIDSpace, IID_IKESINTERFACE, kKESPrefix + 12)
//DECLARE_PMID(kInterfaceIDSpace, IID_IKESINTERFACE, kKESPrefix + 13)
//DECLARE_PMID(kInterfaceIDSpace, IID_IKESINTERFACE, kKESPrefix + 14)
//DECLARE_PMID(kInterfaceIDSpace, IID_IKESINTERFACE, kKESPrefix + 15)
//DECLARE_PMID(kInterfaceIDSpace, IID_IKESINTERFACE, kKESPrefix + 16)
//DECLARE_PMID(kInterfaceIDSpace, IID_IKESINTERFACE, kKESPrefix + 17)
//DECLARE_PMID(kInterfaceIDSpace, IID_IKESINTERFACE, kKESPrefix + 18)
//DECLARE_PMID(kInterfaceIDSpace, IID_IKESINTERFACE, kKESPrefix + 19)
//DECLARE_PMID(kInterfaceIDSpace, IID_IKESINTERFACE, kKESPrefix + 20)
//DECLARE_PMID(kInterfaceIDSpace, IID_IKESINTERFACE, kKESPrefix + 21)
//DECLARE_PMID(kInterfaceIDSpace, IID_IKESINTERFACE, kKESPrefix + 22)
//DECLARE_PMID(kInterfaceIDSpace, IID_IKESINTERFACE, kKESPrefix + 23)
//DECLARE_PMID(kInterfaceIDSpace, IID_IKESINTERFACE, kKESPrefix + 24)
//DECLARE_PMID(kInterfaceIDSpace, IID_IKESINTERFACE, kKESPrefix + 25)


// ImplementationIDs:
DECLARE_PMID(kImplementationIDSpace, kKESScriptProviderImpl, kKESPrefix + 0 )
//DECLARE_PMID(kImplementationIDSpace, kKESImpl, kKESPrefix + 1)
//DECLARE_PMID(kImplementationIDSpace, kKESImpl, kKESPrefix + 2)
//DECLARE_PMID(kImplementationIDSpace, kKESImpl, kKESPrefix + 3)
//DECLARE_PMID(kImplementationIDSpace, kKESImpl, kKESPrefix + 4)
//DECLARE_PMID(kImplementationIDSpace, kKESImpl, kKESPrefix + 5)
//DECLARE_PMID(kImplementationIDSpace, kKESImpl, kKESPrefix + 6)
//DECLARE_PMID(kImplementationIDSpace, kKESImpl, kKESPrefix + 7)
//DECLARE_PMID(kImplementationIDSpace, kKESImpl, kKESPrefix + 8)
//DECLARE_PMID(kImplementationIDSpace, kKESImpl, kKESPrefix + 9)
//DECLARE_PMID(kImplementationIDSpace, kKESImpl, kKESPrefix + 10)
//DECLARE_PMID(kImplementationIDSpace, kKESImpl, kKESPrefix + 11)
//DECLARE_PMID(kImplementationIDSpace, kKESImpl, kKESPrefix + 12)
//DECLARE_PMID(kImplementationIDSpace, kKESImpl, kKESPrefix + 13)
//DECLARE_PMID(kImplementationIDSpace, kKESImpl, kKESPrefix + 14)
//DECLARE_PMID(kImplementationIDSpace, kKESImpl, kKESPrefix + 15)
//DECLARE_PMID(kImplementationIDSpace, kKESImpl, kKESPrefix + 16)
//DECLARE_PMID(kImplementationIDSpace, kKESImpl, kKESPrefix + 17)
//DECLARE_PMID(kImplementationIDSpace, kKESImpl, kKESPrefix + 18)
//DECLARE_PMID(kImplementationIDSpace, kKESImpl, kKESPrefix + 19)
//DECLARE_PMID(kImplementationIDSpace, kKESImpl, kKESPrefix + 20)
//DECLARE_PMID(kImplementationIDSpace, kKESImpl, kKESPrefix + 21)
//DECLARE_PMID(kImplementationIDSpace, kKESImpl, kKESPrefix + 22)
//DECLARE_PMID(kImplementationIDSpace, kKESImpl, kKESPrefix + 23)
//DECLARE_PMID(kImplementationIDSpace, kKESImpl, kKESPrefix + 24)
//DECLARE_PMID(kImplementationIDSpace, kKESImpl, kKESPrefix + 25)


// ActionIDs:
DECLARE_PMID(kActionIDSpace, kKESAboutActionID, kKESPrefix + 0)
//DECLARE_PMID(kActionIDSpace, kKESActionID, kKESPrefix + 5)
//DECLARE_PMID(kActionIDSpace, kKESActionID, kKESPrefix + 6)
//DECLARE_PMID(kActionIDSpace, kKESActionID, kKESPrefix + 7)
//DECLARE_PMID(kActionIDSpace, kKESActionID, kKESPrefix + 8)
//DECLARE_PMID(kActionIDSpace, kKESActionID, kKESPrefix + 9)
//DECLARE_PMID(kActionIDSpace, kKESActionID, kKESPrefix + 10)
//DECLARE_PMID(kActionIDSpace, kKESActionID, kKESPrefix + 11)
//DECLARE_PMID(kActionIDSpace, kKESActionID, kKESPrefix + 12)
//DECLARE_PMID(kActionIDSpace, kKESActionID, kKESPrefix + 13)
//DECLARE_PMID(kActionIDSpace, kKESActionID, kKESPrefix + 14)
//DECLARE_PMID(kActionIDSpace, kKESActionID, kKESPrefix + 15)
//DECLARE_PMID(kActionIDSpace, kKESActionID, kKESPrefix + 16)
//DECLARE_PMID(kActionIDSpace, kKESActionID, kKESPrefix + 17)
//DECLARE_PMID(kActionIDSpace, kKESActionID, kKESPrefix + 18)
//DECLARE_PMID(kActionIDSpace, kKESActionID, kKESPrefix + 19)
//DECLARE_PMID(kActionIDSpace, kKESActionID, kKESPrefix + 20)
//DECLARE_PMID(kActionIDSpace, kKESActionID, kKESPrefix + 21)
//DECLARE_PMID(kActionIDSpace, kKESActionID, kKESPrefix + 22)
//DECLARE_PMID(kActionIDSpace, kKESActionID, kKESPrefix + 23)
//DECLARE_PMID(kActionIDSpace, kKESActionID, kKESPrefix + 24)
//DECLARE_PMID(kActionIDSpace, kKESActionID, kKESPrefix + 25)


// WidgetIDs:
//DECLARE_PMID(kWidgetIDSpace, kKESWidgetID, kKESPrefix + 2)
//DECLARE_PMID(kWidgetIDSpace, kKESWidgetID, kKESPrefix + 3)
//DECLARE_PMID(kWidgetIDSpace, kKESWidgetID, kKESPrefix + 4)
//DECLARE_PMID(kWidgetIDSpace, kKESWidgetID, kKESPrefix + 5)
//DECLARE_PMID(kWidgetIDSpace, kKESWidgetID, kKESPrefix + 6)
//DECLARE_PMID(kWidgetIDSpace, kKESWidgetID, kKESPrefix + 7)
//DECLARE_PMID(kWidgetIDSpace, kKESWidgetID, kKESPrefix + 8)
//DECLARE_PMID(kWidgetIDSpace, kKESWidgetID, kKESPrefix + 9)
//DECLARE_PMID(kWidgetIDSpace, kKESWidgetID, kKESPrefix + 10)
//DECLARE_PMID(kWidgetIDSpace, kKESWidgetID, kKESPrefix + 11)
//DECLARE_PMID(kWidgetIDSpace, kKESWidgetID, kKESPrefix + 12)
//DECLARE_PMID(kWidgetIDSpace, kKESWidgetID, kKESPrefix + 13)
//DECLARE_PMID(kWidgetIDSpace, kKESWidgetID, kKESPrefix + 14)
//DECLARE_PMID(kWidgetIDSpace, kKESWidgetID, kKESPrefix + 15)
//DECLARE_PMID(kWidgetIDSpace, kKESWidgetID, kKESPrefix + 16)
//DECLARE_PMID(kWidgetIDSpace, kKESWidgetID, kKESPrefix + 17)
//DECLARE_PMID(kWidgetIDSpace, kKESWidgetID, kKESPrefix + 18)
//DECLARE_PMID(kWidgetIDSpace, kKESWidgetID, kKESPrefix + 19)
//DECLARE_PMID(kWidgetIDSpace, kKESWidgetID, kKESPrefix + 20)
//DECLARE_PMID(kWidgetIDSpace, kKESWidgetID, kKESPrefix + 21)
//DECLARE_PMID(kWidgetIDSpace, kKESWidgetID, kKESPrefix + 22)
//DECLARE_PMID(kWidgetIDSpace, kKESWidgetID, kKESPrefix + 23)
//DECLARE_PMID(kWidgetIDSpace, kKESWidgetID, kKESPrefix + 24)
//DECLARE_PMID(kWidgetIDSpace, kKESWidgetID, kKESPrefix + 25)

// Script Element IDs
DECLARE_PMID(kScriptInfoIDSpace, kKESMatchScrollZoomAllLayoutMethodScriptElement, kKESPrefix + 1)
DECLARE_PMID(kScriptInfoIDSpace, kKESAccessContentLocationAtFrameOriginXPropertyScriptElement, kKESPrefix + 2)
DECLARE_PMID(kScriptInfoIDSpace, kKESAccessContentLocationAtFrameOriginYPropertyScriptElement, kKESPrefix + 3)

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

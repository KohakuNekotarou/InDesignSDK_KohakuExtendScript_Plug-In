#pragma once

// Interface includes:
#include "IControlView.h"
#include "IPanorama.h"
#include "IScript.h"
#include "IScriptRequestData.h"

class KESLayout
{
public:
    // Apply scrolling and zooming from the Front Layout Window to all Layout.
    static ErrorCode MatchScrollZoomAllLayout(bool16 flg, IPanorama* iPanorama_master);

    // Access the top-left coordinates of the layout Window.
    static ErrorCode AccessContentLocationAtFrameOrigin
        (ScriptID scriptID, IScriptRequestData* iScriptRequestData, IScript* iScript, std::string flgXY);

    // Toggle split layout view.
    static ErrorCode ToggleSplitLayout(IScript* iScript);

    // Query Nth layout.
    static ErrorCode QueryNthLayout(ScriptID scriptID, IScriptRequestData* iScriptRequestData, IScript* iScript);

    // Get put content location at frame origin.
    static ErrorCode GetPutContentLocationAtFrameOrigin
        (ScriptID scriptID, IScriptRequestData* iScriptRequestData, IScript* iScript, std::string flgXY, IControlView* iControlView);

    // Is split layout view shown.
    static ErrorCode IsSplitLayoutViewShown(ScriptID scriptID, IScriptRequestData* iScriptRequestData, IScript* iScript);
};
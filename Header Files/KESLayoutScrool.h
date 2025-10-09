#pragma once

#include "IControlView.h"
#include "IDocument.h"
#include "IPanorama.h"
#include "IScript.h"
#include "IScriptRequestData.h"

#include <string>

class KESLayoutScrool
{
public:
    /** Apply scrolling and zooming from the Front Layout Window to all Layout.
    */
    static ErrorCode MatchScrollZoomAllLayout();

    /**  Access the top-left coordinates of the layout Window.
    */
    static ErrorCode AccessContentLocationAtFrameOrigin
        (ScriptID scriptID, IScriptRequestData* iScriptRequestData, IScript* iScript, std::string flgXY);

private:
    /**  Query panorama.
    */
    static std::pair<IControlView*, IPanorama*> QueryControlViewAndPanorama(IDocument* idocument);
};


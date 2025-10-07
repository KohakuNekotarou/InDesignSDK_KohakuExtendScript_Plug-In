#pragma once

#include "IScript.h"
#include "IScriptRequestData.h"

class KESLayoutScrool
{
private:
    ScriptID scriptID;
    IScriptRequestData* iScriptRequestData;
    IScript* iScript;

public:
    // Constructor
    KESLayoutScrool(ScriptID methodID, IScriptRequestData* data, IScript* parent);

    // MatchScrollZoomAllLayout
    static ErrorCode MatchScrollZoomAllLayout();
};


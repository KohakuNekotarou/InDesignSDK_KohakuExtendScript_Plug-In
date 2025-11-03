#pragma once

// Interface includes:
#include "IScript.h"
#include "IScriptRequestData.h"

class KESShortcut
{
public:
    // Remove current context shortcut.
    static ErrorCode RemoveContextShortcut(IScriptRequestData* iScriptRequestData, IScript* iScript);

    // Display all action.
    static ErrorCode DisplayAllAction();
};
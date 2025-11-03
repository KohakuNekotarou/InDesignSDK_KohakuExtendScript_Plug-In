#pragma once

// Interface includes:
#include "IScript.h"
#include "IScriptRequestData.h"

class KESStyle
{
public:
    // Keyboard shortcut.
	static ErrorCode KeyboardShortcut(ScriptID scriptID, IScriptRequestData* iScriptRequestData, IScript* iScript);
};
#pragma once

// Interface includes:
#include "IScript.h"
#include "IScriptRequestData.h"

/*
typedef enum
{
	kCmdKey = 0x01
	kShiftKey = 0x02,
	kUpDown = kCmdKey | kShiftKey
}eUpDown;
*/

typedef enum
{
	kCmdKey = 0x01, // ctrl
	kShiftKey = 0x02,
	kctrlShiftKey = kShiftKey | kCmdKey
}eUpDown;

class KESStyle
{
public:
    // Set keyboard shortcut.
    static ErrorCode SetKeyboardShortcut(IScriptRequestData* iScriptRequestData, IScript* iScript);
};
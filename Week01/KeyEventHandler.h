#pragma once
#ifndef _KEY_HANDLER_H
#define _KEY_HANDLER_H

#include <Windows.h>

class CKeyEventHandler
{
public:
	virtual void KeyState(BYTE* state) = 0;
	virtual void OnKeyDown(int KeyCode) = 0;
	virtual void OnKeyUp(int KeyCode) = 0;
	virtual void IsKeyDown(int keyCode) = 0;
};

typedef CKeyEventHandler* LPKEYEVENTHANDLER;

#endif // !_KEY_HANDLER_H

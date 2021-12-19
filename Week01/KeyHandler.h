#pragma once
#ifndef _KEY_HANDLER_H

#include "KeyEventHandler.h"

class CKeyHandler : public CKeyEventHandler {
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	virtual void IsKeyDown(int keyCode);
};

#endif // !_KEY_HANDLER_H

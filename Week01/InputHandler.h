#pragma once
#ifndef _INPUT_HANDLER_H
#define _INPUT_HANDLER_H

#include "resources.h"
#include "KeyEventHandler.h"

class CInputHandler {
private:
	static CInputHandler* __instance;

	HWND hWnd;
	LPDIRECTINPUT8       di;		// The DirectInput object         
	LPDIRECTINPUTDEVICE8 didv;		// The keyboard device 

	BYTE  keyStates[256];			// DirectInput keyboard state buffer 
	DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];		// Buffered keyboard data

	LPKEYEVENTHANDLER keyHandler;
	std::vector<int> presses;

public:
	CInputHandler();
	CInputHandler(HWND hWnd, LPKEYEVENTHANDLER keyHandler);

	void SetHandleWindow(HWND hWnd);
	void SetKeyHandler(LPKEYEVENTHANDLER handler);

	void InitKeyboard();
	void ProcessKeyboard();

	int IsKeyDown(int keyCode);
	int OnKeyDown(int keyCode);

	static CInputHandler* GetInstance();
};

#endif // !_INPUT_HANDLER_H

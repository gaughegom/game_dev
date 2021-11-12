#pragma once
#ifndef _GAME_H
#define _GAME_H

#include "resources.h"

class CKeyEventHandler
{
public:
	virtual void Key_state(BYTE* state) = 0;
	virtual void On_key_down(int KeyCode) = 0;
	virtual void On_key_up(int KeyCode) = 0;
};

typedef CKeyEventHandler* LPKEYEVENTHANDLER;

class CGame
{
	static CGame* __instance;
	HWND hWnd;									// Window handle

	LPDIRECT3D9 d3d = NULL;						// Direct3D handle
	LPDIRECT3DDEVICE9 d3ddv = NULL;				// Direct3D device object

	LPDIRECT3DSURFACE9 backBuffer = NULL;
	LPD3DXSPRITE spriteHandler = NULL;			// Sprite helper library to help us draw 2D image on the screen 

	LPDIRECTINPUT8       di;		// The DirectInput object         
	LPDIRECTINPUTDEVICE8 didv;		// The keyboard device 

	BYTE  keyStates[256];			// DirectInput keyboard state buffer 
	DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];		// Buffered keyboard data

	LPKEYEVENTHANDLER keyHandler;

	int backBufferWidth = 0;
	int backBufferHeight = 0;

public:
	void Init_keyboard(LPKEYEVENTHANDLER handler);
	void Init_game(HWND hWnd);
	void Draw(float x, float y, LPDIRECT3DTEXTURE9 texture, int left, int top, int right, int bottom);

	int Is_key_down(int KeyCode);
	void Process_keyboard();

	LPDIRECT3DDEVICE9 Get_direct3D_device() { return this->d3ddv; }
	LPDIRECT3DSURFACE9 Get_backbuffer() { return backBuffer; }
	LPD3DXSPRITE Get_sprite_handler() { return this->spriteHandler; }

	static CGame* Get_instance();

	int Get_backbuffer_width() { return this->backBufferWidth; }
	int Get_backbuffer_height() { return this->backBufferHeight; }

	~CGame();
};

#endif // !_GAME_H

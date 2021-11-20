#pragma once
#ifndef _GAME_H
#define _GAME_H

#include "resources.h"

class CKeyEventHandler
{
public:
	virtual void KeyState(BYTE* state) = 0;
	virtual void OnKeyDown(int KeyCode) = 0;
	virtual void OnKeyUp(int KeyCode) = 0;
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
	void InitKeyboard(LPKEYEVENTHANDLER handler);

	int IsKeyDown(int KeyCode);
	void ProcessKeyboard();
	
	void InitDirectX(HWND hWnd);
	void Draw(Vector2D position, int nx, LPDIRECT3DTEXTURE9 texture, int left, int top, int right, int bottom);

	void Init(HWND hWnd);
	void Update(DWORD dt);
	void Render();
	void Run();

	void CreateGameObject();

	LPDIRECT3DDEVICE9 GetDirect3dDevice() { return this->d3ddv; }
	LPDIRECT3DSURFACE9 GetBackbuffer() { return backBuffer; }
	LPD3DXSPRITE GetSpriteHandler() { return this->spriteHandler; }

	int GetBackbufferWidth() { return this->backBufferWidth; }
	int GetBackbufferHeight() { return this->backBufferHeight; }

	static CGame* GetInstance();

	~CGame();
};

#endif // !_GAME_H

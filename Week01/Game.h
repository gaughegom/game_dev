#pragma once
#ifndef _GAME_H
#define _GAME_H

#include "resources.h"
#include "KeyEventHandler.h"

class CSprite;
class CGameObject;

class CGame {
	static CGame* __instance;

	HWND hWnd;									// Window handle

	LPDIRECT3D9 d3d = NULL;						// Direct3D handle
	LPDIRECT3DDEVICE9 d3ddv = NULL;				// Direct3D device object

	LPDIRECT3DSURFACE9 backBuffer = NULL;
	LPD3DXSPRITE spriteHandler = NULL;			// Sprite helper library to help us draw 2D image on the screen 

	LPKEYEVENTHANDLER keyHandler;

	int backBufferWidth = 0;
	int backBufferHeight = 0;


public:
	CSprite* lpsBackground;
	Vector2D backgound;
	void InitDirectX(HWND hWnd);
	void Draw(Vector2D position, int nx, LPDIRECT3DTEXTURE9 texture, int left, int top, int right, int bottom);

	void InitGame(HWND hWnd);
	void UpdateGame(DWORD dt);
	void RenderGame();
	void RunGame();

	void LoadResource();
	void CreateGameObject();

	LPDIRECT3DDEVICE9 GetDirect3dDevice() { return this->d3ddv; }
	LPDIRECT3DSURFACE9 GetBackbuffer() { return backBuffer; }
	LPD3DXSPRITE GetSpriteHandler() { return this->spriteHandler; }

	int GetBackbufferWidth() { return this->backBufferWidth; }
	int GetBackbufferHeight() { return this->backBufferHeight; }

	LPKEYEVENTHANDLER GetKeyHandler() { return this->keyHandler; }

	static CGame* GetInstance();

	~CGame();
};

#endif // !_GAME_H

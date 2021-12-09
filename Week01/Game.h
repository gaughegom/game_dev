#pragma once
#ifndef _GAME_H
#define _GAME_H

#include <fstream>
#include "resources.h"

class CSprite;
typedef CSprite* LPSPRITE;
class CKeyEventHandler;
typedef CKeyEventHandler* LPKEYEVENTHANDLER;
class CGameObject;
typedef CGameObject* LPGAMEOBJECT;

enum class SceneSection : int {
	SCENE_SECTION_UNKNOW = 0,
	SCENE_SECTION_TEXTURES = 1,
	SCENE_SECTION_SPRITES = 2,
	SCENE_SECTION_ANIMATIONS = 3,
	SCENE_SECTION_MAP = 4,
	SCENE_SECTION_PLATFORMS = 5,
	SCENE_SECTION_OBJECTS = 6
};

class CGame {
	static CGame* __instance;
	static DWORD dt;

	HWND hWnd;									// Window handle

	LPDIRECT3D9 d3d = nullptr;						// Direct3D handle
	LPDIRECT3DDEVICE9 d3ddv = nullptr;				// Direct3D device object

	LPDIRECT3DSURFACE9 backBuffer = nullptr;
	LPD3DXSPRITE spriteHandler = nullptr;			// Sprite helper library to help us draw 2D image on the screen 

	LPKEYEVENTHANDLER keyHandler;

	int mapWidth = 0;
	int mapHeight = 0;

	LPSPRITE map;

public:
	void InitDirectX(HWND hWnd);
	void Draw(Vector2D position, int nx, LPDIRECT3DTEXTURE9 texture, int left, int top, int right, int bottom, D3DCOLOR color);

	// main game loop
	void InitGame(HWND hWnd);
	void UpdateGame(DWORD dt);
	void RenderGame();
	void RunGame();

	// resources
	void LoadResource();
	void __ParseSection_TEXTURES__(std::string line);
	void __ParseSection_SPRITES__(std::string line);
	void __ParseSection_ANIMATIONS__(std::string line);
	void __ParseSection_MAP__(std::string line);
	void __ParseSection_OBJECTS__(std::string line);
	void __ParseSection_PLATFORMS__(std::string line);

	// game object
	void PrepareGameObject(LPGAMEOBJECT& object, std::vector<std::string> tokens);
	void NewGameObject(LPGAMEOBJECT& newObject);
	void CleanGameObject();
	std::vector<LPGAMEOBJECT> GetRenderedObjects();

	// device
	LPDIRECT3DDEVICE9 GetDirect3dDevice() { return this->d3ddv; }
	LPDIRECT3DSURFACE9 GetBackbuffer() { return backBuffer; }
	LPD3DXSPRITE GetSpriteHandler() { return this->spriteHandler; }

	int GetMapWidth() { return this->mapWidth; }
	int GetMapHeight() { return this->mapHeight; }

	LPKEYEVENTHANDLER GetKeyHandler() { return this->keyHandler; }

	static CGame* GetInstance();
	static DWORD GetDeltaTime() { return dt; }
	~CGame();
};

#endif // !_GAME_H

#pragma once
#ifndef _GAME_H
#define _GAME_H

#include <fstream>
#include "resources.h"
#include "Scene.h"

class CSprite;
typedef CSprite* LPSPRITE;
class CKeyEventHandler;
typedef CKeyEventHandler* LPKEYEVENTHANDLER;
class CGameObject;
typedef CGameObject* LPGAMEOBJECT;
class CGate;
class CScene;
typedef CScene* LPSCENE;

enum class SceneSection : int {
	SCENE_SECTION_UNKNOW = 0,
	SCENE_SECTION_TEXTURES = 1,
	SCENE_SECTION_SPRITES = 2,
	SCENE_SECTION_ANIMATIONS = 3,
	SCENE_SECTION_MAP = 4,
	SCENE_SECTION_PLATFORMS = 5,
	SCENE_SECTION_OBJECTS = 6,
	SCENE_SECTION_CHARACTERS = 7,
	SCENE_SECTION_PLAYERS = 8,
	SCENE_SECTION_GATES = 9,
	LOAD_SCENE = 10
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

	std::unordered_map<int, LPSCENE> scenes;
	int currentScene = 0;	// default scene 0


	float camWidth = 0;
	float camHeight = 0;
	float mapWidth = 0;
	float mapHeight = 0;

	LPSPRITE map;
	bool reset = false;

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
	void __ParseSection_CHARACTERS__(std::string line);
	void __LoadSceneResource__(std::string line);

	// game object
	void NewGameObject(LPGAMEOBJECT& newObject);
	void CleanGameObject();
	std::vector<LPGAMEOBJECT> GetRenderedObjects();

	// scene
	void PlayScene();
	void SwitchScene(int id);
	void MappingPlayerScene();

	// device
	LPDIRECT3DDEVICE9 GetDirect3dDevice() { return this->d3ddv; }
	LPDIRECT3DSURFACE9 GetBackbuffer() { return backBuffer; }
	LPD3DXSPRITE GetSpriteHandler() { return this->spriteHandler; }

	LPKEYEVENTHANDLER GetKeyHandler() { return this->keyHandler; }

	static CGame* GetInstance();
	static DWORD GetDeltaTime() { return dt; }
	~CGame();
};

#endif // !_GAME_H

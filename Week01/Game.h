#pragma once
#ifndef _GAME_H
#define _GAME_H

#include <fstream>
#include <queue>
#include <iostream>
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
	SCENE_SECTION_FOREMAP = 10,
	LOAD_SCENE = 11
};

class CGame {
private:
	static CGame* __instance;
	static DWORD dt;

	HWND hWnd;									// Window handle

	LPDIRECT3D9 d3d = nullptr;						// Direct3D handle
	LPDIRECT3DDEVICE9 d3ddv = nullptr;				// Direct3D device object

	LPDIRECT3DSURFACE9 backBuffer = nullptr;
	LPD3DXSPRITE spriteHandler = nullptr;			// Sprite helper library to help us draw 2D image on the screen 

	LPKEYEVENTHANDLER keyHandler;

	std::unordered_map<int, LPSCENE> scenes;
	int currentScene = 3;	// default scene 0

	std::vector<LPGAMEOBJECT> worldObjects, renderedObjects;
	std::queue<LPGAMEOBJECT> queueObjects;

	float camWidth = 0;
	float camHeight = 0;
	float mapWidth = 0;
	float mapHeight = 0;

	LPSPRITE map;
	LPSPRITE foreMap;
	bool reset = false;


	void AddGameObjectToWorld(LPGAMEOBJECT const& newObject);

public:
	// directX
	void InitDirectX(HWND hWnd);
	void Draw(Vector2D position, int nx, LPDIRECT3DTEXTURE9 texture, int left, int top, int right, int bottom, D3DCOLOR color, int layer, float rotate = 0.0f);

	// main game loop
	void InitGame(HWND hWnd);
	void UpdateGame(DWORD dt);
	void RenderGame();
	void RunGame();


	// resource from database
	void LoadResource();
	void __LoadSceneResource__(std::string line);
	void __ParseSection_TEXTURES__(std::string line);
	void __ParseSection_SPRITES__(std::string line);
	void __ParseSection_ANIMATIONS__(std::string line);
	void __ParseSection_CHARACTERS__(std::string line);

	// queue gameObject
	void PushToQueueObject(LPGAMEOBJECT const& object) { this->queueObjects.push(object); }
	template<typename T>
	inline T* InitiateAndPushToQueue(Vector2D position, Vector2D velocity = VectorZero(), int nx = 1);
	std::vector<LPGAMEOBJECT> GetRenderedObjects() const { return this->renderedObjects; }
	std::queue<LPGAMEOBJECT> GetQueueObject() const { return this->queueObjects; }
	void CleanGameObject();

	// scene
	void PlayScene();
	void SwitchScene(int id);
	void MappingPlayerScene();
	int GetCurrentSceneId() { return this->currentScene; }

	// device
	LPDIRECT3DDEVICE9 GetDirect3dDevice() const { return this->d3ddv; }
	LPDIRECT3DSURFACE9 GetBackbuffer() const { return backBuffer; }
	LPD3DXSPRITE GetSpriteHandler() const { return this->spriteHandler; }

	LPKEYEVENTHANDLER GetKeyHandler() const { return this->keyHandler; }

	static CGame* GetInstance();
	static DWORD GetDeltaTime() { return dt; }

	~CGame();
};

#endif // !_GAME_H

/*
	Create a GameObject class and push to scene queue (position, velocity, nx)
	WARM: NOT READY FOR PLAYER BULLET TEMPORARILY
*/
template<typename T>
inline T* CGame::InitiateAndPushToQueue(Vector2D position, Vector2D velocity, int nx)
{
	LPGAMEOBJECT newObject = new T;
	newObject->SetPosition(position);
	newObject->SetVelocity(velocity);
	newObject->SetNx(nx);
	this->PushToQueueObject(newObject);
	return (T*)newObject;
}

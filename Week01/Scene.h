#pragma once
#ifndef _SCENE_H
#define _SCENE_H

#include "Game.h"

class CSprite;
typedef CSprite* LPSPRITE;
class CKeyEventHandler;
typedef CKeyEventHandler* LPKEYEVENTHANDLER;
class CGameObject;
typedef CGameObject* LPGAMEOBJECT;
class CGame;
class CScene {
private:
	int id;
	LPCWSTR filePath;
	LPSPRITE map;
	SRect mapBoundary;
	std::vector<LPGAMEOBJECT> sceneObjects;
	
	void __ParseSection_MAP__(std::string line);
	void __ParseSection_PLATFORMS__(std::string line);
	void __ParseSection_OBJECTS__(std::string line);

public:
	CScene(int id, LPCWSTR filePath);
	
	void LoadScene();
	void UnloadScene();

	// map
	void SetMapSprite(LPSPRITE map) { this->map = map; }
	LPSPRITE GetMapSrite() { return this->map; }

	// sceneObjects
	void SetSceneObjects(std::vector<LPGAMEOBJECT> objects) { this->sceneObjects = objects; }
	std::vector<LPGAMEOBJECT> GetSceneObjects() { return this->sceneObjects; }

	void SetMapBoundary(SRect rect) { this->mapBoundary = rect; }
	SRect GetMapBoundary() { return this->mapBoundary; }

	int GetSceneId() { return this->id; }
	LPCWSTR GetFilePath() { return this->filePath; }

};
typedef CScene* LPSCENE;

#endif // !_SCENE_H

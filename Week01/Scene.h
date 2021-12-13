#pragma once
#ifndef _SCENE_H
#define _SCENE_H

#include "Game.h"

class CSprite;
typedef CSprite* LPSPRITE;
class CGameObject;
typedef CGameObject* LPGAMEOBJECT;
class CGate;
class CGame;
class CScene {
private:
	LPCWSTR filePath;
	LPSPRITE map;
	SRect mapBoundary;
	std::vector<LPGAMEOBJECT> sceneObjects;
	std::vector<CGate*> gates;

	void __ParseSection_MAP__(std::string line);
	void __ParseSection_PLATFORMS__(std::string line);
	void __ParseSection_OBJECTS__(std::string line);
	void __ParseSection_PLAYERS__(std::string line);
	void __ParseSection_GATES__(std::string line);

public:
	CScene(LPCWSTR filePath);
	
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

	std::vector<CGate*> GetGates() { return this->gates; }
	Vector2D GetPositionOfGate(int id);

	LPCWSTR GetFilePath() { return this->filePath; }

};
typedef CScene* LPSCENE;

#endif // !_SCENE_H

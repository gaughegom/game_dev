#pragma once
#ifndef _GATE_H
#define _GATE_H

#include "GameObject.h"

class CGate : public CGameObject {
private:
	int nextScene;

public:
	CGate();
	CGate(Vector2D boundingBox);
	CGate(Vector2D boundingBox, int next);

	void SetNextScene(int value) { this->nextScene = value; }
	int GetNextScene() { return this->nextScene; }

	void Update(DWORD dt);
	void Render();
};

#endif // !_GATE_H

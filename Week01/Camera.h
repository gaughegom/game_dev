#pragma once
#ifndef _CAMERA_H
#define _CAMARA_H

#include "resources.h"
#include "GameObject.h"
#include "Transform.h"

class CCamera {
private:
	static CCamera* __instance;

protected:
	Vector2D position;
	Vector2D size;
	CGameObject* target;
	SRect boundary;
	SRect freezeBoundary = SRect(104, 120, 152, 150);

	bool boundless = false;

public:
	CCamera();

	// position and site
	void SetPosition(Vector2D position);
	void SetSize(Vector2D size);
	void Update();

	Vector2D GetPosition();
	SRect GetBoundingBox();
	void SetBoundary(SRect boundary);
	void SetBoundless(bool value) { this->boundless = value; }

	// target
	void SetTarget(CGameObject* target);
	CGameObject* GetTarget();

	Vector2D TranslateWorldToScreen(Vector2D pos);

	static CCamera* GetInstance();
};

#endif // !_CAMERA_H

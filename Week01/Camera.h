#pragma once
#ifndef _CAMERA_H
#define _CAMARA_H

#include "resources.h"
#include "GameObject.h"
#include "Transform.h"

class CCamera {
protected:
	Vector2D position;
	Vector2D size;
	CGameObject* target;
	SRect boundary;

public:
	CCamera();

	// position and site
	void SetPosition(Vector2D position);
	void SetSize(Vector2D size);
	void Update();

	Vector2D GetPosition();
	SRect GetBoundingBox();
	void SetBoundary(SRect boundary);

	// target
	void SetTarget(CGameObject* target);
	CGameObject* GetTarget();

	Vector2D TranslateWorldToScreen(Vector2D pos);
};

#endif // !_CAMERA_H

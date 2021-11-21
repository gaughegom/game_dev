#pragma once
#ifndef _CAMERA_H
#define _CAMARA_H

#include "resources.h"
#include "GameObject.h"
#include "Transform.h"

class CCamera {
protected:
	Vector2D position;
	int width, height;
	CGameObject* target;


public:
	CCamera();

	// position and site
	void SetPosition(Vector2D position);
	void SetSize(int newWidth, int newHeight);
	void UpdateGame();

	Vector2D GetPosition();
	float GetX();
	float GetY();
	int GetWidth();
	int GetHeight();
	SRect GetBoundingBox();

	// target
	void SetTarget(CGameObject* target);
	CGameObject* GetTarget();
};

#endif // !_CAMERA_H

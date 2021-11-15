#pragma once
#ifndef _CAMERA_H
#define _CAMARA_H

#include "resources.h"
#include "GameObject.h"

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
	void Update();

	Vector2D GetPosition();
	float GetX();
	float GetY();
	int GetWidth();
	int GetHeight();

	// target
	void SetTarget(CGameObject* target);
	CGameObject* GetTarget();
};

#endif // !_CAMERA_H

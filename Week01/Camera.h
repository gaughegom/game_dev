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
	void Set_position(float newX, float newY);
	void Set_size(int newWidth, int newHeight);
	void Update();

	Vector2D Get_position();
	float Get_x();
	float Get_y();
	int Get_width();
	int Get_height();

	// target
	void Set_target(CGameObject* target);
	CGameObject* Get_target();
};

#endif // !_CAMERA_H

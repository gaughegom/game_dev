#pragma once
#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H

#include "resources.h"
#include "Sprites.h"
#include "Game.h"
#include "Vector2D.h"

class CGameObject
{
protected:

	CVector2D position;
	CVector2D velocity;

	/*float x;
	float y;

	float vx;
	float vy;*/

	int nx;

	int state;

	static std::vector<LPANIMATION> animations;

public:
	void Set_position(float _x, float _y) { this->position.x = _x, this->position.y = _y; }
	void Set_speed(float _vx, float _vy) { this->velocity.x = _vx, this->velocity.y = _vy; }

	void Set_state(int _state) { this->state = _state; }
	int Get_state() { return this->state; }

	void Set_x(float _x);
	void Set_y(float _y);

	static void Add_animation(int _aniId);

	CGameObject();

	virtual void Update(DWORD dt);
	virtual void Render() = 0;
	~CGameObject();
};

#endif // !_GAMEOBJECT_H

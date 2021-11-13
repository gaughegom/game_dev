#pragma once
#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H

#include "resources.h"
#include "Sprites.h"
#include "Game.h"
#include "Vector2D.h"
#include "GameMovement.h"

class CGameObject
{
protected:

	CVector2D position;
	CVector2D velocity;

	int nx;

	int state;

	static std::vector<LPANIMATION> animations;

public:
	void Set_position(float newX, float newY) { this->position.x = newX, this->position.y = newY; }
	void Set_speed(float newVx, float newVy) { this->velocity.x = newVx, this->velocity.y = newVy; }

	void Set_state(int newState) { this->state = newState; }
	int Get_state() { return this->state; }

	void Set_x(float newX);
	void Set_y(float newY);

	static void Add_animation(int animationId);

	CGameObject();

	virtual void Update(DWORD dt);
	virtual void Render() = 0;
	~CGameObject();
};

#endif // !_GAMEOBJECT_H

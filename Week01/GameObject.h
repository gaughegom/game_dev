#pragma once
#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H

#include "resources.h"
#include "Sprites.h"
#include "Game.h"
#include "GameMovement.h"

class CGameObject
{
protected:

	Vector2D position;
	Vector2D velocity;

	int nx;

	int state;

	static std::vector<LPANIMATION> animations;

public:
	// position
	void Set_position(float newX, float newY) { this->position.x = newX, this->position.y = newY; }
	Vector2D Get_position();
	void Set_x(float newX);
	void Set_y(float newY);
	float Get_x();
	float Get_y();

	// velocity
	void Set_velocity(float newVx, float newVy) { this->velocity.x = newVx, this->velocity.y = newVy; }

	// state
	void Set_state(int newState) { this->state = newState; }
	int Get_state() { return this->state; }


	static void Add_animation(int animationId);

	CGameObject();

	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0;
	~CGameObject();
};

#endif // !_GAMEOBJECT_H

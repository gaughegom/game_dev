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
	void SetPosition(float newX, float newY) { this->position.x = newX, this->position.y = newY; }
	Vector2D GetPosition();
	void SetX(float newX);
	void SetY(float newY);
	void SetNx(float newNX);
	float GetX();
	float GetY();
	int GetNX() { return this->nx; }

	// velocity
	void SetVelocity(float newVx, float newVy) { this->velocity.x = newVx, this->velocity.y = newVy; }
	Vector2D GetVelocity() { return this->velocity; }

	// state
	void SetState(int newState) { this->state = newState; }
	int GetState() { return this->state; }


	static void AddAnimation(int animationId);

	CGameObject();

	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0;
	~CGameObject();
};

#endif // !_GAMEOBJECT_H

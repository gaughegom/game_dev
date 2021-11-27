#pragma once
#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H

#include "resources.h"
#include "Sprites.h"
#include "Game.h"
#include "GameMovement.h"
#include "Animations.h"

class CGameObject
{
protected:

	Vector2D position;
	Vector2D velocity;

	int nx;
	int state; // use for single state object

	float width;
	float height;

	SRect rect = SRect(
		position.x - width / 2 ,
		position.y + height / 2,
		position.x + width / 2,
		position.y - height / 2
	);

	std::unordered_map<std::string, LPANIMATION> animations;

public:
	CGameObject();

	// position
	void SetPosition(float newX, float newY) { this->position.x = newX, this->position.y = newY; }
	Vector2D GetPosition();
	void SetX(float newX);
	void SetY(float newY);
	void SetNx(float newNX);
	float GetX();
	float GetY();
	int GetNx();

	// velocity
	void SetVelocity(float newVx, float newVy) { this->velocity.x = newVx, this->velocity.y = newVy; }
	Vector2D GetVelocity() { return this->velocity; }

	// width and height
	void SetSize(float newWidth, float newHeight) { this->width = newWidth, this->height = newHeight; }
	float GetWidth() { return this->width; }
	float GetHeight() { return this->height; }

	// state
	void SetState(int newState) { this->state = newState; }
	int GetState() { return this->state; }

	SRect GetRect() { return this->rect; }

	// animation
	void AddAnimation(std::string key, int animationId);
	std::unordered_map<std::string, LPANIMATION> GetAnimations() { return this->animations; }


	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0;

	virtual void EdgeCollisionHandler();

	~CGameObject();
};
typedef CGameObject* LPGAMEOBJECT;

#endif // !_GAMEOBJECT_H

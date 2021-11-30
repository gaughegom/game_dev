#pragma once
#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H

#include "resources.h"
#include "Sprites.h"
#include "Game.h"
#include "GameMovement.h"
#include "Animations.h"
#include "Collider2D.h"
#include "QuadTree.h"

class CCollider2D;
struct SCollisionEvent;
typedef SCollisionEvent* LPCOLLISIONEVENT;

class CGameObject
{
protected:

	Vector2D position;
	Vector2D velocity;
	std::vector<CCollider2D*> colliders;

	int nx;
	int state; // use for single state object
	bool ground;

	std::unordered_map<std::string, LPANIMATION> animations;

public:
	CGameObject();

	// position
	void SetPosition(Vector2D position) { this->position = position; }
	Vector2D GetPosition();
	void SetX(float newX);
	void SetY(float newY);
	void SetNx(float newNX);
	float GetX();
	float GetY();
	int GetNx();

	// velocity
	void SetVelocity(Vector2D velocity) { this->velocity = velocity; }
	Vector2D GetVelocity() { return this->velocity; }

	// state
	void SetState(int state) { this->state = state; }
	int GetState() { return this->state; }

	// animation
	void AddAnimation(std::string key, int animationId);
	std::unordered_map<std::string, LPANIMATION> GetAnimations() { return this->animations; }

	// collider
	void SetColliders(std::vector<CCollider2D*> colliders) { this->colliders = colliders; }
	std::vector<CCollider2D*> GetColliders() { return this->colliders; }

	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0;
	virtual void PhysicalUpdate(std::vector<LPGAMEOBJECT>* coObjects);
	virtual void OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent);
	virtual void OnTrigger(CCollider2D* self, LPCOLLISIONEVENT coEvent);

	~CGameObject();
};
typedef CGameObject* LPGAMEOBJECT;

#endif // !_GAMEOBJECT_H

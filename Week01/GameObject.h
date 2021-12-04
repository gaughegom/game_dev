#pragma once
#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H

#include "resources.h"
#include "Animations.h"
#include "Collider2D.h"
#include "Game.h"
#include "QuadTree.h"
#include "Sprites.h"
#include "SimulationEnvroment.h"

struct SCollisionEvent;
typedef SCollisionEvent* LPCOLLISIONEVENT;
class CQuadTree;
class CCollider2D;
class CGameObject
{
protected:

	Vector2D position;
	Vector2D velocity;
	std::vector<CCollider2D*> colliders;

	int nx;

	float hp;
	float damage;

	bool ground;
	bool live = true;
	bool active = true;
	bool deleted = false;

	CQuadTree* selfNode;
	int selfIndexInNode = -1;

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

	// animation
	void AddAnimation(std::string key, int animationId);
	std::unordered_map<std::string, LPANIMATION> GetAnimations() { return this->animations; }

	// quadtree node
	void SetSelfNodeQt(CQuadTree* node) { this->selfNode = node; }
	CQuadTree* GetSelfNodeQt() { return this->selfNode; }
	void SetSelfIndexInNodeQt(int index) { this->selfIndexInNode = index; }
	int GetSelfIndexInNodeQt() { return this->selfIndexInNode; }

	// collider
	void SetColliders(std::vector<CCollider2D*> colliders) { this->colliders = colliders; }
	std::vector<CCollider2D*> GetColliders() { return this->colliders; }

	// live
	void SetLive(bool value) { this->live = value; }
	bool IsLive() { return this->live; }

	// delete
	void SetDeleted(bool value) { this->deleted = value; }
	bool IsDeleted() { return this->deleted; }

	// enable
	void SetActive(bool value) { this->active = value; }
	bool IsActive() { return this->active; }

	// hp
	void TakeDamage(float damage) { this->hp -= damage; }
	float GetHp() { return this->hp; }

	// damage
	void SetDamage(float damage) { this->damage = damage; }
	float GetDamage() { return this->damage; }

	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0;
	virtual void PhysicalUpdate(std::vector<LPGAMEOBJECT>* coObjects);
	virtual void OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent);
	virtual void OnTrigger(CCollider2D* self, LPCOLLISIONEVENT coEvent);

	~CGameObject();
};
typedef CGameObject* LPGAMEOBJECT;

#endif // !_GAMEOBJECT_H

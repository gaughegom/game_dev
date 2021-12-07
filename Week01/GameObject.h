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
#include "TriggerTag.h"

struct STriggerTag;
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

	bool rendering = false;
	bool ground;
	bool live = true; // TODO: use with dynamic and hp
	bool active = true;
	bool deleted = false;
	bool invicible = false;

	std::vector<STriggerTag> triggerTag;

	std::vector<CQuadTree*> selfNodes;
	int selfIndexInNode = -1;

	std::unordered_map<std::string, LPSPRITE> sprites;
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

	// sprites
	void AddSprite(std::string key, int spriteId);
	std::unordered_map<std::string, LPSPRITE> GetSprites() { return this->sprites; }

	// animations
	void AddAnimation(std::string key, int animationId);
	std::unordered_map<std::string, LPANIMATION> GetAnimations() { return this->animations; }

	// rendering
	void SetRendering(bool value) { this->rendering = value; }
	bool IsRendering() { return this->rendering; }

	// quadtree node
	void SetSelfNodeQt(CQuadTree* node) { this->selfNodes.push_back(node); }
	void ClearSelfNodesQt() { this->selfNodes.clear(); }
	std::vector<CQuadTree*> GetSelfNodesQt() { return this->selfNodes; }
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

	// active
	void SetActive(bool value) { this->active = value; }
	bool IsActive() { return this->active; }

	// hp
	void TakeDamage(LPCOLLISIONEVENT& bulletCollision);
	void SetHp(float hp) { this->hp = hp; }
	float GetHp() { return this->hp; }

	// damage
	void SetDamage(float damage) { this->damage = damage; }
	float GetDamage() { return this->damage; }

	// invisible
	void SetInvisible(bool value) { this->invicible = true; }
	bool GetInvisible() { return this->invicible; }

	// invisible with
	void SetTriggerTag(STriggerTag tag) { this->triggerTag.push_back(tag); }
	void ClearTriggerTag() { this->triggerTag.clear(); }
	std::vector<STriggerTag> GetTriggerTag() { return this->triggerTag; }

	// virtual
	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0;
	virtual void PhysicalUpdate(std::vector<LPGAMEOBJECT>* coObjects);
	virtual void OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent);
	virtual void OnTrigger(CCollider2D* self, LPCOLLISIONEVENT coEvent);

	~CGameObject();
};
typedef CGameObject* LPGAMEOBJECT;

#endif // !_GAMEOBJECT_H

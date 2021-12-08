#pragma once
#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H

#include "resources.h"
#include "Animations.h"
#include "Collider2D.h"
#include "Game.h"
#include "QuadTree.h"
#include "Sprites.h"
#include "GameEnv.h"
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

	float hp = 10; // default hp
	float damage;

	bool rendering = false;
	bool ground;
	bool active = true;
	bool invicible = false;
	bool suffering = false;

	std::vector<STriggerTag> triggerTags;

	std::vector<CQuadTree*> selfNodes;
	int selfIndexInNode = -1;

	std::unordered_map<std::string, LPSPRITE> sprites;
	std::unordered_map<std::string, LPANIMATION> animations;

public:
	float duration;
	DWORD sufferingStart;

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
	void AddSelfNodeQt(CQuadTree* node) { this->selfNodes.push_back(node); }
	void ClearSelfNodesQt() { this->selfNodes.clear(); }
	std::vector<CQuadTree*> GetSelfNodesQt() { return this->selfNodes; }
	void SetSelfIndexInNodeQt(int index) { this->selfIndexInNode = index; }
	int GetSelfIndexInNodeQt() { return this->selfIndexInNode; }

	// collider
	void SetColliders(std::vector<CCollider2D*> colliders) { this->colliders = colliders; }
	std::vector<CCollider2D*> GetColliders() { return this->colliders; }

	// active
	void SetActive(bool value) { this->active = value; }
	bool IsActive() { return this->active; }

	// hp
	void TakeDamage(LPCOLLISIONEVENT& bulletCollision);
	void SetHp(float hp) { this->hp = hp; }
	float GetHp() { return this->hp; }
	bool IsLive() { return this->hp > 0; }

	// damage
	void SetDamage(float damage) { this->damage = damage; }
	float GetDamage() { return this->damage; }

	// invisible
	void SetInvisible(bool value) { this->invicible = true; }
	bool IsInvisible() { return this->invicible; }

	// invisible with
	void AddTriggerTag(STriggerTag tag) { this->triggerTags.push_back(tag); }
	void ClearTriggerTag() { this->triggerTags.clear(); }
	std::vector<STriggerTag> GetTriggerTag() { return this->triggerTags; }

	// suffering
	void SetSuffering(bool value) { this->suffering = value; this->sufferingStart = GetTickCount64(); }
	bool IsSuffering() { return this->suffering; }

	// virtual
	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0;
	virtual void PhysicalUpdate(std::vector<LPGAMEOBJECT>* coObjects);
	virtual void OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent);
	virtual void OnTrigger(CCollider2D* self, LPCOLLISIONEVENT coEvent);

	virtual void FilterTriggerTag();

	~CGameObject();
};
typedef CGameObject* LPGAMEOBJECT;

#endif // !_GAMEOBJECT_H

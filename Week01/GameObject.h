#pragma once
#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H

#include <math.h>
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
using LPCOLLISIONEVENT = SCollisionEvent*;
class CQuadTree;
class CCollider2D;
class CGameObject
{
protected:

	Vector2D position;
	Vector2D velocity;
	std::vector<CCollider2D*> colliders;

	int nx;

	int level = 1;
	float hp = 10; // default hp
	float damage;
	float bonusDamage = 0;

	float rotateZ = 0;

	bool rendering = false;
	bool ground;
	bool active = true;
	bool invicible = false;
	bool effected = false;

	DWORD effectDuration;
	DWORD initTime = GetTickCount64();
	
	std::vector<STriggerTag> triggerTags;

	std::vector<CQuadTree*> selfNodes;
	int selfIndexInNode = -1;

	std::unordered_map<std::string, LPSPRITE> sprites;
	std::unordered_map<std::string, LPANIMATION> animations;

public:
	float angular;

	CGameObject();

	// position
	void SetPosition(Vector2D position) { this->position = position; }
	Vector2D GetPosition() const;
	void SetX(float newX);
	void SetY(float newY);
	void SetNx(int newNX);
	float GetX() const;
	float GetY() const;
	int GetNx() const;

	// velocity
	void SetVelocity(Vector2D velocity) { this->velocity = velocity; }
	Vector2D GetVelocity() const { return this->velocity; }

	// sprite
	void AddSprite(std::string key, std::string spriteId);
	std::unordered_map<std::string, LPSPRITE> GetSprites() const { return this->sprites; }

	// animation
	void AddAnimation(std::string key, std::string animationId);
	std::unordered_map<std::string, LPANIMATION> GetAnimations() { return this->animations; }

	// quadtree
	void AddSelfNodeQt(CQuadTree* node) { this->selfNodes.push_back(node); }
	void ClearSelfNodesQt() { this->selfNodes.clear(); }
	std::vector<CQuadTree*> GetSelfNodesQt() { return this->selfNodes; }
	void SetSelfIndexInNodeQt(int index) { this->selfIndexInNode = index; }
	int GetSelfIndexInNodeQt() const { return this->selfIndexInNode; }

	// collider
	void SetColliders(const std::vector<CCollider2D*>& colliders) { this->colliders = colliders; }
	std::vector<CCollider2D*> GetColliders() const { return this->colliders; }
	
	// rendering status
	void SetRendering(bool value) { this->rendering = value; }
	bool IsRendering() const { return this->rendering; }

	// active status
	void SetActive(bool value) { this->active = value; }
	bool IsActive() const { return this->active; }

	// hero point
	void TakeDamage(const float& damage);
	void SetHp(const float hp) { this->hp = hp; }
	float GetHp() const { return this->hp; }
	bool IsLive() const { return this->hp > 0; }

	// level
	void SetLevel(const int& value) { this->level = level; }
	int GetLevel()const { return this->level; }

	// damage
	void SetDamage(const float& damage) { this->damage = damage; }
	float GetDamage() const { return this->damage; }
	void SetBonusDamage(const float& bonusValue) { this->bonusDamage += bonusValue; }
	float GetBonusDamage() const { return this->bonusDamage; }

	// visible status
	void SetInvisible(const bool& value) { this->invicible = value; }
	bool IsInvisible() const { return this->invicible; }

	// trigger tag
	void AddTriggerTag(STriggerTag tag) { this->triggerTags.push_back(tag); }
	std::vector<STriggerTag> GetTriggerTag() const { return this->triggerTags; }
	void CleanTriggerTag();

	// effect
	void SetInEffect(const bool& value) { this->effected = value; this->effectDuration = 1; }
	bool IsEffected() const { return this->effected; }

	// ratationZ
	void SetRotationZ(float value) { this->rotateZ = value; }
	float GetRotationZ() { return this->rotateZ; }

	void ActiveByRadiusDistance(const float& activeDistance);
	virtual D3DCOLOR GetRenderColor();


	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0;
	virtual void PhysicalUpdate(std::vector<LPGAMEOBJECT>* coObjects);
	virtual void OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent);
	virtual void OnTrigger(CCollider2D* self, LPCOLLISIONEVENT coEvent);

	~CGameObject();
};
using LPGAMEOBJECT = CGameObject*;

#endif // !_GAMEOBJECT_H

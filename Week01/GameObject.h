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
	bool effected = false;

	DWORD effectDuration;
	DWORD initTime = GetTickCount64();
	
	std::vector<STriggerTag> triggerTags;

	std::vector<CQuadTree*> selfNodes;
	int selfIndexInNode = -1;

	std::unordered_map<std::string, LPSPRITE> sprites;
	std::unordered_map<std::string, LPANIMATION> animations;

public:
	float duration;

	CGameObject();

	/*
		Position	
	*/
	void SetPosition(Vector2D position) { this->position = position; }
	Vector2D GetPosition();
	void SetX(float newX);
	void SetY(float newY);
	void SetNx(int newNX);
	float GetX();
	float GetY();
	int GetNx();

	/*
		Velocity
	*/
	void SetVelocity(Vector2D velocity) { this->velocity = velocity; }
	Vector2D GetVelocity() { return this->velocity; }

	/*
		Sprites of object
	*/
	void AddSprite(std::string key, std::string spriteId);
	std::unordered_map<std::string, LPSPRITE> GetSprites() { return this->sprites; }

	/*
		Animations of object
	*/
	void AddAnimation(std::string key, std::string animationId);
	std::unordered_map<std::string, LPANIMATION> GetAnimations() { return this->animations; }

	/*
		QuadtreeNode address of object
	*/
	void AddSelfNodeQt(CQuadTree* node) { this->selfNodes.push_back(node); }
	void ClearSelfNodesQt() { this->selfNodes.clear(); }
	std::vector<CQuadTree*> GetSelfNodesQt() { return this->selfNodes; }
	void SetSelfIndexInNodeQt(int index) { this->selfIndexInNode = index; }
	int GetSelfIndexInNodeQt() { return this->selfIndexInNode; }

	/*
		Collider
	*/
	void SetColliders(std::vector<CCollider2D*> colliders) { this->colliders = colliders; }
	std::vector<CCollider2D*> GetColliders() { return this->colliders; }
	
	/*
		Rendering status
	*/
	void SetRendering(bool value) { this->rendering = value; }
	bool IsRendering() { return this->rendering; }

	/*
		Active status
	*/
	void SetActive(bool value) { this->active = value; }
	bool IsActive() { return this->active; }

	/*
		Hero point
	*/
	void TakeDamage(float damage);
	void SetHp(float hp) { this->hp = hp; }
	float GetHp() { return this->hp; }
	bool IsLive() { return this->hp > 0; }

	/*
		Damage
	*/
	void SetDamage(float damage) { this->damage = damage; }
	float GetDamage() { return this->damage; }

	/*
		Visible status
	*/
	void SetInvisible(bool value) { this->invicible = true; }
	bool IsInvisible() { return this->invicible; }

	/*
		Triggertag
	*/
	void AddTriggerTag(STriggerTag tag) { this->triggerTags.push_back(tag); }
	std::vector<STriggerTag> GetTriggerTag() { return this->triggerTags; }
	void CleanTriggerTag();

	/*
		Effect when take damage
	*/
	void SetInEffect(bool value) { this->effected = value; this->effectDuration = 1; }
	bool IsEffected() { return this->effected; }


	void ActiveByRadiusDistance(float activeDistance);
	D3DCOLOR GetRenderColor();


	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0;
	virtual void PhysicalUpdate(std::vector<LPGAMEOBJECT>* coObjects);
	virtual void OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent);
	virtual void OnTrigger(CCollider2D* self, LPCOLLISIONEVENT coEvent);
	virtual void OnOverlapped(CCollider2D* self, LPCOLLISIONEVENT coEvent);


	~CGameObject();
};
typedef CGameObject* LPGAMEOBJECT;

#endif // !_GAMEOBJECT_H

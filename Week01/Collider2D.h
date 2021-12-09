#pragma once
#ifndef _COLLIDER2D_H
#define _COLLIDER2D_H

#include <algorithm>
#include "GameObject.h"
#include "Transform.h"

class CGameObject;
typedef CGameObject* LPGAMEOBJECT;
class CCollider2D;
struct SCollisionEvent;
typedef SCollisionEvent* LPCOLLISIONEVENT;

struct SCollisionEvent
{
	LPGAMEOBJECT object;
	CCollider2D* collider;
	float nx, ny, t;

	bool deleted;

	SCollisionEvent(float t, float nx, float ny,
		LPGAMEOBJECT object = nullptr, CCollider2D* collider = nullptr) {
		this->t = t;
		this->nx = nx;
		this->ny = ny;
		this->object = object;
		this->collider = collider;
		this->deleted = false;
	}

	static bool compare(const LPCOLLISIONEVENT& a, LPCOLLISIONEVENT& b) {
		return a->t < b->t;
	}
};

class CCollider2D {
private:
	std::vector<LPCOLLISIONEVENT> coEvents;
	LPCOLLISIONEVENT coEventX;
	LPCOLLISIONEVENT coEventY;

protected:
	float dx;
	float dy;
	bool trigger = false;
	bool dynamic = false;
	LPGAMEOBJECT object;
	SRect boundingBox;
	Vector2D offset;
	Vector2D boxSize;

public:
	CCollider2D();
	CCollider2D(LPGAMEOBJECT object, bool dynamic, bool trigger, Vector2D offset, Vector2D boxSize);

	static void SweptAABB(SRect movingRect, SRect staticRect,
		float dx, float dy,
		float& nx, float& ny, float& dt);
	LPCOLLISIONEVENT SweptAABBEx(CCollider2D* coOther);
	void PredictPotentialCollision(std::vector<LPGAMEOBJECT>* coObject, 
		std::vector<LPCOLLISIONEVENT>& coEvents);
	void FilterCollision(std::vector<LPCOLLISIONEVENT>& coEvents,
		LPCOLLISIONEVENT& colX, LPCOLLISIONEVENT& colY,
		bool filterX, bool filterY);
	void PhysicalUpdate(std::vector<LPGAMEOBJECT>* coObjects);

	// dynamic
	void SetDynamic(bool value) { this->dynamic = value; }
	bool IsDynamic() { return this->dynamic; }

	// trigger
	void SetTrigger(bool value) { this->trigger = value; }
	bool IsTrigger() { return this->trigger; }

	// object
	void SetGameObject(LPGAMEOBJECT gameObj) { this->object = gameObj; }
	LPGAMEOBJECT GetGameObject() { return this->object; }

	// offset
	void SetOffset(Vector2D offset) { this->offset = offset; }
	Vector2D GetOffSet() { return this->offset; }

	// boxsize
	void SetBoxSize(Vector2D size) { this->boxSize = size; }
	Vector2D GetBoxSize() { return this->boxSize; }

	// bounding box
	void SetBoundingBox(const SRect& bounding) { this->boundingBox = bounding; }
	SRect GetBoundingBox();
	void RenderBoundingBox();
};

#endif // !_COLLIDER2D_H

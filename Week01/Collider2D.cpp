#include "Collider2D.h"
#include "Textures.h"

#include "Jason.h"
#include "Sophia.h"

#define MARGIN_COLLISION		0.2f

CCollider2D::CCollider2D()
{
}

CCollider2D::CCollider2D(LPGAMEOBJECT object, bool dynamic, bool trigger, Vector2D offset, Vector2D boxSize)
{
	this->object = object;
	this->dynamic = dynamic;
	this->trigger = trigger;
	this->offset = offset;
	this->boxSize = boxSize;
}

void CCollider2D::SweptAABB(SRect movingRect, SRect staticRect,
	float dx, float dy, float& nx, float& ny, float& dt)
{
	float dxEntry, dxExit, txEntry, txExit;
	float dyEntry, dyExit, tyEntry, tyExit;

	float tEntry, tExit;

	dt = -1.0f;			// no collision
	nx = ny = 0.0f;

	//
	// Broad-phase test 
	//

	SRect rBroadPhase;
	rBroadPhase.left = dx > 0 ? movingRect.left : movingRect.left + dx;
	rBroadPhase.top = dy > 0 ? movingRect.top + dy : movingRect.top;
	rBroadPhase.right = dx > 0 ? movingRect.right + dx : movingRect.right;
	rBroadPhase.bottom = dy > 0 ? movingRect.bottom : movingRect.bottom + dy;

	if (!rBroadPhase.Overlap(staticRect)) return;

	if (dx == 0 && dy == 0) return;		// moving object is not moving > obvious no collision

	if (dx > 0)
	{
		dxEntry = staticRect.left - movingRect.right;
		dxExit = staticRect.right - movingRect.left;
	}
	else if (dx < 0)
	{
		dxEntry = staticRect.right - movingRect.left;
		dxExit = staticRect.left - movingRect.right;
	}

	if (dy > 0)
	{
		dyEntry = staticRect.bottom - movingRect.top;
		dyExit = staticRect.top - movingRect.bottom;
	}
	else if (dy < 0)
	{
		dyEntry = staticRect.top - movingRect.bottom;
		dyExit = staticRect.bottom - movingRect.top;
	}

	if (dx == 0)
	{
		txEntry = -VectorInfinity().x;
		txExit = VectorInfinity().x;
	}
	else
	{
		txEntry = dxEntry / dx;
		txExit = dxExit / dx;
	}

	if (dy == 0)
	{
		tyEntry = -VectorInfinity().y;
		tyExit = VectorInfinity().y;
	}
	else
	{
		tyEntry = dyEntry / dy;
		tyExit = dyExit / dy;
	}

	if ((txEntry < 0.0f && tyEntry < 0.0f)
		|| txEntry > 1.0f || tyEntry > 1.0f) {
		return;
	}

	tEntry = max(txEntry, tyEntry);
	tExit = min(txExit, tyExit);

	if (tEntry > tExit)
		return; // end

	dt = tEntry;

	if (txEntry > tyEntry)
	{
		ny = 0.0f;
		dx > 0 ? nx = -1.0f : nx = 1.0f;
	}
	else
	{
		nx = 0.0f;
		dy > 0 ? ny = -1.0f : ny = 1.0f;
	}
}

LPCOLLISIONEVENT CCollider2D::SweptAABBEx(CCollider2D* coOther)
{
	SRect staticRect;
	SRect movingRect;
	float t, nx, ny;

	staticRect = coOther->GetBoundingBox();

	auto coObject = coOther->GetGameObject();
	DWORD deltaTime = CGame::GetDeltaTime();
	float sdx = coObject->GetVelocity().x * deltaTime;
	float sdy = coObject->GetVelocity().y * deltaTime;

	Vector2D selfVelocity = this->object->GetVelocity();
	this->dx = selfVelocity.x * deltaTime;
	this->dy = selfVelocity.y * deltaTime;

	float rdx = this->dx - sdx;
	float rdy = this->dy - sdy;

	movingRect = this->GetBoundingBox();

	this->SweptAABB(
		movingRect, staticRect,
		rdx, rdy, nx, ny, t);

	SCollisionEvent* e = new SCollisionEvent(t, nx, ny, coObject, coOther);
	return e;
}

void CCollider2D::PredictPotentialCollision(std::vector<LPGAMEOBJECT>* coObjects, 
	std::vector<LPCOLLISIONEVENT>& coEvents)
{
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		auto coObject = coObjects->at(i);

		if (this->object == coObject)
			continue;

		if (coObject->IsLive() == false)
			continue;

		if (coObject->IsActive() == false)
			continue;

		// check trigger tag
		bool activeTrigger = false;
		for (auto &triggerObject : this->object->GetTriggerTag()) {
			LPGAMEOBJECT tagTarget = triggerObject.target;
			if (tagTarget == coObject)
				activeTrigger = true;
		}
		if (activeTrigger)
			continue;

		for (auto co : coObject->GetColliders())
		{
			LPCOLLISIONEVENT e = this->SweptAABBEx(co);

			if (e->t > 0 && e->t <= 1.0f) {
				coEvents.push_back(e);
			}
			else {
				delete e;
			}
		}
	}

	std::sort(coEvents.begin(), coEvents.end(), SCollisionEvent::compare);
}

void CCollider2D::FilterCollision(std::vector<LPCOLLISIONEVENT>& coEvents, 
	LPCOLLISIONEVENT& colX, LPCOLLISIONEVENT& colY, 
	bool filterX = true, bool filterY = true)
{
	float minTx, minTy;

	minTx = 1.0f;
	minTy = 1.0f;
	int minIX = -1;
	int minIY = -1;

	int coEventsSize = coEvents.size();

	for (UINT i = 0; i < coEventsSize; i++)
	{
		LPCOLLISIONEVENT collisionEvent = coEvents.at(i);
		
		if (collisionEvent->deleted || collisionEvent->collider->IsTrigger())
			continue;

		if (collisionEvent->t < minTx && collisionEvent->nx != 0 && filterX) {
			minTx = collisionEvent->t; 
			minIX = i;
		}

		if (collisionEvent->t < minTy && collisionEvent->ny != 0 && filterY) {
			minTy = collisionEvent->t; 
			minIY = i;
		}
	}

	if (minIX >= 0) {
		colX = coEvents[minIX];
	}
	if (minIY >= 0) {
		colY = coEvents[minIY];
	}
}

void CCollider2D::PhysicalUpdate(std::vector<LPGAMEOBJECT>* coObjects)
{
	// null, not dynamic, not active
	if (this->object == nullptr || !this->dynamic
		|| !this->object->IsActive()) {
		return;
	}

	this->PhysicalOverlapHandler(coObjects);

	// get delta time
	auto deltaTime = CGame::GetDeltaTime();
	// get object selfPosition, selfVelocity
	auto selfPosition = this->object->GetPosition();
	auto selfVelocity = this->object->GetVelocity();

	this->dx = selfVelocity.x * deltaTime;
	this->dy = selfVelocity.y * deltaTime;

	this->coEvents.clear();
	this->coEventX = nullptr;
	this->coEventY = nullptr;

	PredictPotentialCollision(coObjects, this->coEvents);

	if (this->coEvents.size() == 0)
	{
		selfPosition.x += dx;
		selfPosition.y += dy;
	}
	else
	{
		FilterCollision(this->coEvents, this->coEventX, this->coEventY);

		if (this->coEventX != nullptr && this->coEventY != nullptr)
		{
			// collision y first
			if (this->coEventY->t < this->coEventX->t)
			{
				if (this->trigger == false)
				{
					selfPosition.y += this->coEventY->t * this->dy + this->coEventY->ny * MARGIN_COLLISION;

					selfVelocity.y = 0;
					this->object->SetVelocity(selfVelocity);
				}
				else {
					selfPosition.y += this->dy;
				}

				this->object->SetPosition(selfPosition);

				if (this->coEventY->ny != 0) {
					if (this->trigger == false) {
						this->object->OnCollision(this, this->coEventY);
					}
					else {
						this->object->OnTrigger(this, this->coEventY);
					}
				}

				//
				// see if after correction on Y, is there still a collision on X ? 
				//
				LPCOLLISIONEVENT colX_other = nullptr;

				this->coEventX->deleted = true;

				// replace with a new collision event using corrected location 
				this->coEvents.push_back(SweptAABBEx(this->coEventX->collider));

				// re-filter on X only
				FilterCollision(this->coEvents, colX_other, this->coEventY, true, false);

				if (colX_other != nullptr)
				{
					if (this->trigger == false) {
						selfPosition.x += colX_other->t * this->dx + colX_other->nx * MARGIN_COLLISION;
					}

					selfVelocity.x = 0;
					this->object->SetVelocity(selfVelocity);

					if (this->trigger == false) {
						this->object->OnCollision(this, colX_other);
					}
					else {
						this->object->OnTrigger(this, colX_other);
					}
				}
				else
				{
					selfPosition.x += this->dx;
				}
			}
			// collision on X first
			else
			{
				if (this->trigger == false)
				{
					selfPosition.x += this->coEventX->t * this->dx + this->coEventX->nx * MARGIN_COLLISION;

					selfVelocity.x = 0;
					this->object->SetVelocity(selfVelocity);
				}
				else {
					selfPosition.x += this->dx;
				}

				this->object->SetPosition(selfPosition);

				if (this->coEventX->nx != 0) {
					if (this->trigger == false) {
						this->object->OnCollision(this, coEventX);
					}
					else {
						this->object->OnTrigger(this, this->coEventX);
					}
				}

				//
				// see if after correction on X, is there still a collision on Y ? 
				//
				LPCOLLISIONEVENT colY_other = nullptr;

				this->coEventY->deleted = true;

				// replace with a new collision event using corrected location 
				this->coEvents.push_back(SweptAABBEx(this->coEventY->collider));

				// re-filter on X only
				FilterCollision(this->coEvents, this->coEventX, colY_other, false, true);

				if (colY_other != nullptr)
				{
					if (this->trigger == false) {
						selfPosition.y += colY_other->t * this->dy + colY_other->ny * MARGIN_COLLISION;
					}

					selfVelocity.x = 0;
					object->SetVelocity(selfVelocity);

					if (this->trigger == false) {
						this->object->OnCollision(this, colY_other);
					}
					else {
						this->object->OnTrigger(this, colY_other);
					}
				}
				else
				{
					selfPosition.y += this->dy;
				}
			}
		}
		else
		{
			if (this->coEventX != nullptr)
			{
				if (this->trigger == false)
				{
					selfPosition.x += this->coEventX->t * this->dx + this->coEventX->nx * MARGIN_COLLISION;
					selfPosition.y += this->dy;

					selfVelocity.x = 0;
					this->object->SetVelocity(selfVelocity);
					this->object->OnCollision(this, this->coEventX);
				}
				else {
					selfPosition.x += this->dx;
					selfPosition.y += this->dy;
					this->object->OnTrigger(this, this->coEventX);
				}
			}
			else
			{
				if (this->coEventY != nullptr)
				{
					if (this->trigger == false)
					{
						selfPosition.x += this->dx;
						selfPosition.y += this->coEventY->t * this->dy + this->coEventY->ny * MARGIN_COLLISION;

						selfVelocity.y = 0;
						this->object->SetVelocity(selfVelocity);
						this->object->OnCollision(this, this->coEventY);
					}
					else {
						selfPosition.x += this->dx;
						selfPosition.y += this->dy;
						this->object->OnTrigger(this, this->coEventY);
					}
				}
				// both colX & colY are NULL 
				else
				{
					selfPosition.x += this->dx;
					selfPosition.y += this->dy;
				}
			}
		}
	}

	this->object->SetPosition(selfPosition);

	for (UINT i = 0; i < this->coEvents.size(); i++) {
		if (this->coEvents.at(i)->collider->IsTrigger()) {
			if (this->trigger == false) {
				this->object->OnCollision(this, this->coEvents.at(i));
			}
			else {
				this->object->OnTrigger(this, this->coEvents.at(i));
			}
		}
	}

	for (UINT i = 0; i < this->coEvents.size(); i++) {
		delete this->coEvents.at(i);
	}
}

void CCollider2D::PhysicalOverlapHandler(std::vector<LPGAMEOBJECT>* coObjects)
{
	if (this->trigger == true) return;

	std::vector<CGameObject*> overlappedObjects;

	for (auto coObject : *coObjects)
	{
		if (coObject == object) continue;
		if (coObject->IsActive() == false) continue;
		if (coObject->GetColliders().size() == 0) continue;

		auto coOther = coObject->GetColliders().at(0);
		if (coOther->trigger == true) continue;

		auto bbOther = coOther->GetBoundingBox();
		auto bbSelf = GetBoundingBox();

		if (bbSelf.Overlap(bbOther) && dynamic_cast<CBrick*>(coObject))
			overlappedObjects.emplace_back(coObject);
	}

	for (auto coObject : overlappedObjects)
	{
		auto bbOther = coObject->GetColliders().at(0)->GetBoundingBox();
		auto bbSelf = GetBoundingBox();

		if (bbSelf.Overlap(bbOther) == false) continue;

		float deltaX = 0, deltaY = 0;

		if (bbSelf.left < bbOther.right && bbSelf.left > bbOther.left)
		{
			deltaX += bbOther.right - bbSelf.left + MARGIN_COLLISION;
		}

		if (bbSelf.right > bbOther.left && bbSelf.right < bbOther.right)
		{
			deltaX += -1 * (bbSelf.right - bbOther.left + MARGIN_COLLISION);
		}

		if (bbSelf.bottom < bbOther.top && bbSelf.bottom > bbOther.bottom)
		{
			deltaY += bbOther.top - bbSelf.bottom + MARGIN_COLLISION;
		}

		if (bbSelf.top > bbOther.bottom && bbSelf.top < bbOther.top)
		{
			deltaY += -1 * (bbSelf.top - bbOther.bottom + MARGIN_COLLISION);
		}

		if (deltaX != 0 && deltaY != 0)
		{
			if (abs(deltaX) <= abs(deltaY))
			{
				deltaY = 0;
			}
			else deltaX = 0;
		}

		auto newPos = object->GetPosition();
		newPos += Vector2D(deltaX, deltaY);
		object->SetPosition(newPos);
	}
}

SRect CCollider2D::GetBoundingBox()
{
	Vector2D posCollider = object->GetPosition() + offset;
	SRect boundingBox;
	boundingBox.left = posCollider.x - boxSize.x / 2;
	boundingBox.top = posCollider.y + boxSize.y / 2;
	boundingBox.right = posCollider.x + boxSize.x / 2;
	boundingBox.bottom = posCollider.y - boxSize.y / 2;
	return boundingBox;
}

void CCollider2D::RenderBoundingBox()
{
	Vector2D positionCollider = this->object->GetPosition() + this->offset;
	LPDIRECT3DTEXTURE9 bbox = CTextures::GetInstance()->Get(20); // texId 20: bbox for render collider
	SRect rect;
	rect.left = 0;
	rect.top = 0;
	rect.right = this->boxSize.x;
	rect.bottom = this->boxSize.y;

	D3DCOLOR color = D3DCOLOR_ARGB(40, 255, 255, 255);
	CGame::GetInstance()->Draw(positionCollider, -1, bbox, rect.left, rect.top, rect.right, rect.bottom, color);
}
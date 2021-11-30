#include "Collider2D.h"
#include "Textures.h"

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

	SRect boardPhase;
	boardPhase.left = dx > 0 ? movingRect.left : movingRect.left + dx;
	boardPhase.top = dy > 0 ? movingRect.top + dy : movingRect.top;
	boardPhase.right = dx > 0 ? movingRect.right + dx : movingRect.right;
	boardPhase.bottom = dy > 0 ? movingRect.bottom : movingRect.bottom + dy;

	if (!boardPhase.Overlap(staticRect)) return;

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

	if ((txEntry < 0.0f && tyEntry < 0.0f) || txEntry > 1.0f || tyEntry > 1.0f) return;

	tEntry = max(txEntry, tyEntry);
	tExit = min(txExit, tyExit);

	if (tEntry > tExit) return;

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
	SRect staticRect;		// static object bbox
	SRect movingRect;		// moving object bbox
	float t, nx, ny;

	staticRect = coOther->GetBoundingBox();

	// deal with moving object: m speed = original m speed - collide object speed
	auto coObject = coOther->GetGameObject();
	float sdx = coObject->GetVelocity().x * CGame::GetDeltaTime();
	float sdy = coObject->GetVelocity().y * CGame::GetDeltaTime();

	// (rdx, rdy) is RELATIVE movement distance/velocity 
	float rdx = this->dx - sdx;
	float rdy = this->dy - sdy;

	movingRect = GetBoundingBox();

	SweptAABB(
		movingRect, staticRect,
		rdx, rdy, nx, ny, t);

	auto e = new SCollisionEvent(t, nx, ny, coObject, coOther);
	return e;
}

void CCollider2D::PredictPotentialCollision(std::vector<LPGAMEOBJECT>* coObjects, 
	std::vector<LPCOLLISIONEVENT>& coEvents)
{
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		auto coObject = coObjects->at(i);
		if (this->object != coObject) {
			for (auto co : coObject->GetColliders())
			{
				LPCOLLISIONEVENT e = SweptAABBEx(co);

				if (e->t > 0 && e->t <= 1.0f)
					coEvents.push_back(e);
				else
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
	float minTX, minTY;

	minTX = 1.0f;
	minTY = 1.0f;
	int minIX = -1;
	int minIY = -1;

	for (UINT i = 0; i < coEvents.size(); i++)
	{
		LPCOLLISIONEVENT c = coEvents[i];

		if (c->t < minTX && c->nx != 0 && filterX == true) {
			minTX = c->t; minIX = i;
		}

		if (c->t < minTY && c->ny != 0 && filterY == true) {
			minTY = c->t; minIY = i;
		}
	}

	if (minIX >= 0) colX = coEvents[minIX];
	if (minIY >= 0) colY = coEvents[minIY];
}

void CCollider2D::PhysicalUpdate(std::vector<LPGAMEOBJECT>* coObjects)
{
	// Reduce the number of check collision if game object is not enabled, is nullptr, static
	if (object == nullptr || this->dynamic == false) return;

	auto dt = CGame::GetDeltaTime();
	auto position = object->GetPosition();
	auto velocity = object->GetVelocity();

	this->dx = velocity.x * dt;
	this->dy = velocity.y * dt;

	this->coEvents.clear();
	this->coEventX = NULL;
	this->coEventY = NULL;

	PredictPotentialCollision(coObjects, this->coEvents);

	if (this->coEvents.size() == 0)
	{
		position.x += dx;
		position.y += dy;
		this->object->SetPosition(position);
	}
	else
	{
		FilterCollision(this->coEvents, this->coEventX, this->coEventY);

		if (this->coEventX != NULL && this->coEventY != NULL)
		{
			// was collision on Y first ?
			if (this->coEventY->t < this->coEventX->t)
			{
				if (this->trigger == false)
				{
					position.y += this->coEventY->t * dy + this->coEventY->ny * 0.4f;
					this->object->SetPosition(position);

					if (this->coEventY->ny != 0) {
						velocity.y = 0;
					}
					this->object->SetVelocity(velocity);
				}

				if (this->coEventY->ny != 0)
					if (this->trigger == false) {
						this->object->OnCollision(this, this->coEventY);
					}
					else {
						this->object->OnTrigger(this, coEventY);
					}

				//
				// see if after correction on Y, is there still a collision on X ? 
				//
				LPCOLLISIONEVENT colX_other = NULL;

				//
				// check again if there is true collision on X 
				//

				// replace with a new collision event using corrected location 
				this->coEvents.push_back(SweptAABBEx(coEventX->collider));

				// re-filter on X only
				FilterCollision(this->coEvents, colX_other, this->coEventY, /*filterX=*/1, /*filterY=*/0);

				if (colX_other != NULL)
				{
					position.x += colX_other->t * dx + colX_other->nx * 0.4f;
					/*object->SetPosition(position);*/

					if (this->trigger == false) {
						this->object->OnCollision(this, colX_other);
					}
					else {
						this->object->OnTrigger(this, colX_other);
					}
				}
				else
				{
					position.x += dx;
				}
			}
			// collision on X first
			else
			{
				if (this->trigger == false)
				{
					position.x += this->coEventX->t * dx + this->coEventX->nx * 0.4f;
					this->object->SetPosition(position);

					if (this->coEventX->nx != 0) {
						velocity.x = 0;
					}
					this->object->SetVelocity(velocity);
				}

				if (this->coEventX->nx != 0)
					if (this->trigger == false) {
						this->object->OnCollision(this, this->coEventX);
					}
					else { 
						this->object->OnTrigger(this, this->coEventX);
					}

				//
				// see if after correction on X, is there still a collision on Y ? 
				//
				LPCOLLISIONEVENT colY_other = NULL;

				//
				// check again if there is true collision on X 
				//

				// replace with a new collision event using corrected location 
				this->coEvents.push_back(SweptAABBEx(coEventY->collider));

				// re-filter on X only
				FilterCollision(this->coEvents, this->coEventX, colY_other, /*filterX=*/0, /*filterY=*/1);

				if (colY_other != NULL)
				{
					position.y += colY_other->t * dy + colY_other->ny * 0.4f;

					if (this->trigger == false) {
						this->object->OnCollision(this, colY_other);
					}
					else {
						this->object->OnTrigger(this, colY_other);
					}
				}
				else
				{
					position.y += dy;
				}
			}
		}
		else
		{
			if (this->coEventX != NULL)
			{
				if (this->trigger == false)
				{
					position.x += this->coEventX->t * dx + this->coEventX->nx * 0.4f;
					position.y += dy;
					this->object->SetPosition(position);

					if (this->coEventX->nx != 0) {
						velocity.x = 0;
					}
					this->object->SetVelocity(velocity);
				}

				if (this->trigger == false) {
					this->object->OnCollision(this, this->coEventX);
				}
				else {
					this->object->OnTrigger(this, this->coEventX);
				}
			}
			else
			{
				if (this->coEventY != NULL)
				{
					if (this->trigger == false)
					{
						position.x += dx;
						position.y += this->coEventY->t * dy + this->coEventY->ny * 0.4f;
						this->object->SetPosition(position);

						if (this->coEventY->ny != 0) {
							velocity.y = 0;
						}
						this->object->SetVelocity(velocity);
					}

					if (this->trigger == false)
					{
						this->object->OnCollision(this, this->coEventY);
					}
					else {
						this->object->OnTrigger(this, this->coEventY);
					}
				}
				// both colX & colY are NULL 
				else
				{
					position.x += dx;
					position.y += dy;
				}
			}
		}

		this->object->SetPosition(position);
	}

	for (UINT i = 0; i < this->coEvents.size(); i++) {
		delete this->coEvents[i];
	}
}

SRect CCollider2D::GetBoundingBox()
{
	Vector2D positionCollider = this->object->GetPosition() + this->offset;
	SRect bounding;
	bounding.left = positionCollider.x - this->boxSize.x / 2;
	bounding.top = positionCollider.y + this->boxSize.y / 2;
	bounding.right = positionCollider.x + this->boxSize.x / 2;
	bounding.bottom = positionCollider.y - this->boxSize.y / 2;
	return bounding;
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

	CGame::GetInstance()->Draw(positionCollider, -1, bbox, rect.left, rect.top, rect.right, rect.bottom, 100);
	
}
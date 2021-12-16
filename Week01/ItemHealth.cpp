#include "ItemHealth.h"
#include "Sophia.h"

#define V_BOXSIZE			Vector2D(16.0f, 16.0f)
#define	SPRITE_DEFAULT_ID	"df"

CItemHealth::CItemHealth()
{
	this->AddSprite(SPRITE_DEFAULT_ID, "sprItemHealth");
	
	this->hp = 1;
	this->damage = 0;

	//
	CCollider2D* collider = new CCollider2D(this, false, true, VectorZero(), V_BOXSIZE);
	this->colliders.push_back(collider);
	this->SetColliders(this->colliders);
}

void CItemHealth::Update(DWORD dt)
{
}

void CItemHealth::Render()
{
	this->sprites.at(SPRITE_DEFAULT_ID)->Draw(this->position, this->nx, DRAW_COLOR_DEFAULT);
}

void CItemHealth::OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent)
{
}

void CItemHealth::OnTrigger(CCollider2D* self, LPCOLLISIONEVENT coEvent)
{
	/*if (dynamic_cast<CSophia*>(coEvent->object)) {
		CSophia* sophia = (CSophia*)coEvent->object;
		sophia->RecoverHealth(this->recoverHeath);
		this->hp = 0;
	}*/
}

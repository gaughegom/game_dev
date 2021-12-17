#include "ItemHealth.h"
#include "Sophia.h"

#define V_BOXSIZE			Vector2D(16.0f, 16.0f)

constexpr auto SPRITE_DEFAULT_ID = "df";
constexpr auto EFFECT_TIME		= 1800;
constexpr auto LIFE_TIME		= 2500;

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
	DWORD now = GetTickCount64();
	if (now - this->initTime <= LIFE_TIME && now - this->initTime >= EFFECT_TIME) {
		this->effected = true;
	}
	else if (now - this->initTime > LIFE_TIME) {
		this->hp = 0;
	}
}

void CItemHealth::Render()
{
	D3DCOLOR color = this->GetRenderColor();
	this->sprites.at(SPRITE_DEFAULT_ID)->Draw(this->position, this->nx, color);
}

void CItemHealth::OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent)
{
}

void CItemHealth::OnTrigger(CCollider2D* self, LPCOLLISIONEVENT coEvent)
{
}

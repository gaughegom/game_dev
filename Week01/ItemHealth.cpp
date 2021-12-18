#include "ItemHealth.h"
#include "Sophia.h"

#define V_BOXSIZE			Vector2D(16.0f, 16.0f)

constexpr auto SpriteDefaultId = "df";
constexpr auto EffectTime = 800;
constexpr auto LifeTime	= 4000;

CItemHealth::CItemHealth()
{
	this->AddSprite(SpriteDefaultId, "sprItemHealth");
	
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
	if (this->effected == false && now - this->initTime > LifeTime - EffectTime) {
		this->SetInEffect(true);
	}
	else if (now - this->initTime > LifeTime) {
		this->hp = 0;
	}
}

void CItemHealth::Render()
{
	D3DCOLOR color = this->GetRenderColor();
	this->sprites.at(SpriteDefaultId)->Draw(this->position, this->nx, color);
}

void CItemHealth::OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent)
{
}

void CItemHealth::OnTrigger(CCollider2D* self, LPCOLLISIONEVENT coEvent)
{
}

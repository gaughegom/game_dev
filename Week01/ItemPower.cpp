#include "ItemPower.h"

#define V_BOXSIZE		Vector2D(16.0f, 16.0f)

constexpr auto SpriteDefaultId = "df";
constexpr auto EffectTime = 800;
constexpr auto LifeTime = 4000;

CItemPower::CItemPower()
{
	this->AddSprite(SpriteDefaultId, "sprItemPower");

	//
	CCollider2D* collider = new CCollider2D(this, false, true, VectorZero(), V_BOXSIZE);
	this->colliders.push_back(collider);
	this->SetColliders(this->colliders);
}

void CItemPower::Update(DWORD dt)
{
	DWORD now = GetTickCount64();
	if (this->effected == false && now - this->initTime > LifeTime - EffectTime) {
		this->SetInEffect(true);
	}
	else if (now - this->initTime > LifeTime) {
		this->hp = 0;
	}
}

void CItemPower::Render()
{
	D3DCOLOR color = this->GetRenderColor();
	this->sprites.at(SpriteDefaultId)->Draw(this->position, this->nx, color);
}

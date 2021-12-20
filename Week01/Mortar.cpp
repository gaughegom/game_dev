#include "Mortar.h"
#include "BigDestroyEffect.h"


constexpr auto SpriteDefaultId = "df";

CMortar::CMortar(Vector2D boundingBox)
{
	this->AddSprite(SpriteDefaultId, "sprMortar");

	this->hp = 20;
	this->damage = 0;

	//
	CCollider2D* collider = new CCollider2D(this, false, false, VectorZero(), boundingBox);
	this->colliders.push_back(collider);
	this->SetColliders(this->colliders);
}

void CMortar::Update(DWORD dt)
{
	if (this->IsLive() == false) {
		CGame::GetInstance()->InitiateAndPushToQueue<CBigDestroyEffect>(this->position);
	}
}

void CMortar::Render()
{
	D3DCOLOR color = this->GetRenderColor();
	this->sprites.at(SpriteDefaultId)->Draw(this->position, this->nx, color, DrawLayer01);
}

void CMortar::OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent)
{
}

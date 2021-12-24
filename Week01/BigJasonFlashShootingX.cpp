#include "BigJasonFlashShootingX.h"

constexpr auto SpriteDefaultId = "df";
constexpr auto LifeTime = 200;

CBigJasonFlashShootingX::CBigJasonFlashShootingX()
{
	this->AddSprite(SpriteDefaultId, "sprBJShootingX");

	//
	CCollider2D* collider = new CCollider2D(this, false, true, VectorZero(), Vector2D(1.0f, 1.0f));
	this->colliders.push_back(collider);
	this->SetColliders(this->colliders);
}

void CBigJasonFlashShootingX::Update(DWORD dt)
{
	if (GetTickCount64() - this->initTime > LifeTime) {
		this->hp = 0;
	}
}

void CBigJasonFlashShootingX::Render()
{
	this->sprites.at(SpriteDefaultId)->Draw(this->position, -this->nx, DrawArgbColorDefault());
}

#include "BigDestroyEffect.h"

#define V_BOXSIZE		Vector2D(4.0f, 4.0f)

constexpr auto AnimationDefaultId = "df";
constexpr auto LifeTime = 300;

CBigDestroyEffect::CBigDestroyEffect()
{
	this->AddAnimation(AnimationDefaultId, "aniBigDestroy");

	this->velocity = VectorZero();
	this->nx = 1;

	//
	CCollider2D* collider = new CCollider2D(this, false, true, VectorZero(), V_BOXSIZE);
	this->colliders.push_back(collider);
	this->SetColliders(this->colliders);
}

void CBigDestroyEffect::Update(DWORD dt)
{
	if (GetTickCount64() - this->initTime > LifeTime) {
		this->hp = 0;
	}
}

void CBigDestroyEffect::Render()
{
	this->animations.at(AnimationDefaultId)->Render(this->position, 1, DrawArgbColorDefault());
}

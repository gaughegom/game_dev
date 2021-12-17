#include "SmallDestroyEffect.h"

#define V_BOXSIZE				Vector2D(4.0f, 4.0f)

constexpr auto AnimationDefaultId = "df";
constexpr auto LifeTime = 200;

CSmallDestroyEffect::CSmallDestroyEffect()
{
	// add animation
	this->AddAnimation(AnimationDefaultId, "aniSmallDestroy");
	
	this->velocity = VectorZero();
	this->hp = 1;

	//
	CCollider2D* collider = new CCollider2D(this, false, true, VectorZero(), V_BOXSIZE);
	this->colliders.push_back(collider);
	this->SetColliders(this->colliders);
}

void CSmallDestroyEffect::Update(DWORD dt)
{
	// delete
	if (GetTickCount64() - this->initTime > LifeTime) {
		this->hp = 0;
	}
}

void CSmallDestroyEffect::Render()
{
	// render animation
	this->animations.at(AnimationDefaultId)->Render(this->position, this->nx, DRAW_COLOR_DEFAULT);
}

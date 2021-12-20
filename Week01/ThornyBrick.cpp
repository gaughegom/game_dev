#include "ThornyBrick.h"
#include "BigJason.h"
#include "Player.h"

constexpr auto DelayMakeDamage = 2000;

CThornyBrick::CThornyBrick(Vector2D boundingBox)
{
	this->damage = 5;


	//
	CCollider2D* collider = new CCollider2D(this, false, true, VectorZero(), boundingBox);
	this->colliders.push_back(collider);
	this->SetColliders(this->colliders);
}

void CThornyBrick::Update(DWORD dt)
{
	CCharaterBase* player = (CCharaterBase*)CPlayer::GetInstance()->GetPlayer();

	if (this->colliders.at(0)->GetBoundingBox().Overlap(player->GetColliders().at(0)->GetBoundingBox())
		&& player->IsInThorny() && (GetTickCount64() - player->GetPrevTimeThornyDamage() > DelayMakeDamage)) {
		player->TakeDamage(this->damage);
		player->ResetPrevTimeThoryDamage();
	}
}

void CThornyBrick::Render()
{
}

void CThornyBrick::OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent)
{
}

void CThornyBrick::OnTrigger(CCollider2D* self, LPCOLLISIONEVENT coEvent)
{
}

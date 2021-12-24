#include "BossTrigger.h"
#include "Player.h"

constexpr auto DurationTimeForTrigger = 3000;

CBossTrigger::CBossTrigger()
{
	// No sprite
	this->hp = 10;
	this->damage = 0;

	//
	CCollider2D* collider = new CCollider2D(this, false, true, VectorZero(), Vector2D(220.0f, 280.0f));
	this->colliders.push_back(collider);
	this->SetColliders(this->colliders);
}

void CBossTrigger::Update(DWORD dt)
{
	LPGAMEOBJECT player = CPlayer::GetInstance()->GetPlayer();

	if (player->GetColliders().at(0)->GetBoundingBox().Overlap(this->colliders.at(0)->GetBoundingBox())) {
		auto now = GetTickCount64();
		if (this->triggering == false) {
			this->startTrigger = now;
			this->triggering = true;
		}
		else {
			if (now - this->startTrigger > DurationTimeForTrigger) {
				CGame::GetInstance()->SwitchScene(CGame::GetInstance()->GetCurrentSceneId() + 1);
			}
		}
	}
	else {
		this->triggering = false;
	}
}

void CBossTrigger::Render()
{
}

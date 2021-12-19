#include "EnemyBase.h"
#include "BigDestroyEffect.h"
#include "ItemHealth.h"

CEnemyBase::CEnemyBase()
{
}

void CEnemyBase::Update(DWORD dt)
{
}

void CEnemyBase::Render()
{
}

void CEnemyBase::OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent)
{
}

void CEnemyBase::OnTrigger(CCollider2D* self, LPCOLLISIONEVENT coEvent)
{
}

bool CEnemyBase::HandleLifeCycle()
{
	if (!this->IsLive()) {
		CGame::GetInstance()->InitiateAndPushToQueue<CBigDestroyEffect>(this->position);

		// TODO: drop item rate
		CGame::GetInstance()->InitiateAndPushToQueue<CItemHealth>(this->position);
		return false;
	}
	else {
		return true;
	}
}

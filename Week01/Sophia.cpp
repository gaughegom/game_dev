#include "Sophia.h"
#include "Camera.h"
#include "EnemyStuka.h"
#include "EnemyInterrupt.h"
#include "EnemyNeoWorm.h"
#include "Gate.h"
#include "ItemHealth.h"
#include "Jason.h"
#include "SophiaBullet.h"
#include "BigDestroyEffect.h"
#include "ThornyBrick.h"
#include "ItemPower.h"

CSophia::CSophia()
{
	this->directState = SophiaDirectState::Stay;
	this->actionState = SophiaActionState::Idle;

	this->hp = 80;
	this->damage = 0;

	InitParts();
	auto collider = new CCollider2D(this, true, false, SOPHIA_OFFSET_IDLE, SOPHIA_BOX_IDLE);
	this->colliders.push_back(collider);
	this->SetColliders(colliders);
}

void CSophia::InitParts()
{
	this->leftWheel = new CSophiaWheel(this);
	this->rightWheel = new CSophiaWheel(this);
	this->body = new CSophiaBody(this);
	this->cabin = new CSophiaCabin(this);
	this->gun = new CSophiaGun(this);
	this->leftWheel->AddAnimation(AnimationWheelId, "aniSLeftWheel");
	this->rightWheel->AddAnimation(AnimationWheelId, "aniSRightWheel");
}

void CSophia::Shooting()
{
	int direct;
	if (this->actionState == SophiaActionState::Idle) {
		direct = this->nx;
	}
	else {
		direct = 0;
	}

	LPGAMEOBJECT bullet = new CSophiaBullet(direct);
	Vector2D bulletPosition = Vector2D(this->position.x, this->position.y + this->cabin->GetPosition().y);
	bullet->SetPosition(bulletPosition);
	CGame::GetInstance()->PushToQueueObject(bullet);
	this->bullets++;
	this->prevBulletTime = GetTickCount64();
}

void CSophia::Update(DWORD dt)
{
	if (this->IsLive() == false) {
		CGame::GetInstance()->InitiateAndPushToQueue<CBigDestroyEffect>(this->position);
		return;
	}

	// TODO: Debug only
	if (this->prevHp != this->hp) {
		DebugOut(L"sophia hp: %f\n", this->hp);
		this->prevHp = this->hp;
	}

	if (this->colliders.at(0)->IsDynamic() == true) {
		InGravityAffect(this, dt);
		this->UpdateColliders();
	}

	if (CPlayer::GetInstance()->GetSelectId() == PlayerCharacterId::SOPHIA) {
		ListenKeyEvent();
	}
}

void CSophia::ListenKeyEvent()
{
	#pragma region LISTEN KEYBOARD

	auto input = CInputHandler::GetInstance();
	// observe direct state
	if (input->IsKeyDown(DIK_RIGHT)) {
		this->directState = SophiaDirectState::RightMove;
	}
	else if (input->IsKeyDown(DIK_LEFT)) {
		this->directState = SophiaDirectState::LeftMove;
	}
	else {
		this->directState = SophiaDirectState::Stay;
	}

	this->SubcribeDirectState(this->directState);

	// observe self action
	if (input->IsKeyDown(DIK_UP)) {
		DWORD now = GetTickCount64();
		this->stateTime = now;
		if (this->actionState == SophiaActionState::Idle) {
			this->actionState = SophiaActionState::Tile45;
		}
		else if (now - this->prevStateTime > 200 && this->actionState == SophiaActionState::Tile45) {
			this->actionState = SophiaActionState::Up90;
		}
	}
	else {
		DWORD now = GetTickCount64();
		this->prevStateTime = now;
		if (this->actionState == SophiaActionState::Up90) {
			this->actionState = SophiaActionState::Tile45;
		}
		else if (now - this->stateTime > 100 && this->actionState == SophiaActionState::Tile45) {
			this->actionState = SophiaActionState::Idle;
		}
	}

	// listen key W for jumping
	if (input->OnKeyDown(JUMP_KEYCODE) && this->velocity.y < 0 && this->ground == true) {
		this->ground = false;
		this->velocity.y = PlayerJumpForce;
	}

	// listen key switch playerControll
	if (input->OnKeyDown(SWITCH_CONTROLLER_KEYCODE)) {
		auto playerControll = CPlayer::GetInstance();
		this->actionState = SophiaActionState::OpenOut;
		playerControll->SelectPlayer(playerControll->GetJason());
	}

	// listen key shooting
	if (input->IsKeyDown(SHOTTING_KEYCODE)) {
		if (GetTickCount64() - this->prevBulletTime >= this->delayBullet && this->bullets < SophiaMaxBullets) {
			this->Shooting();
		}
	}

	#pragma endregion
}

void CSophia::UpdateColliders()
{
	switch (this->actionState)
	{
	case SophiaActionState::Idle:
		this->colliders.at(0)->SetOffset(SOPHIA_OFFSET_IDLE);
		this->colliders.at(0)->SetBoxSize(SOPHIA_BOX_IDLE);
		break;
	case SophiaActionState::Tile45:
		this->colliders.at(0)->SetOffset(Vector2D(-0.5f * this->nx, 10.5f));
		this->colliders.at(0)->SetBoxSize(SOPHIA_BOX_TILE45);
		break;
	case SophiaActionState::Up90:
		this->colliders.at(0)->SetOffset(Vector2D(-3.0f * this->nx, 12.0f));
		this->colliders.at(0)->SetBoxSize(SOPHIA_BOX_UP90);
		break;
	default:
		this->colliders.at(0)->SetOffset(SOPHIA_OFFSET_IDLE);
		this->colliders.at(0)->SetBoxSize(SOPHIA_BOX_IDLE);
		break;
	}
}

void CSophia::Render()
{
	this->renderColor = this->GetRenderColor();
	this->leftWheel->Render();
	this->rightWheel->Render();
	this->body->Render();
	this->cabin->Render();
	this->gun->Render();
}

void CSophia::SubcribeDirectState(SophiaDirectState directState)
{
	switch (directState)
	{
	case SophiaDirectState::Stay:
		this->velocity.x = 0;
		break;

	case SophiaDirectState::LeftMove:
		this->velocity.x = -PlayerMovingSpeed;
		this->nx = -1;

		break;
	case SophiaDirectState::RightMove:
		this->velocity.x = PlayerMovingSpeed;
		this->nx = 1;

		break;
	}
	
}

void CSophia::SetActionState(SophiaActionState actionState)
{
	this->actionState = actionState;
}

void CSophia::OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent)
{
	LPGAMEOBJECT other = coEvent->object;
	if (dynamic_cast<CBrick*>(other)) {
		if (!this->ground && coEvent->ny == 1) {
			this->ground = true;
		}
	}
	else if (dynamic_cast<CGate*>(other)) {
		CGate* gate = (CGate*)other;
		CGame::GetInstance()->SwitchScene(gate->GetNextScene());
	}
	else if (dynamic_cast<CItemBase*>(other)) {
		this->OnCollisionWithItem((CItemBase*)(other));
	}
	else if (dynamic_cast<CEnemyBase*>(other)) {
		this->OnCollisionWithEnemy(other);
	}
}

void CSophia::OnTrigger(CCollider2D* self, LPCOLLISIONEVENT coEvent)
{
}

void CSophia::OnCollisionWithEnemy(LPGAMEOBJECT const& other)
{
	other->TakeDamage(this->damage);
	this->TakeDamage(other->GetDamage());

	STriggerTag tag = STriggerTag(other);
	other->AddTriggerTag(this);
	this->AddTriggerTag(other);
}

void CSophia::OnCollisionWithItem(CItemBase* const& other)
{
	if (dynamic_cast<CItemHealth*>(other)) {
		CItemHealth* item = (CItemHealth*)other;
		this->hp += item->GetRecoverHealth();
		if (this->hp > 80 + ((this->level - 1) * 50)) {
			this->hp = 80;
		}
	}
	else if (dynamic_cast<CItemPower*>(other)) {
		CItemPower* item = (CItemPower*)other;
		this->SetBonusDamage(item->GetBonusDamage());
	}

	other->OnUse();
}

void CSophia::DecreaseBullet()
{
	this->bullets--;
}

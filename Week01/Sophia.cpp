#include "Sophia.h"
#include "Camera.h"
#include "Jason.h"
#include "ControllerObject.h"
#include "SophiaBasicBullet.h"

CSophia::CSophia()
{
	this->directState = SophiaDirectState::Stay;
	this->actionState = SophiaActionState::Idle;

	this->leftWheel = new CSophiaWheel(this);
	this->rightWheel = new CSophiaWheel(this);
	this->body = new CSophiaBody(this);
	this->cabin = new CSophiaCabin(this);
	this->gun = new CSophiaGun(this);
	this->leftWheel->AddAnimation(C_A_DEFAULT_KEY, 0); // 0: left wheel
	this->rightWheel->AddAnimation(C_A_DEFAULT_KEY, 1); // 1: right wheel

	//
	auto collider = new CCollider2D;
	collider->SetGameObject(this);
	collider->SetOffset(SOPHIA_OFFSET_IDLE);
	collider->SetBoxSize(SOPHIA_BOX_IDLE);
	collider->SetDynamic(true);
	this->colliders.push_back(collider);
	this->SetColliders(colliders);
}

void CSophia::Update(DWORD dt)
{
	if (this->colliders.at(0)->IsDynamic() == true) {
		InGravityAffect(this, dt);
		this->UpdateColliders();
	}

	if (CControllerObject::GetInstance()->GetSelectId() == ControllerObjectID::SOPHIA) {
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
	if (input->OnKeyDown(DIK_X) && this->ground) {
		this->ground = false;
		this->velocity.y = PLAYER_JUMP_FORCE;
	}

	// listten key switch controller
	if (input->OnKeyDown(SWITCH_CONTROLLER_KEYCODE)) {
		CControllerObject::GetInstance()->Select(ControllerObjectID::JASON);
	}

	// listen key shooting
	if (input->IsKeyDown(DIK_S)) {
		if (GetTickCount64() - this->prevBulletTime >= this->delayBullet && this->bullets < SOPHIA_MAX_BULLETS) {
			int direct;
			if (this->actionState == SophiaActionState::Idle) {
				direct = this->nx;
			}
			else {
				direct = 0;
			}
			LPGAMEOBJECT bullet = new CSophiaBasicBullet(direct);
			bullet->SetPosition(this->position + this->gun->GetPosition());
			CGame::GetInstance()->NewGameObject(bullet);
			this->bullets++;
			this->prevBulletTime = GetTickCount64();
		}
	}

	#pragma endregion
}

void CSophia::UpdateColliders()
{
	auto collider = this->colliders.at(0);
	this->colliders.clear();
	switch (this->actionState)
	{
	case SophiaActionState::Idle:
		collider->SetOffset(SOPHIA_OFFSET_IDLE);
		collider->SetBoxSize(SOPHIA_BOX_IDLE);
		break;
	case SophiaActionState::Tile45:
		collider->SetOffset(Vector2D(-0.5f * this->nx, 10.5f));
		collider->SetBoxSize(SOPHIA_BOX_TILE45);
		break;
	case SophiaActionState::Up90:
		collider->SetOffset(Vector2D(-3.0f * this->nx, 12.0f));
		collider->SetBoxSize(SOPHIA_BOX_UP90);
		break;
	default:
		collider->SetOffset(SOPHIA_OFFSET_IDLE);
		collider->SetBoxSize(SOPHIA_BOX_IDLE);
		break;
	}

	collider->SetDynamic(true);
	this->colliders.push_back(collider);
	this->SetColliders(colliders);
}

void CSophia::Render()
{
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
		this->velocity.x = -PLAYER_MOVING_SPEED;
		this->nx = -1;

		break;
	case SophiaDirectState::RightMove:
		this->velocity.x = PLAYER_MOVING_SPEED;
		this->nx = 1;

		break;
	}
	
}

void CSophia::SubcribeActionState(SophiaActionState actionState)
{
}

void CSophia::OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent)
{
	if (dynamic_cast<CBrick*>(coEvent->object)) {

		if (!this->ground && coEvent->ny == 1) {
			this->ground = true;
		}
	}
}

void CSophia::OnTrigger(CCollider2D* self, LPCOLLISIONEVENT coEvent)
{
}

void CSophia::DecreaseBullet()
{
	this->bullets--;
}

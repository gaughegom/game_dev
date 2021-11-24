#include "Sophia.h"

CSophia::CSophia()
{
	this->SetSize(17, 10);
	this->SetPosition(PLAYER_START_X, PLAYER_START_Y);
	this->directState = new CSophiaDirectState(this);
	this->actionState = new CSophiaActionState(this);

	this->AddAnimation(LEFT_WHEEL, ANIMATION_SOPHIA_LEFT_WHEEL);
	this->AddAnimation(RIGHT_WHEEL, ANIMATION_SOPHIA_RIGHT_WHEEL);
	auto sprites = CSprites::GetInstance();
	this->lpsBody = sprites->Get(SPRITE_SOPHIA_BODY);

	this->directState->Stay();
	this->actionState->IdleState();
}

void CSophia::Update(DWORD dt)
{
	LinearMoveInGravity(this, dt);

	int backbufferWidth = CGame::GetInstance()->GetBackbufferWidth();
	this->EdgeCollisionHandler(CGame::GetInstance()->GetBackbufferWidth());

	if (this->IsSelected()) {
		this->ListenKeyEvent();
	}
}

void CSophia::ListenKeyEvent()
{
	#pragma region LISTEN KEYBOARD

	auto input = CInputHandler::GetInstance();
	// observe direct state
	if (input->IsKeyDown(DIK_RIGHT)) {
		this->directState->SetState(SOPHIA_STATE_DIRECTION_FORWARD);
	}
	else if (input->IsKeyDown(DIK_LEFT)) {
		this->directState->SetState(SOPHIA_STATE_DIRECTION_BACKWARD);
	}
	else {
		this->directState->SetState(SOPHIA_STATE_DIRECTION_STAY);
	}

	this->SubcribeDirectState(this->directState->GetState());

	// observe sophia action
	if (input->IsKeyDown(DIK_UP)) {
		DWORD now = GetTickCount();
		this->stateTime = now;
		int state = this->actionState->GetState();
		if (state == SOPHIA_STATE_ACTION_IDLE) {
			this->actionState->SetState(SOPHIA_STATE_ACTION_TILE_45);
		}
		else if (now - this->prevStateTime > 200 && state == SOPHIA_STATE_ACTION_TILE_45) {
			this->actionState->SetState(SOPHIA_STATE_ACTION_UP_90);
		}
	}
	else {
		DWORD now = GetTickCount();
		this->prevStateTime = now;
		int state = this->actionState->GetState();
		if (state == SOPHIA_STATE_ACTION_UP_90) {
			this->actionState->SetState(SOPHIA_STATE_ACTION_TILE_45);
		}
		else if (now - this->stateTime > 100 && state == SOPHIA_STATE_ACTION_TILE_45) {
			this->actionState->SetState(SOPHIA_STATE_ACTION_IDLE);
		}
	}

	if (input->OnKeyDown(DIK_X)) {
		if (this->velocity.y <= 0) {
			this->velocity.y = PLAYER_JUMP_FORCE;
		}
	}

	#pragma endregion
}

void CSophia::EdgeCollisionHandler(int width)
{
	switch (this->directState->GetState())
	{
	case SOPHIA_STATE_DIRECTION_FORWARD:
		if (this->position.x > width * 10 - PLAYER_WIDTH) {
			this->SetX(width * 10 - PLAYER_WIDTH);
		}
	case SOPHIA_STATE_DIRECTION_BACKWARD:
		if (this->position.x <= 0) {
			this->SetX(0);
		}
	default:
		break;
	}
	if (this->position.y <= 20) {
		this->position.y = 20;
	}
}

void CSophia::Render()
{
	animations.at(LEFT_WHEEL)->Render(this->position + this->leftWheel, 1);
	animations.at(RIGHT_WHEEL)->Render(this->position + this->rightWheel, 1);
	this->lpsBody->Draw(this->position + this->body, this->nx);
	this->lpsCabin->Draw(this->position + this->cabin, this->nx);
	this->lpsGun->Draw(this->position + this->gun, this->nx);
}

void CSophia::SubcribeDirectState(int directState)
{
	this->directState->SetState(directState);
	switch (directState)
	{
	case SOPHIA_STATE_DIRECTION_STAY:
		this->velocity.x = 0;
		this->directState->Stay();
		this->SubcribeActionState(this->actionState->GetState());
		break;
	case SOPHIA_STATE_DIRECTION_BACKWARD:
		this->velocity.x = -PLAYER_MOVING_SPEED;
		this->nx = -1;
		this->directState->MoveBackward();
		this->SubcribeActionState(this->actionState->GetState());
		break;
	case SOPHIA_STATE_DIRECTION_FORWARD:
		this->velocity.x = PLAYER_MOVING_SPEED;
		this->nx = 1;
		this->directState->MoveForward();
		this->SubcribeActionState(this->actionState->GetState());
		break;
	default:
		this->velocity.x = 0;
		this->directState->Stay();
		this->SubcribeActionState(this->actionState->GetState());
		break;
	}
}

void CSophia::SubcribeActionState(int actionState)
{
	switch (actionState)
	{
	case SOPHIA_STATE_ACTION_IDLE:
		this->actionState->IdleState();
		break;
	case SOPHIA_STATE_ACTION_TILE_45:
		this->actionState->Tilt45State();
		break;
	case SOPHIA_STATE_ACTION_UP_90:
		this->actionState->Up90State();
		break;
	default:
		this->actionState->IdleState();
		break;
	}
}
#include "Sophia.h"

CSophia::CSophia()
{
	this->SetSize(20, 20);
	this->SetPosition(PLAYER_START_X, PLAYER_START_Y);
	this->directState = SophiaDirectState::Stay;
	this->actionState = SophiaActionState::Idle;

	this->leftWheel = new CSophiaWheel(this);
	this->rightWheel = new CSophiaWheel(this);
	this->body = new CSophiaBody(this);
	this->cabin = new CSophiaCabin(this);
	this->gun = new CSophiaGun(this);
	this->leftWheel->AddAnimation(C_A_DEFAULT_KEY, 0); // 0: left wheel
	this->rightWheel->AddAnimation(C_A_DEFAULT_KEY, 1); // 1: right wheel
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
		this->directState = SophiaDirectState::RightMove;
	}
	else if (input->IsKeyDown(DIK_LEFT)) {
		this->directState = SophiaDirectState::LeftMove;
	}
	else {
		this->directState = SophiaDirectState::Stay;
	}

	this->SubcribeDirectState(this->directState);

	// observe sophia action
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

	if (input->OnKeyDown(DIK_X)) {
		if (this->velocity.y <= 0) {
			this->velocity.y = PLAYER_JUMP_FORCE;
		}
	}

	#pragma endregion
}

void CSophia::EdgeCollisionHandler(int width)
{
	switch (this->directState)
	{
	case SophiaDirectState::RightMove:
		if (this->position.x > width * 10 - PLAYER_WIDTH) {
			this->SetX(width * 10 - PLAYER_WIDTH);
		}
	case SophiaDirectState::LeftMove:
		if (this->position.x <= 0) {
			this->SetX(0);
		}
	default:
		break;
	}
	if (this->position.y <= GAME_GROUND) {
		this->position.y = GAME_GROUND;
	}
}

void CSophia::Render()
{
	this->leftWheel->Render();
	this->rightWheel->Render();
	this->body->Render();
	this->cabin->Render();
	this->gun->Render();

	auto debugPosSprite = CSprites::GetInstance()->Get(2000);
	Vector2D debugPos = Vector2D(this->position.x - 8, this->position.y);
	debugPosSprite->Draw(debugPos, this->nx);
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
	default:
		this->velocity.x = 0;
		break;
	}
	
}

void CSophia::SubcribeActionState(SophiaActionState actionState)
{
	/*switch (actionState)
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
	}*/
}
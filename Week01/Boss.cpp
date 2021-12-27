#include "Boss.h"
#include "Brick.h"
#include "Player.h"

constexpr auto MaxCloneBosses = 15;
constexpr auto MaxShootingTimes = 3;
constexpr auto DelayShootingTime = 300;

constexpr auto AnimationOpenEyeId = "openEye";
constexpr auto AnimationIdleId = "idle";
constexpr auto AnimationMoveId = "move";

int CBoss::__cloneCount = -1;
std::unordered_map<int, CBoss*> CBoss::__cloneBosses = {};

CBoss::CBoss()
{
	// add sprites
	this->AddAnimation(AnimationOpenEyeId, "aniBossEye");
	this->AddAnimation(AnimationIdleId, "aniBossIdle");
	this->AddAnimation(AnimationMoveId, "aniBossMove");

	this->hp = 50;
	this->damage = 10;

	// collider
	CCollider2D* collider = new CCollider2D(this, true, false, VectorZero(), Vector2D(34.0f, 34.0f));
	this->colliders.push_back(collider);
	this->SetColliders(this->colliders);

	this->SetState(EBossState::PREPARE_AWAKING);
	this->__cloneCount++;
	this->__cloneBosses.insert(std::make_pair(this->__cloneCount, this));
	DebugOut(L"create new boss clone %d\n", this->__cloneCount);
}

void CBoss::SetState(EBossState nextState)
{
	this->state = nextState;
	switch (this->state)
	{
	case EBossState::PREPARE_AWAKING:
		this->OnPrepareAwaking();
		break;
	case EBossState::AWAKING:
		this->OnAwaking();
		break;
	case EBossState::MOVING:
		this->OnMoving();
		break;
	case EBossState::SHOOTING:
		this->OnShooting();
		break;
	case EBossState::MOVING_AND_SHOOTING:
		this->OnMovingAndShooting();
		break;
	case EBossState::PREPARE_SPLEEPING:
		this->OnPrepareSleeping();
		break;
	case EBossState::SLEEPING:
		this->OnSleeping();
		break;
	default:
		break;
	}

	DebugOut(L"state: %d\n", this->state);
}

void CBoss::OnPrepareAwaking()
{
	this->keyDisplay = AnimationOpenEyeId;
	
	this->sleeping = false;
	

	this->animations.at(this->keyDisplay)->SetFinish(false);
	this->animations.at(this->keyDisplay)->SetLoop(false);
}

void CBoss::OnAwaking()
{
	this->keyDisplay = AnimationIdleId;
	this->DirectiveAwaking();
}

void CBoss::OnMoving()
{
	DebugOut(L"call moving method\n");

	this->keyDisplay = AnimationMoveId;

	this->stepMove = Random(30, 80);
	int direction = Random(1, 4);
	switch (direction)
	{
	case 1:
		this->velocity.x = 0.05f;
		break;
	case 2:
		this->velocity.x = -0.05f;
		break;
	case 3:
		this->velocity.y = 0.05f;
		break;
	case 4:
		this->velocity.y = -0.05f;
		break;
	default:
		break;
	}

}

void CBoss::OnShooting()
{
	DebugOut(L"call shooting method\n");

	if (this->shootingTimes < MaxShootingTimes) {
		DWORD now = GetTickCount64();

		if (now - this->prevShootingTime > DelayShootingTime) {
			DebugOut(L"Boss shooting\n");
			this->shootingTimes++;
			this->prevShootingTime = now;
		}
	}
	else {
		this->SetState(EBossState::PREPARE_SPLEEPING);
	}
}

void CBoss::OnMovingAndShooting()
{
	DebugOut(L"call movingAndShooting method\n");
	this->OnMoving();

}

void CBoss::OnPrepareSleeping()
{
	DebugOut(L"call prepareSleeping method\n");
	this->keyDisplay = AnimationOpenEyeId;
	this->animations.at(this->keyDisplay)->SetReverse(true);
	this->animations.at(this->keyDisplay)->SetFinish(false);
}

void CBoss::OnSleeping()
{
	DebugOut(L"call sleeping\n");

	this->keyDisplay = AnimationIdleId;

	this->sleeping = true;
	this->velocity = VectorZero();
	this->stepMove = 0;
	this->shootingTimes = 0;

	this->CallNextClone();
}

void CBoss::DirectiveAwaking()
{
	int randomInt = Random(1, 20);

	if (randomInt <= 3) {
		this->SetState(EBossState::SHOOTING);
	}
	else if (randomInt <= 6) {
		this->SetState(EBossState::MOVING_AND_SHOOTING);
	}
	else {
		this->SetState(EBossState::MOVING);
	}
}

void CBoss::CallNextClone() {
	DebugOut(L"call callNextClone method\n");

	if (this->__cloneCount < MaxCloneBosses) {
		// awake or create other clone
		if (this->__cloneBosses.size() > 1) {
			int rate = Random(1, 10);

			int rateInit = 6;
			if (this->__cloneBosses.size() >= 10) {
				rateInit = 0;
			}
			if (rate > rateInit) {
				this->CallSleepingClone();
			}
			else {
				this->InitiateNewClone();
			}
		}
		else {
			this->InitiateNewClone();
		}
	}
	else {
		this->CallSleepingClone();
	}
}

void CBoss::CallSleepingClone() {
	DebugOut(L"call callSleepingClone method\n");

	int randomIndex = Random(0, this->__cloneBosses.size() - 1);
	while (this->__cloneBosses.at(randomIndex) == this) {
		randomIndex = Random(0, this->__cloneBosses.size() - 1);
	}

	this->__cloneBosses.at(randomIndex)->SetState(EBossState::PREPARE_AWAKING);
}

void CBoss::InitiateNewClone() {
	DebugOut(L"call initiateNewClone method\n");

label_again:
	int randXAxis = Random(1, 6) * 32;
	int randYAxis = Random(1, 6) * 32;
	Vector2D randPosition = Vector2D(randXAxis, randYAxis);

	for (const auto& mapClone : this->__cloneBosses) {
		CBoss* clone = mapClone.second;

		float distancePlayer = PositionsDistance(randPosition, CPlayer::GetInstance()->GetPlayer()->GetPosition());
		if (randPosition == clone->GetPosition() || distancePlayer < 32) {
			goto label_again;
		}
	}

	CGame::GetInstance()->InitiateAndPushToQueue<CBoss>(randPosition);
	DebugOut(L"new clone done\n");
}

void CBoss::Update(DWORD dt)
{
	if (this->sleeping)
		return;

	if (this->animations.at(AnimationOpenEyeId)->IsFinish()) {
		switch (this->state)
		{
		case EBossState::PREPARE_AWAKING:
			this->SetState(EBossState::AWAKING);
			break;

		case EBossState::MOVING:
		case EBossState::MOVING_AND_SHOOTING:
			{
				if (this->stepMove > 0) {
					this->stepMove--;
				}
				else {
					this->SetState(EBossState::PREPARE_SPLEEPING);
				}
			}
			break;

		case EBossState::PREPARE_SPLEEPING:
			this->SetState(EBossState::SLEEPING);
			break;

		default:
			break;
		}
	}

	if (this->state == EBossState::SHOOTING || this->state == EBossState::MOVING_AND_SHOOTING) {
		this->OnShooting();
	}
}

void CBoss::Render()
{
	D3DCOLOR color = this->GetRenderColor();
	this->animations.at(this->keyDisplay)->Render(this->position, this->nx, color);
}

void CBoss::OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent)
{
	LPGAMEOBJECT other = coEvent->object;
	if (dynamic_cast<CBrick*>(other) || dynamic_cast<CBoss*>(other)) {
		if (this->state == EBossState::MOVING
			|| this->state == EBossState::SHOOTING
			|| this->state == EBossState::MOVING_AND_SHOOTING) {
			this->SetState(EBossState::PREPARE_SPLEEPING);
			this->velocity = VectorZero();
			this->stepMove = 0;
		}
	}
}

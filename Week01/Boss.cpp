#include "Boss.h"
#include "Brick.h"
#include "Player.h"
#include "BossMarbleBullet.h"
#include "BigDestroyEffect.h"

constexpr auto MaxCloneBosses = 15;
constexpr auto MaxShootingTimes = 3;
constexpr auto DelayShootingTime = 300;

constexpr auto OwnBulletSpeed = 0.1;

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
	CCollider2D* collider = new CCollider2D(this, true, false, VectorZero(), Vector2D(32.0f, 32.0f));
	this->colliders.push_back(collider);
	this->SetColliders(this->colliders);

	this->SetState(EBossState::PREPARE_AWAKING);
	this->__cloneCount++;
	this->index = this->__cloneCount;
	this->__cloneBosses.insert(std::make_pair(this->index, this));
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
		this->CalcBulletDirection(); // lock player position
		break;
	case EBossState::MOVING_AND_SHOOTING:
		this->OnMoving();
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
}

void CBoss::OnPrepareAwaking()
{
	this->keyDisplay = AnimationOpenEyeId;
	
	this->sleeping = false;
	

	this->animations.at(this->keyDisplay)->SetFinish(false);
	this->animations.at(this->keyDisplay)->SetReverse(false);
	this->animations.at(this->keyDisplay)->SetLoop(false);
}

void CBoss::OnAwaking()
{
	this->keyDisplay = AnimationIdleId;
	this->DirectiveAwaking();
}

void CBoss::OnMoving()
{

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
	if (this->shootingTimes < MaxShootingTimes) {
		DWORD now = GetTickCount64();

		if (now - this->prevShootingTime > DelayShootingTime) {
			this->shootingTimes++;
			this->prevShootingTime = now;

			CGame* game = CGame::GetInstance();
			CBossMarbleBullet* bullet1 = game->InitiateAndPushToQueue<CBossMarbleBullet>(this->position);
			CBossMarbleBullet* bullet2 = game->InitiateAndPushToQueue<CBossMarbleBullet>(this->position);
			CBossMarbleBullet* bullet3 = game->InitiateAndPushToQueue<CBossMarbleBullet>(this->position);

			bullet1->SetVelocity(RotateVector(this->shootingDirect) * OwnBulletSpeed);
			bullet2->SetVelocity(RotateVector(this->shootingDirect, 45) * OwnBulletSpeed);
			bullet3->SetVelocity(RotateVector(this->shootingDirect, -45) * OwnBulletSpeed);
		}
	}
	else {
		this->SetState(EBossState::PREPARE_SPLEEPING);
	}
}

void CBoss::OnMovingAndShooting()
{
	Vector2D bulletVelocity = NormalizeVector(CPlayer::GetInstance()->GetPlayer()->GetPosition() - this->position) * OwnBulletSpeed;
	CBossMarbleBullet* bullet = CGame::GetInstance()->InitiateAndPushToQueue<CBossMarbleBullet>(this->position);
	bullet->SetVelocity(bulletVelocity);
}

void CBoss::OnPrepareSleeping()
{
	this->keyDisplay = AnimationOpenEyeId;
	this->animations.at(this->keyDisplay)->SetReverse(true);
	this->animations.at(this->keyDisplay)->SetFinish(false);
}

void CBoss::OnSleeping()
{
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

	if (randomInt <= 4) {
		this->SetState(EBossState::SHOOTING);
	}
	else if (randomInt <= 7) {
		this->SetState(EBossState::MOVING_AND_SHOOTING);
	}
	else {
		this->SetState(EBossState::MOVING);
	}
}

void CBoss::CallNextClone() {
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

	if (this->__cloneBosses.size() == 0) {
		return;
	}

	int chooseIndex = -1;

	int randomIndex = Random(0, this->__cloneBosses.size() - 1);
	do {
		int randomIndex = Random(0, this->__cloneBosses.size() - 1);
		int i = 0;
		for (auto map_clone : this->__cloneBosses)
		{
			if (this->__cloneBosses.size() > 1 && map_clone.second == this) continue;
			if (i == randomIndex)
			{
				chooseIndex = map_clone.first;
				break;
			}

			i++;
		} 
	} while (chooseIndex == -1);

	this->__cloneBosses.at(chooseIndex)->SetState(EBossState::PREPARE_AWAKING);
}

void CBoss::InitiateNewClone() {

label_again:
	int randXAxis = Random(1, 6) * 32 + 16;
	int randYAxis = Random(1, 6) * 32;
	Vector2D randPosition = Vector2D(randXAxis, randYAxis);

	for (const auto& mapClone : this->__cloneBosses) {
		CBoss* clone = mapClone.second;

		SRect randomRect = SRect(randXAxis - 16, randYAxis + 16, randXAxis + 16, randYAxis - 16);

		float distancePlayer = PositionsDistance(randPosition, CPlayer::GetInstance()->GetPlayer()->GetPosition());
		if (randPosition == clone->GetPosition() 
			|| distancePlayer < 32
			|| randomRect.Overlap(clone->GetColliders().at(0)->GetBoundingBox())) {
			goto label_again;
		}
	}

	CGame::GetInstance()->InitiateAndPushToQueue<CBoss>(randPosition);
}

void CBoss::CalcBulletDirection() {
	this->shootingTimes = 0;
	this->prevShootingTime = GetTickCount64();

	Vector2D playerPosition = CPlayer::GetInstance()->GetPlayer()->GetPosition();

	if (abs(this->position.y - playerPosition.y) < 90.0f) {
		this->shootingAngle = 90;

		if (this->position.x < playerPosition.x) {
			this->shootingDirect = Vector2D(1.0f, 0.0f);
		}
		else {
			this->shootingDirect = Vector2D(-1.0f, 0.0f);
		}
	}
	else {
		this->shootingAngle = 0;

		if (this->position.y < playerPosition.y) {
			this->shootingDirect = Vector2D(0.0f, 1.0f);
		}
		else {
			this->shootingDirect = Vector2D(0.0f, -1.0f);
		}
	}
}

void CBoss::Update(DWORD dt)
{
	if (this->IsLive() == false) {
		CGame::GetInstance()->InitiateAndPushToQueue<CBigDestroyEffect>(this->position);
		this->__cloneBosses.erase(this->index);

		if (this->sleeping == false) {
			this->CallNextClone();
		}

		return;
	}
	
	
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

	if (this->state == EBossState::SHOOTING) {
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
	else if (dynamic_cast<CBossMarbleBullet*>(other)) {
		STriggerTag tag = STriggerTag(other);
		other->AddTriggerTag(this);
		this->AddTriggerTag(other);
	}
}

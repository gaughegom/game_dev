#include "EnemyBallcarry.h"
#include "Player.h"
#include "EnemyBallbomb.h"
#include "BigDestroyEffect.h"

#define V_BOXSIZE					Vector2D(18.0f, 18.0f)

constexpr auto SpriteStayId = "stay";
constexpr auto SpriteAttackId = "attack";
constexpr auto AnimationMoveId = "move";
constexpr auto DetectedPlayerRadius = 80.0f;
constexpr auto MaxBombCarry = 7;
constexpr auto MaxStepMove = 10;

CEnemyBallcarry::CEnemyBallcarry()
{
	// sprite, animation
	this->AddAnimation(AnimationMoveId, "aniEBallcarry");
	this->AddSprite(SpriteStayId, "sprEBallcarry00");
	this->AddSprite(SpriteAttackId, "sprEBallcarry02");

	this->hp = 30;
	this->damage = 10;

	// collider
	CCollider2D* collider = new CCollider2D(this, true, false, VectorZero(), V_BOXSIZE);
	this->colliders.push_back(collider);
	this->SetColliders(this->colliders);
}

void CEnemyBallcarry::Update(DWORD dt)
{
	if (!this->IsLive()) {
		CGame::GetInstance()->InitiateAndPushToQueue<CBigDestroyEffect>(this->position);
		return;
	}

	// gravity
	InGravityAffect(this, dt);

	LPGAMEOBJECT player = CPlayer::GetInstance()->GetPlayer();

	// detacted player
	if (!this->activeAttack && PositionsDistance(this->position, player->GetPosition()) < DetectedPlayerRadius) {
		this->activeAttack = true;
		this->timeAttack = GetTickCount64();

		// droping bomb
		for (int i = 0; i < MaxBombCarry; i++) {
			int sign = (rand() % 2 == 0) ? 1 : -1;
			float bombVx = Random(5, 12) * 0.001f * sign;
			float bombVy = Random(12, 15) * 0.01f;
			CGame::GetInstance()->InitiateAndPushToQueue<CEnemyBallbomb>(this->position, Vector2D(bombVx, bombVy));
		}
	}
	else if (this->activeAttack && (GetTickCount64() - this->timeAttack > 300)) {
		// duration attack then move
		this->activeMove = true;

		// move reverse player
		if (player->GetPosition().x < this->position.x) {
			this->nx = 1;
		}
		else {
			this->nx = -1;
		}
	}

	if (this->activeMove) {
		if (this->stepMove > MaxStepMove) {
			this->velocity.x = 0;
		}
		else {
			this->velocity.x = this->nx * 0.12f;
			this->stepMove++;
		}
	}
}

void CEnemyBallcarry::Render()
{
	D3DCOLOR color = this->GetRenderColor();
	if (this->activeMove && this->velocity != VectorZero()) {
		// render move
		this->animations.at(AnimationMoveId)->Render(this->position, this->nx, color);
	}
	else if (this->activeAttack) {
		// render attack sprite
		this->sprites.at(SpriteAttackId)->Draw(this->position, this->nx, color);
	}
	else {
		// render stay sprite
		this->sprites.at(SpriteStayId)->Draw(this->position, this->nx, color);
	}
}

void CEnemyBallcarry::OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent)
{
}

void CEnemyBallcarry::OnTrigger(CCollider2D* self, LPCOLLISIONEVENT coEvent)
{
}

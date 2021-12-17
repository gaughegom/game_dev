#include "EnemyBallcarry.h"
#include "Player.h"
#include "EnemyBallbomb.h"

#define V_BOXSIZE					Vector2D(18.0f, 18.0f)

constexpr auto SpriteStayId = "stay";
constexpr auto SpriteAttackId = "attack";
constexpr auto AnimationMoveId = "move";
constexpr auto DetectedPlayerRadius = 80.0f;
constexpr auto MaxBombCarry = 7;

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
	// gravity
	InGravityAffect(this, dt);

	LPGAMEOBJECT player = CPlayer::GetInstance()->GetPlayer();

	// detacted player
	if (!this->activeAttack && PositionsDistance(this->position, player->GetPosition()) < DetectedPlayerRadius) {
		this->activeAttack = true;
		this->timeAttack = GetTickCount64();

		// droping bomb
		for (int i = 0; i < MaxBombCarry; i++) {
			CEnemyBallbomb* bomb = new CEnemyBallbomb();
			int sign = (rand() % 2 == 0) ? 1 : -1;
			float bombVx = Random(5, 12) * 0.001f * sign;
			bomb->SetVelocity(Vector2D(bombVx, 0));
			bomb->SetPosition(this->position);
			LPGAMEOBJECT bombObj = (LPGAMEOBJECT)bomb;
			CGame::GetInstance()->NewGameObject(bombObj);
		}
	}
	else if (this->activeAttack && (GetTickCount64() - this->timeAttack > 300)) {
		// duration attack then move
		this->activeMove = true;
	}

	if (this->activeMove) {
		this->nx = RandomDirect();
		this->velocity.x = this->nx * PlayerMovingSpeed;
	}
}

void CEnemyBallcarry::Render()
{
	D3DCOLOR color = this->GetRenderColor();
	if (this->activeMove) {
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
	if (dynamic_cast<CSophia*>(coEvent->object)) {
		coEvent->object->TakeDamage(this->damage);
		this->TakeDamage(coEvent->object->GetDamage());

		STriggerTag tag = STriggerTag(coEvent->object);
		coEvent->object->AddTriggerTag(this);
		this->AddTriggerTag(coEvent->object);
	}
}

void CEnemyBallcarry::OnTrigger(CCollider2D* self, LPCOLLISIONEVENT coEvent)
{
}

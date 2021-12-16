#include "EnemyBallcarry.h"
#include "Player.h"
#include "EnemyBallbomb.h"

#define SPRITE_STAY_ID				"stay"
#define SPRITE_ATTACK_ID			"attack"
#define ANIMATION_MOVE_ID			"move"

#define V_BOXSIZE					Vector2D(18.0f, 18.0f)
#define DETACTED_PLAYER_DISTANCE	80.0f
#define MAX_BOMB_CARRY				7

CEnemyBallcarry::CEnemyBallcarry()
{
	// sprite, animation
	this->AddAnimation(ANIMATION_MOVE_ID, "aniEBallcarry");
	this->AddSprite(SPRITE_STAY_ID, "sprEBallcarry00");
	this->AddSprite(SPRITE_ATTACK_ID, "sprEBallcarry02");

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
	if (!this->activeAttack && PositionsDistance(this->position, player->GetPosition()) < DETACTED_PLAYER_DISTANCE) {
		this->activeAttack = true;
		this->timeAttack = GetTickCount64();

		// droping bomb
		for (int i = 0; i < MAX_BOMB_CARRY; i++) {
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
		this->velocity.x = this->nx * PLAYER_MOVING_SPEED;
	}
}

void CEnemyBallcarry::Render()
{
	D3DCOLOR color = this->GetRenderColor();
	if (this->activeMove) {
		// render move
		this->animations.at(ANIMATION_MOVE_ID)->Render(this->position, this->nx, color);
	}
	else if (this->activeAttack) {
		// render attack sprite
		this->sprites.at(SPRITE_ATTACK_ID)->Draw(this->position, this->nx, color);
	}
	else {
		// render stay sprite
		this->sprites.at(SPRITE_STAY_ID)->Draw(this->position, this->nx, color);
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

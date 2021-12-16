#include "EnemyInterrupt.h"
#include "Player.h"
#include "EnemyNeoWorm.h"

#define V_BOXSIZE			Vector2D(22.0f, 18.0f)
#define ANIMATION_ID		"df"
#define SPRITE_ID			"df"

#define MAX_NEOWORM			2
#define DELAY_NEOWORM		700

#define ACTIVE_DISTANCE_X	10

CEnemyInterrupt::CEnemyInterrupt()
{
	this->AddAnimation(ANIMATION_ID, "aniEInterrupt");
	this->AddSprite(SPRITE_ID, "sprEInterrupt00");

	this->hp = 30;
	this->damage = 10;	// TODO: adjust damage later

	//
	this->colliders.clear();
	CCollider2D* collider = new CCollider2D(this, true, false, VectorZero(), V_BOXSIZE);
	this->colliders.push_back(collider);
	this->SetColliders(this->colliders);
}

void CEnemyInterrupt::Update(DWORD dt)
{
	LPGAMEOBJECT player = CPlayer::GetInstance()->GetPlayer();
	if (abs(this->position.x - player->GetPosition().x) <= ACTIVE_DISTANCE_X 
		&& this->position.y > player->GetPosition().y
		&& (GetTickCount64() - this->prevTimeNeoworm) > DELAY_NEOWORM
		&& this->existNeoworm < MAX_NEOWORM) {
		LPGAMEOBJECT neoworm = new CEnemyNeoWorm();
		neoworm->SetNx(RandomDirect());
		neoworm->SetPosition(this->position);
		CGame::GetInstance()->NewGameObject(neoworm);

		this->prevTimeNeoworm = GetTickCount64();
		this->existNeoworm++;
	}
}

void CEnemyInterrupt::Render()
{
	D3DCOLOR color = this->GetRenderColor();
	LPGAMEOBJECT player = CPlayer::GetInstance()->GetPlayer();

	if (abs(this->position.x - player->GetPosition().x) <= ACTIVE_DISTANCE_X && this->position.y > player->GetPosition().y) {
		this->animations.at(ANIMATION_ID)->Render(this->position, this->nx, color);
	}
	else {
		this->sprites.at(SPRITE_ID)->Draw(this->position, this->nx, color);
	}
}

void CEnemyInterrupt::OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent)
{
	if (dynamic_cast<CSophia*>(coEvent->object)) {
		coEvent->object->TakeDamage(this->damage);
		this->TakeDamage(coEvent->object->GetDamage());

		STriggerTag tag = STriggerTag(coEvent->object);
		coEvent->object->AddTriggerTag(this);
		this->AddTriggerTag(coEvent->object);
	}
}

void CEnemyInterrupt::OnTrigger(CCollider2D* self, LPCOLLISIONEVENT coEvent)
{
}

#include "EnemyBallot.h"
#include "SophiaBullet.h"
#include "ControllerObject.h"

#define	V_BALLOT_BOXSIZE			Vector2D(18, 18)
#define ANIMATION_DEFAULT_ID	"default"
#define SPR_IDLE_ID				"idle"

CEnemyBallot::CEnemyBallot()
{
	this->AddAnimation(ANIMATION_DEFAULT_ID, "aniEBallot");		// animation
	this->AddSprite(SPR_IDLE_ID, "sprEBallot00");		// for idle state

	// hp, damage
	this->hp = 20;
	this->damage = 10;

	// collider
	this->colliders.clear();
	auto collider = new CCollider2D;
	collider->SetGameObject(this);
	collider->SetOffset(VectorZero());
	collider->SetBoxSize(V_BALLOT_BOXSIZE);
	collider->SetDynamic(true);
	this->colliders.push_back(collider);
	this->SetColliders(this->colliders);
}

void CEnemyBallot::Update(DWORD dt)
{
}

void CEnemyBallot::Render()
{
	auto player = CControllerObject::GetInstance()->GetPlayer();
	if (abs(this->position.x - player->GetPosition().x) < 60) {
		this->animations.at(ANIMATION_DEFAULT_ID)->Render(this->position, this->nx, DRAW_COLOR_DEFAULT);
	}
	else {
		this->sprites.at(SPR_IDLE_ID)->Draw(this->position, this->nx, DRAW_COLOR_DEFAULT);
	}
}

void CEnemyBallot::OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent)
{
	if (dynamic_cast<CSophia*>(coEvent->object)) {
		LPGAMEOBJECT thisObject = dynamic_cast<LPGAMEOBJECT>(this);
		coEvent->object->TakeDamage(thisObject);
	}
	else if (dynamic_cast<CSophiaBullet*>(coEvent->object)) {
		this->TakeDamage(coEvent->object);
	}
}

void CEnemyBallot::OnTrigger(CCollider2D* self, LPCOLLISIONEVENT coEvent)
{
}

#include "GameObject.h"
#include "Player.h"
#include "SophiaBullet.h"
#include "EnemyStuka.h"
#include "ItemHealth.h"


CGameObject::CGameObject()
{
	this->position.x = this->position.y = 0;
	this->velocity.x = this->velocity.y = 0;
	this->nx = 1;
}

Vector2D CGameObject::GetPosition()
{
	return this->position;
}

void CGameObject::SetX(float x)
{
	this->position.x = x;
}

void CGameObject::SetY(float y)
{
	this->position.y = y;
}

void CGameObject::SetNx(int newNX)
{
	this->nx = newNX;
}

float CGameObject::GetX()
{
	return this->position.x;
}

float CGameObject::GetY()
{
	return this->position.y;
}

int CGameObject::GetNx()
{
	return this->nx;
}

void CGameObject::AddSprite(std::string key, std::string spriteId)
{
	auto sprite = CSprites::GetInstance()->Get(spriteId);
	this->sprites.insert(std::make_pair(key, sprite));
}

void CGameObject::AddAnimation(std::string key, std::string animationId)
{
	LPANIMATION ani = CAnimations::GetInstance()->Get(animationId);
	this->animations.insert(std::make_pair(key, ani));
}

void CGameObject::TakeDamage(float damage)
{
	this->hp -= damage;
	this->SetInEffect(true);

	if (this->hp <= 0 
		&& (dynamic_cast<CEnemyEyelet*>(this) 
		|| dynamic_cast<CEnemyStuka*>(this))) {
		LPGAMEOBJECT item = nullptr;
		item = new CItemHealth;
		item->SetPosition(this->position);
		CGame::GetInstance()->PushToQueueObject(item);
	}
}

void CGameObject::ActiveByRadiusDistance(float activeDistance)
{
	if (this->active == false) {
		Vector2D playerPosition = CPlayer::GetInstance()->GetPlayer()->GetPosition();
		float distance = PositionsDistance(playerPosition, this->position);
		if (this->nx == 1 && distance < activeDistance && playerPosition.x > this->position.x) {
			this->active = true;
		}
		else if (this->nx == -1 && distance > activeDistance && playerPosition.x < this->position.x) {
			this->active = true;
		}
	}
}

D3DCOLOR CGameObject::GetRenderColor()
{
	if (this->effected == false || this->effectDuration == 0) {
		this->effected = false;
		this->effectDuration = 0;
		return DrawArgbColorDefault();
	}
	else {
		this->effectDuration += 1; // TODO: make the same duration of triggerTag
		if (this->effectDuration > 10) {
			this->effectDuration = 0;
			return DrawArgbColorDefault();
		}
		if (this->effectDuration % 2 == 0) {
			return DrawArgbColorDefault();
		}
		else {
			return D3DCOLOR_ARGB(255, 125, 125, 125);
		}
	}
}

void CGameObject::PhysicalUpdate(std::vector<LPGAMEOBJECT>* coObjects)
{
	for (auto collider : this->colliders) {
		collider->PhysicalUpdate(coObjects);
	}
}

void CGameObject::OnCollision(CCollider2D* selfCollider, LPCOLLISIONEVENT collision)
{
}

void CGameObject::OnTrigger(CCollider2D* selfCollider, LPCOLLISIONEVENT collsion)
{
}

void CGameObject::CleanTriggerTag()
{
	this->triggerTags.erase(
		std::remove_if(this->triggerTags.begin(), this->triggerTags.end(), [&](STriggerTag const& tag) {
			return (GetTickCount64() - tag.start > 1200); // Time period out of 500 will be remove
			}),
		this->triggerTags.end());
}

CGameObject::~CGameObject()
{
	this->animations.clear();
}
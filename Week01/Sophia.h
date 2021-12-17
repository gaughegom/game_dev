#pragma once
#ifndef _GAMEPLAYER_H
#define _GAMEPLAYER_H

#include "GameObject.h"
#include "Player.h"
#include "InputHandler.h"
#include "SophiaWheel.h"
#include "SophiaBody.h"
#include "SophiaCabin.h"
#include "SophiaGun.h"
#include "Brick.h"

#define	SOPHIA_BOX_IDLE				Vector2D(24.0f, 17.0f)
#define SOPHIA_OFFSET_IDLE			Vector2D(0.0f, 4.5f)
#define SOPHIA_BOX_TILE45			Vector2D(23.0f, 29.0f)
#define SOPHIA_BOX_UP90				Vector2D(24.0f, 32.0f)

constexpr auto SOPHIA_MAX_BULLETS = 3;

class CSophiaCabin;
class CSophiaWheel;
class CSophiaBody;
class CSophiaGun;

enum class SophiaDirectState : int
{
	Stay = 0,
	RightMove = 1,
	LeftMove = -1
};

enum class SophiaActionState : int {
	Idle = 0,
	Tile45 = 1,
	Up90 = 2,
	OpenIn = 3,
	OpenOut = 4
};

class CSophia : public CGameObject
{
private:
	CSophiaWheel* leftWheel;
	CSophiaWheel* rightWheel;
	CSophiaBody* body;
	CSophiaCabin* cabin;
	CSophiaGun* gun;

	D3DCOLOR renderColor = DRAW_COLOR_DEFAULT;

	SophiaDirectState directState;
	SophiaActionState actionState;

	// TODO: only test
	float prevHp;

	void InitParts();
public:
	// state
	DWORD stateTime;
	DWORD prevStateTime;
	// bullet
	int bullets;
	DWORD prevBulletTime;
	DWORD delayBullet = 180;

	CSophia();

	void Update(DWORD dt);
	void Render();

	D3DCOLOR GetSophiaPartRenderColor() { return this->renderColor; }
	void ListenKeyEvent();
	void SubcribeDirectState(SophiaDirectState directState);
	void SetActionState(SophiaActionState actionState);

	void RecoverHealth(float recover) { this->hp += recover; }

	void UpdateColliders();
	void OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent);
	void OnTrigger(CCollider2D* self, LPCOLLISIONEVENT coEvent);

	void OnCollisionWithEnemy(LPCOLLISIONEVENT coEvent);

	SophiaDirectState GetDirectState() { return this->directState; }
	SophiaActionState GetActionState() { return this->actionState; }

	CSophiaWheel* GetLeftWheel() { return this->leftWheel; }
	CSophiaWheel* GetRightWheel() { return this->rightWheel; }
	
	void DecreaseBullet();
};

#endif // !_GAMEPLAYER_H


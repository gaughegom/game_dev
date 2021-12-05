#pragma once
#ifndef _GAMEPLAYER_H
#define _GAMEPLAYER_H

#include "GameObject.h"
#include "ControllerObject.h"
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

#define SOPHIA_MAX_BULLETS			3

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
};

class CSophia : public CGameObject
{
private:
	CSophiaWheel* leftWheel;
	CSophiaWheel* rightWheel;
	CSophiaBody* body;
	CSophiaCabin* cabin;
	CSophiaGun* gun;

	SophiaDirectState directState;
	SophiaActionState actionState;

public:
	// state
	DWORD stateTime;
	DWORD prevStateTime;
	// bullet
	int bullets;
	DWORD prevBulletTime;
	DWORD delayBullet = 300;

	CSophia();

	void Update(DWORD dt);
	void Render();
	void ListenKeyEvent();

	void SubcribeDirectState(SophiaDirectState directState);
	void SubcribeActionState(SophiaActionState actionState);

	void UpdateColliders();
	void OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent);
	void OnTrigger(CCollider2D* self, LPCOLLISIONEVENT coEvent);

	SophiaDirectState GetDirectState() { return this->directState; }
	SophiaActionState GetActionState() { return this->actionState; }

	CSophiaWheel* GetLeftWheel() { return this->leftWheel; }
	CSophiaWheel* GetRightWheel() { return this->rightWheel; }
	
	void DecreaseBullet();
};

#endif // !_GAMEPLAYER_H


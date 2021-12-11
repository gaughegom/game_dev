#pragma once
#ifndef _JASON_H
#define _JASON_H

#include "Player.h"
#include "GameObject.h"
#include "Camera.h"
#include "EnemyEyelet.h"
#include "JasonDirectionState.h"
#include "InputHandler.h"
#include "Brick.h"
#include "Sophia.h"

#define V_JASON_BOX_SIZE	Vector2D(8.0f, 16.0f)
#define ANIMATION_JASON_STAY_ID	"stay"
#define ANIMATION_JASON_WALK_ID	"walk"

class CJasonDirectionState;

enum class JasonDirectState : int {
	STAY = 0,
	RIGHTWALK = 1,
	LEFTWALK = -1,
	JUMP = 2
};

class CJason : public CGameObject{
private:
	CJasonDirectionState* directState;

public:
	CJason();

	
	void Update(DWORD dt);
	void Render();

	void UpdateColliders();
	void OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent);
	void OnTrigger(CCollider2D* self, LPCOLLISIONEVENT coEvent);

	void OnCollisionWithEnemy(LPCOLLISIONEVENT coEvent);

	void ListenKeyEvent();

	void SubcribeDirectionState(JasonDirectState directState);
};

#endif // !_JASON_H

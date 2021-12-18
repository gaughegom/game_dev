#pragma once
#ifndef _ENEMY_BALLCARRY_H
#define _ENEMY_BALLCARRY_H

#include "EnemyBase.h"

class CEnemyBallcarry : public CEnemyBase {
private:
	bool activeAttack = false;
	DWORD timeAttack;
	bool activeMove = false;

public:
	CEnemyBallcarry();

	void Update(DWORD dt);
	void Render();

	void OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent);
	void OnTrigger(CCollider2D* self, LPCOLLISIONEVENT coEvent);
};

#endif // !_ENEMY_BALLCARRY_H

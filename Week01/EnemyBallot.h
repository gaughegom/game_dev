#pragma once
#ifndef _ENEMY_BALLOT_H
#define _ENEMY_BALLOT_H

#include "EnemyBase.h"

class CEnemyBallot : public CEnemyBase {
private:
	DWORD prevAttackTime;
	Vector2D vTarget;
	bool isFlying = false;

public:
	CEnemyBallot();

	void Update(DWORD dt);
	void Render();

	void OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent);
	void OnTrigger(CCollider2D* self, LPCOLLISIONEVENT coEvent);
};

#endif // !_ENEMY_BALLOT_H

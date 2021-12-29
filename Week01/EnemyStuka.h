#pragma once
#ifndef _ENEMY_STUKA_H
#define _ENEMY_STUKA_H

#include "EnemyBase.h"

#define C_STUKA			0
#define V_STUKA_BOXSIZE		Vector2D(18, 18)

enum class EStukaState : int {
	FREE_FLYING,
	BACK_FLYING,
	ATTACKING
};

class CEnemyStuka : public CEnemyBase {
private:
	int stepMove = 0;
	float attackFromY;

	void OnFreeFlying();
	void OnBackFlying();
	void OnAttacking();

public:
	EStukaState state;
	DWORD dwPrevAttackTime;
	
	
	CEnemyStuka();

	void Update(DWORD dt);
	void Render();

	void OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent);
	void OnTrigger(CCollider2D* self, LPCOLLISIONEVENT coEvent);
};

#endif // !_ENEMY_STUKA_H

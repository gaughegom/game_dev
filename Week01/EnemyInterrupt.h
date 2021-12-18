#pragma once
#ifndef _ENEMY_INTERRUPT_H
#define _ENEMY_INTERRUPT_H

#include "EnemyBase.h"

class CEnemyInterrupt : public CEnemyBase {
private:
	int existNeoworm = 0;
	DWORD prevTimeNeoworm;

public:
	CEnemyInterrupt();

	void Update(DWORD dt);
	void Render();

	void OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent);
	void OnTrigger(CCollider2D* self, LPCOLLISIONEVENT coEvent);
};

#endif // !_ENEMY_INTERRUPT_H

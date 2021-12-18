#pragma once
#ifndef _ENEMY_BALLBOMB_H
#define _ENEMY_BALLBOMB_H

#include "EnemyBase.h"

class CEnemyBallbomb : public CEnemyBase {
private:
	DWORD bornTime = GetTickCount64();

public:
	CEnemyBallbomb();

	void Update(DWORD dt);
	void Render();

	void OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent);
	void OnTrigger(CCollider2D* self, LPCOLLISIONEVENT coEvent);
};

#endif // !_ENEMY_BALLBOMB_H

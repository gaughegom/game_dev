#pragma once
#ifndef _ENEMY_EYELET_H
#define _ENEMY_EYELET_H

#include "EnemyBase.h"

#define C_EYELET			0
#define C_EYELET_REVERSE	1
#define	V_EYELET_BOXSIZE	Vector2D(18, 15)

class CEnemyEyelet : public CEnemyBase {
private:

public:
	CEnemyEyelet();

	void Update(DWORD dt);
	void Render();

	void OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent);
	void OnTrigger(CCollider2D* self, LPCOLLISIONEVENT coEvent);

};

#endif // !_ENEMY_EYELET_H

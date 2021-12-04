#pragma once
#ifndef _ENEMY_EYELET_H
#define _ENEMY_EYELET_H

#include "GameObject.h"

#define C_EYELET			0
#define C_EYELET_REVERSE	1

class CEnemyEyelet : public CGameObject {
private:

public:
	CEnemyEyelet();

	void Update(DWORD dt);
	void Render();

	void OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent);
	void OnTrigger(CCollider2D* self, LPCOLLISIONEVENT coEvent);

	~CEnemyEyelet();
};

#endif // !_ENEMY_EYELET_H

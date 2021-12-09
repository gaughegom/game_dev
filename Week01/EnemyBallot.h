#pragma once
#ifndef _ENEMY_BALLOT_H
#define _ENEMY_BALLOT_H

#include "GameObject.h"

class CEnemyBallot : public CGameObject {
private:

public:
	CEnemyBallot();

	void Update(DWORD dt);
	void Render();

	void OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent);
	void OnTrigger(CCollider2D* self, LPCOLLISIONEVENT coEvent);
};

#endif // !_ENEMY_BALLOT_H

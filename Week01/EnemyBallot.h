#pragma once
#ifndef _ENEMY_BALLOT_H
#define _ENEMY_BALLOT_H

#include "GameObject.h"

#define	V_BALLOT_BOXSIZE			Vector2D(18, 18)
#define BALLOT_DEFAULT_ANIMATION	"default"
#define BALLOT_DEFAULT_SPRITE_IDLE	"idle"

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

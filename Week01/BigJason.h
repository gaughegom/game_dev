#pragma once
#ifndef _BIG_JASON_H
#define _BIG_JASON_H

#include "GameObject.h"

#define ANI_BIG_JASON_WALK_HORIZON_ID		"walk"
#define	ANI_BIG_JASON_WALK_UP_ID			"walk-up"
#define	ANI_BIG_JASON_WALK_DOWN_ID			"walk-down"
#define	SPR_BIG_JASON_STAY_HORIZON_ID		"stay-horizon"
#define SPR_BIG_JASON_STAY_UP_ID			"stay-up"
#define SPR_BIG_JASON_STAY_DOWN_ID			"stay-down"

enum class BigJasonDirectState : int {
	STAY = 0,
	RIGHTWALK = 1,
	LEFTWALK = -1,
	UPWALK = 2,
	DOWNWALK = -2
};

class CBigJason : public CGameObject {
private:
	BigJasonDirectState directState;

public:
	CBigJason();

	void Update(DWORD dt);
	void Render();

	void ListenKeyEvent();
	void UpdateColliders();

	void OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent);
	void OnTrigger(CCollider2D* self, LPCOLLISIONEVENT coEvent);

};

#endif // !_BIG_JASON_H

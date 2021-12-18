#pragma once
#ifndef _BIG_JASON_H
#define _BIG_JASON_H

#include "GameObject.h"

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
	std::string currentSpriteState;

	// TODO: debug only
	float prevHp;

	void Shooting();
public:
	CBigJason();

	void Update(DWORD dt);
	void Render();

	void UpdateColliders();
	void ListenKeyEvent();
	void SubcribeDirectState(BigJasonDirectState newState);
	std::string MappingStateOfAnimation();

	void OnCollisionWithEnemy(LPCOLLISIONEVENT coEvent);

	void OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent);
	void OnTrigger(CCollider2D* self, LPCOLLISIONEVENT coEvent);

};

#endif // !_BIG_JASON_H

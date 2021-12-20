#pragma once
#ifndef _BIG_JASON_H
#define _BIG_JASON_H

#include "CharacterBase.h"
#include "EnemyBase.h"
#include "ItemBase.h"

enum class BigJasonDirectState : int {
	STAY = 0,
	RIGHTWALK = 1,
	LEFTWALK = -1,
	UPWALK = 2,
	DOWNWALK = -2
};

class CBigJason : public CCharaterBase {
private:
	BigJasonDirectState directState;
	std::string currentSpriteState;

	void Shooting();
public:
	CBigJason();

	void Update(DWORD dt);
	void Render();

	void UpdateColliders();
	void ListenKeyEvent();
	void SubcribeDirectState(BigJasonDirectState newState);
	std::string MappingStateOfAnimation();


	void OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent);
	void OnTrigger(CCollider2D* self, LPCOLLISIONEVENT coEvent);

	void OnCollisionWithEnemy(CEnemyBase* const& other);
	void OnCollisionWithItem(CItemBase* const& other);
};

#endif // !_BIG_JASON_H

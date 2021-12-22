#pragma once
#ifndef _ENEMY_LAZER_GUARD_H
#define _ENEMY_LAZER_GUARD_H

#include "EnemyBase.h"

class CEnemyLazerGuard : public CEnemyBase {
private:
	DWORD prevAttackTime;

public:
	CEnemyLazerGuard();

	void Update(DWORD dt) override;
	void Render() override;

	void OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent) override;
};

#endif // !_ENEMY_LAZER_GUARD_H

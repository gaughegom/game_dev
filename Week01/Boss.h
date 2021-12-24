#pragma once
#ifndef _BOSS_H
#define _BOSS_H

#include "EnemyBase.h"

class CBoss : public CEnemyBase {
private:
public:
	CBoss();

	void Update(DWORD dt) override;
	void Render() override;

	void OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent) override;
};

#endif // !_BOSS_H

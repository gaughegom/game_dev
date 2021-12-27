#pragma once
#ifndef _BOSS_SPIN_BULLET_H
#define _BOSS_SPIN_BULLET_H

#include "BulletBase.h"

class CBossSpinBullet : public CBulletBase {
private:
public:
	CBossSpinBullet();

	void Update(DWORD dt) override;
	void Render() override;
	void OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent) override;
};

#endif // !_BOSS_SPIN_BULLET_H

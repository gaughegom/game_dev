#pragma once
#ifndef _LAZER_GUARD_BULLET_H
#define _LAZER_GUARD_BULLET_H

#include "BulletBase.h"

class CLazerGuardBullet : public CBulletBase {
private:
	Vector2D vTarget = VectorZero();

public:
	CLazerGuardBullet();

	void Update(DWORD dt) override;
	void Render() override;

	void OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent) override;
};

#endif // !_LAZER_GUARD_BULLET_H

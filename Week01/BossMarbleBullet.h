#pragma once
#ifndef _BOSS_MARBLE_BULLET_H
#define _BOSS_MARBLE_BULLET_H

#include "BulletBase.h"

class CBossMarbleBullet : public CBulletBase {
private:
public:
	CBossMarbleBullet();

	void Update(DWORD dt) override;
	void Render() override;
	void OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent) override;
};

#endif // !_BOSS_MARBLE_BULLET_H

#pragma once
#ifndef _BIG_JASON_BULLET_H
#define _BIG_JASON_BULLET_H

#include "BulletBase.h"

enum class BigJasonBulletDirection : int {
	LEFT	= 0,
	RIGHT	= 1,
	UP		= 2,
	DOWN	= 3,
};

class CBigJasonBullet : public CBulletBase {
private:
	BigJasonBulletDirection directState;
	bool inSinWave = false;

public:
	CBigJasonBullet(BigJasonBulletDirection state);

	void Update(DWORD dt) override;
	void Render() override;

	void SetDirectState(BigJasonBulletDirection directState) { this->directState = directState; }

	void OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent) override;
};

#endif // !_BIG_JASON_BULLET_H

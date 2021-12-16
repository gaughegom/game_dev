#pragma once
#ifndef _BIG_JASON_BULLET_H
#define _BIG_JASON_BULLET_H

#include "GameObject.h"

enum class BigJasonBulletDirection : int {
	LEFT	= 0,
	RIGHT	= 1,
	UP		= 2,
	DOWN	= 3,
};

class CBigJasonBullet : public CGameObject {
private:
	BigJasonBulletDirection directState;

public:
	CBigJasonBullet(BigJasonBulletDirection state);

	void Update(DWORD dt);
	void Render();

	void SetDirectState(BigJasonBulletDirection directState) { this->directState = directState; }

	void OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent);
	void OnTrigger(CCollider2D* self, LPCOLLISIONEVENT coEvent);
};

#endif // !_BIG_JASON_BULLET_H

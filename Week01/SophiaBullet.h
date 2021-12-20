#pragma once
#ifndef _SOPHIA_BASIC_BULLET_H
#define _SOPHIA_BASIC_BULLET_H

#include "BulletBase.h"

class CSophiaBullet : public CBulletBase {

public:
	CSophiaBullet(int direct); // 0: vertical, -1: left, 1: right

	void Update(DWORD dt) override;
	void Render() override;
	void OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent) override;

	void OnDelete();
};

#endif // !_SOPHIA_BASIC_BULLET_H

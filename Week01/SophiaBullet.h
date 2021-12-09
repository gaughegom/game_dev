#pragma once
#ifndef _SOPHIA_BASIC_BULLET_H
#define _SOPHIA_BASIC_BULLET_H

#include "GameObject.h"	

class CSophiaBullet : public CGameObject {

public:
	CSophiaBullet(int direct); // 0: vertical, -1: left, 1: right

	void Update(DWORD dt);
	void Render();
	void OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent);
	void OnTrigger(CCollider2D* self, LPCOLLISIONEVENT coEvent);

	void OnDelete();

	~CSophiaBullet();
};

#endif // !_SOPHIA_BASIC_BULLET_H

#pragma once
#ifndef _SOPHIA_BASIC_BULLET_H
#define _SOPHIA_BASIC_BULLET_H

#include "GameObject.h"	

#define V_BULLET_BOXSIZE_HORIZON	Vector2D(22, 6)
#define	V_BULLET_BOXSIZE_VERTICAL	Vector2D(6, 22)

class CSophiaBullet : public CGameObject {
private:
	LPSPRITE sprite;

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

#pragma once
#ifndef _ENEMY_BASE_H
#define _ENEMY_BASE_H

#include "GameObject.h"

class CEnemyBase : public CGameObject {
private:
protected:
	virtual bool InLifeCycle();

public:
	CEnemyBase();

	virtual void Update(DWORD dt);
	virtual void Render();

	virtual void OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent);
	virtual void OnTrigger(CCollider2D* self, LPCOLLISIONEVENT coEvent);
};

#endif // !_ENEMY_BASE_H

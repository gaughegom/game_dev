#pragma once
#ifndef _BULLET_BASE_H
#define _BULLET_BASE_H

#include "GameObject.h"

class CBulletBase : public CGameObject {
private:
protected:
public:
	CBulletBase();

	virtual void Update(DWORD dt);
	virtual void Render();

	virtual void OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent);
};

#endif // !_BULLET_BASE_H

#pragma once
#ifndef _BULLET_BASE_H
#define _BULLET_BASE_H

#include "GameObject.h"

class CBulletBase : public CGameObject {
private:
protected:
	int level = 1;	// TODO: Upgrade damage when eat item power

public:
	CBulletBase();

	void UpgradeLevel(const int& value);

	virtual void Update(DWORD dt);
	virtual void Render();

	virtual void OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent);
};

#endif // !_BULLET_BASE_H

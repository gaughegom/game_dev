#pragma once
#ifndef _CHARACTER_BASE_H
#define _CHARACTER_BASE_H

#include "GameObject.h"

class CCharaterBase : public CGameObject {
private:
protected:
	float prevHp;

public:
	CCharaterBase();

	virtual void Update(DWORD dt);
	virtual void Render();

	virtual void OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent);
	virtual void OnTrigger(CCollider2D* self, LPCOLLISIONEVENT coEvent);
};

#endif // !_CHARACTER_BASE_H

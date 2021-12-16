#pragma once
#ifndef _ITEM_HEALTH_H
#define _ITEM_HEALTH_H

#include "GameObject.h"

class CItemHealth : public CGameObject {
private:
	float recoverHeath = 10;

public:
	CItemHealth();

	void Update(DWORD dt);
	void Render();

	void OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent);
	void OnTrigger(CCollider2D* self, LPCOLLISIONEVENT coEvent);

	float GetRecoverHealth() { return this->recoverHeath; }
	void SetUsed() { this->hp = 0; }
};

#endif // !_ITEM_HEALTH_H

#pragma once
#ifndef _ITEM_HEALTH_H
#define _ITEM_HEALTH_H

#include "ItemBase.h"

class CItemHealth : public CItemBase {
private:
	float recoverHeath = 10;

public:
	CItemHealth();

	void Update(DWORD dt);
	void Render();

	void OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent);
	void OnTrigger(CCollider2D* self, LPCOLLISIONEVENT coEvent);

	void OnUse() { CItemBase::OnUse(); }

	float GetRecoverHealth() const { return this->recoverHeath; }
};

#endif // !_ITEM_HEALTH_H

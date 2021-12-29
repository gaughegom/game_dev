#pragma once
#ifndef _ITEM_BASE_H
#define _ITEM_BASE_H

#include "GameObject.h"
#include "Sound.h"

class CItemBase : public CGameObject {
private:

public:
	CItemBase();

	virtual void Update(DWORD dt);
	virtual void Render();

	virtual void OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent);
	virtual void OnTrigger(CCollider2D* self, LPCOLLISIONEVENT coEvent);

	virtual void OnUse() { 
		this->hp = 0;
		CSound::GetInstance()->PlayWaveFile("useItem");
	}

};

#endif // !_ITEM_BASE_H

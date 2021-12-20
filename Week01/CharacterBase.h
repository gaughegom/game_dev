#pragma once
#ifndef _CHARACTER_BASE_H
#define _CHARACTER_BASE_H

#include "GameObject.h"

class CCharaterBase : public CGameObject {
private:
protected:
	float prevHp;
	
	bool inThorny = false;
	DWORD prevThornyDamage;

public:
	CCharaterBase();

	virtual void Update(DWORD dt);
	virtual void Render();

	virtual void OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent);
	virtual void OnTrigger(CCollider2D* self, LPCOLLISIONEVENT coEvent);

	void SetInThorny(const bool& value) { this->inThorny = value; this->ResetPrevTimeThoryDamage(); }
	bool IsInThorny() const { return this->inThorny; }
	void ResetPrevTimeThoryDamage() { this->prevThornyDamage = GetTickCount64(); }
	DWORD GetPrevTimeThornyDamage() const { return this->prevThornyDamage; }
};

#endif // !_CHARACTER_BASE_H

#pragma once
#ifndef _SOPHIA_GUN_H
#define _SOPHIA_GUN_H

#include "Sophia.h"

class CSophia;
enum class SophiaActionState;

class CSophiaGun : public CGameObject {
private:
	CSophia* self;

public:
	CSophiaGun();
	CSophiaGun(CSophia* target);

	void Update(DWORD dt);
	void Render();

	int MappingGunSpriteState(SophiaActionState actionState);
};

#endif // !_SOPHIA_GUN_H

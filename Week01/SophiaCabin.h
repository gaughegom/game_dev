#pragma once
#ifndef _SOPHIA_CABIN_H
#define _SOPHIA_CABIN_H

#include "Sophia.h"

class CSophia;
enum class SophiaActionState;

class CSophiaCabin : public CGameObject {
private:
	CSophia* self;

public:
	CSophiaCabin(CSophia* target);
	
	void Update(DWORD dt);
	void Render();

	int MappingCabinSpriteState(SophiaActionState actionState);
};

#endif // !_SOPHIA_CABIN_H

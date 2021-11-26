#pragma once
#ifndef _SOPHIA_CABIN_H
#define _SOPHIA_CABIN_H

#include "Sophia.h"

class CSophia;
enum SophiaActionState;

class CSophiaCabin : public CGameObject {
private:
	CSophia* sophia;

public:
	CSophiaCabin(CSophia* target);
	
	void Update(DWORD dt);
	void Render();

	int MappingCabinSpriteState(SophiaActionState actionState);
};

#endif // !_SOPHIA_CABIN_H

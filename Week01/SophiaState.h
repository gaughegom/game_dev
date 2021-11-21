#pragma once
#ifndef _SOPHIA_STATE_H
#define _SOPHIA_STATE_H

#include "Sophia.h"

class CSophia;

class CSophiaState {
public:
	virtual void Update(DWORD dt, int nx, CSophia& sophia);
	virtual void Render(CSophia& sophia);
};

#endif // !_SOPHIA_STATE_H

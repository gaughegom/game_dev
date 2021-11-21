#pragma once
#ifndef _SOPHIA_STATE_H
#define _SOPHIA_STATE_H

#include "Sophia.h"

class CSophia;

class CSophiaState {
public:
	virtual void UpdateGame(DWORD dt, int nx, CSophia& sophia);
	virtual void RenderGame(CSophia& sophia);
};

#endif // !_SOPHIA_STATE_H

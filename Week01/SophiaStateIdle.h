#pragma once
#ifndef _SOPHIA_STATE_IDLE_H
#define _SOPHIA_STATE_IDLE_H

#include "SophiaState.h"

class CSophiaStateIdle : public CSophiaState {
public:
	virtual void Update(DWORD dt, int nx, CSophia& sophia);
	virtual void Render();
};

#endif // !_SOPHIA_STATE_IDLE_H

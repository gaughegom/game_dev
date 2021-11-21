#pragma once
#ifndef _SOPHIA_DIRECT_STATE_H
#define _SOPHIA_DIRECT_STATE_H

#include "Sophia.h"

class CSophia;

class CSophiaDirectState {
private:
	CSophia* target;
	int state;

public:
	CSophiaDirectState();
	CSophiaDirectState(CSophia* target);

	void SetTarget(CSophia* target);

	void Stay();
	void MoveBackward();
	void MoveForward();

	void SetState(int state);
	int GetState();
};

#endif // !_SOPHIA_DIRECT_STATE_H

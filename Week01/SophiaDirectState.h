#pragma once
#ifndef _SOPHIA_DIRECT_STATE_H
#define _SOPHIA_DIRECT_STATE_H

#include "Sophia.h"

class CSophia;

class CSophiaDirectState {
private:
	CSophia* target;

public:
	CSophiaDirectState();
	CSophiaDirectState(CSophia* target);

	void SetTarget(CSophia* target);

	void SetNotMove();
	void SetMoveBackward();
	void SetMoveForward();
};

#endif // !_SOPHIA_DIRECT_STATE_H

#pragma once
#ifndef _SOPHIA_ACTION_STATE_H
#define _SOPHIA_ACTION_STATE_H

#include "Sophia.h"

class CSophia;

class CSophiaActionState {
private:
	CSophia* target;

public:
	CSophiaActionState();
	CSophiaActionState(CSophia* target);

	void SetTarget(CSophia* target);
	void SetIdleState();
};

#endif // !_SOPHIA_ACTION_STATE_H

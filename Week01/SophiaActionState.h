#pragma once
#ifndef _SOPHIA_ACTION_STATE_H
#define _SOPHIA_ACTION_STATE_H

#include "Sophia.h"

class CSophia;

class CSophiaActionState {
private:
	CSophia* target;
	int state;

public:
	CSophiaActionState();
	CSophiaActionState(CSophia* target);

	void SetTarget(CSophia* target);
	void IdleState();
	void Tilt45State();
	void Up90State();

	void SetState(int state);
	int GetState();
};

#endif // !_SOPHIA_ACTION_STATE_H

#pragma once
#ifndef _JASON_DIRECTION_STATE_H
#define _JASON_DIRECTION_STATE_H

#include "Jason.h"

class CJason;

class CJasonDirectionState
{
private:
	CJason* target;
	int state;

public:
	CJasonDirectionState();
	CJasonDirectionState(CJason* target);

	void SetTarget(CJason* target);
	void SetState(int state);
	int GetState();

	std::string MappingStateOfAnimation(int state);

	void Stay();
	void MoveBackward();
	void MoveForward();
	void MoveUpward();
	void MoveDownWard();
};

#endif // !_JASON_DIRECTION_STATE_H

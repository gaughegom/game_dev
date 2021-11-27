#pragma once
#ifndef _JASON_DIRECTION_STATE_H
#define _JASON_DIRECTION_STATE_H

#include "Jason.h"

class CJason;
enum class JasonDirectState;

class CJasonDirectionState
{
private:
	CJason* target;
	JasonDirectState state;

public:
	CJasonDirectionState();
	CJasonDirectionState(CJason* target);

	void SetTarget(CJason* target);
	void SetState(JasonDirectState state);
	JasonDirectState GetState();

	std::string MappingStateOfAnimation(JasonDirectState state);

	void Stay();
	void MoveBackward();
	void MoveForward();
};

#endif // !_JASON_DIRECTION_STATE_H

#pragma once
#ifndef _JASON_H
#define _JASON_H

#include "GameObject.h"
#include "GameMovement.h"
#include "JasonDirectionState.h"
#include "InputHandler.h"
#include "ControllerObject.h"

#define	C_JASON_HORIZON	0 // move
#define C_JASON_UP		1
#define C_JASON_DOWN	2
#define C_JASON_IDLE_L	3 // idle
#define C_JASON_IDLE_U	4
#define C_JASON_IDLE_D	5

class CJasonDirectionState;

class CJason : public CGameObject, public CControllerObject {
private:
	CJasonDirectionState* directState;

public:
	CJason();
	
	void Update(DWORD dt);
	void Render();
	void ListenKeyEvent();

	void EdgeCollisionHandler();

	void SubcribeDirectionState(int directState);
};

#endif // !_JASON_H

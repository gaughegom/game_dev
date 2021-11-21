#pragma once
#ifndef _GAMENPC_H
#define _GAMENPC_H

#include "resources.h"
#include "GameObject.h"
#include "Game.h"

class CEnemyRobot : public CGameObject
{
public:
	CEnemyRobot();

	void UpdateGame(DWORD dt);
	void RenderGame();
	
	int GetState();
	void SetState(int state);
};

#endif // !_GAMENPC_H

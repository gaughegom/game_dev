#pragma once
#ifndef _GAMENPC_H

#include "resources.h"
#include "GameObject.h"
#include "Game.h"

class CGameNpc : public CGameObject
{
public:
	void Update(DWORD dt);
	void Render();
	
	int Get_state();
	void Set_state(int state);
	
	void NpcMoveFollowClock(int backbufferWidth, int backbufferHeight);
	void NpcMoveReverseClock(int backbufferHeight, int backbufferWidth);
};

#endif // !_GAMENPC_H

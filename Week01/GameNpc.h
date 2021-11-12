#pragma once
#ifndef _GAMENPC_H
#define _GAMENPC_H

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
	
	void Npc_move_follow_clock(int backbufferWidth, int backbufferHeight);
	void Npc_move_reverse_clock(int backbufferHeight, int backbufferWidth);
};

#endif // !_GAMENPC_H

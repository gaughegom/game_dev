#pragma once
#ifndef _GAMENPC_H

#include "GameObject.h"
#include "Game.h"
#include "resources.h"

class CGameNpc : public CGameObject
{
public:
	void Update(DWORD dt);
	void Render();
	int Get_state();
	void Set_state(int state);
};

#endif // !_GAMENPC_H

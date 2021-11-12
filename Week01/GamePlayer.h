#pragma once
#ifndef _GAMEPLAYER_H
#define _GAMEPLAYER_H

#include "resources.h"
#include "GameObject.h"
#include "Game.h"

class CGamePlayer : public CGameObject
{
public:
	void Update(DWORD dt);
	void Render();
	int Get_state();
	void Set_state(int state);
};

#endif // !_GAMEPLAYER_H


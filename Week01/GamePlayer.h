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
	void EdgeCollisionHandler(int backbufferWidth, int backbufferHeight);
	void Render();
	void SetState(int state);
	int GetState();
};

#endif // !_GAMEPLAYER_H


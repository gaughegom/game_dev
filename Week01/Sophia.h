#pragma once
#ifndef _GAMEPLAYER_H
#define _GAMEPLAYER_H

#include "resources.h"
#include "GameObject.h"
#include "Game.h"

class CSophia : public CGameObject
{
private:
	Vector2D vt2LeftWheel;
	Vector2D vt2RightWheel;

	LPSPRITE lpsBody;
	LPSPRITE lpsCabin;

public:
	CSophia();

	void Update(DWORD dt);
	void Render();
	void SetState(int state);
	int GetState();

	void EdgeCollisionHandler(int width);
};

#endif // !_GAMEPLAYER_H


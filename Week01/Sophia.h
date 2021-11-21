#pragma once
#ifndef _GAMEPLAYER_H
#define _GAMEPLAYER_H

#include "GameObject.h"
#include "SophiaDirectState.h"
#include "SophiaActionState.h"


#define LEFT_WHEEL		0
#define RIGHT_WHEEL		1

class CSophiaDirectState;
class CSophiaActionState;

class CSophia : public CGameObject
{
private:
	CSophiaDirectState* directState;
	CSophiaActionState* actionState;


public:
	DWORD stateTime;
	DWORD prevStateTime;

	Vector2D leftWheel;
	Vector2D rightWheel;
	LPSPRITE lpsBody;
	Vector2D body;
	LPSPRITE lpsCabin;
	Vector2D cabin;
	LPSPRITE lpsGun;
	Vector2D gun;

	CSophia();

	void Update(DWORD dt);
	void Render();

	void SubcribeDirectState(int directState);
	void SubcribeActionState(int actionState);

	void EdgeCollisionHandler(int width);
};

#endif // !_GAMEPLAYER_H


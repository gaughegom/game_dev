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
	/*CSophiaState* wheelState;
	CSophiaState* directState;*/

	CSophiaDirectState* directState;
	CSophiaActionState* actionState;

public:
	Vector2D leftWheel;
	Vector2D rightWheel;
	LPSPRITE lpsBody;
	Vector2D body;
	LPSPRITE lpsCabin;
	Vector2D cabin;

	CSophia();

	void Update(DWORD dt);
	void Render();
	void SetState(int state);
	int GetState();

	void EdgeCollisionHandler(int width);
};

#endif // !_GAMEPLAYER_H


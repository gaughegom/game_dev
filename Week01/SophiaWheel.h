#pragma once
#ifndef _SOPHIA_WHEEL_H
#define	_SOPHIA_WHEEL_H

#include "GameObject.h"
#include "Sophia.h"

#define C_A_DEFAULT_KEY	"default"

class CSophia;
enum SophiaDirectState;
enum SophiaActionState;

class CSophiaWheel : public CGameObject {
private:
	CSophia* sophia;

public:
	CSophiaWheel(CSophia* target);

	void Update(DWORD dt);
	void Render();

	void HandleAnimationDirectState(SophiaDirectState directState);
	void HandleAnimationActionState(SophiaActionState actionState);

	void NotMove();
	void RightMove();
	void LeftMove();
};

#endif // !_SOPHIA_WHEEL_H

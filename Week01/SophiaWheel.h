#pragma once
#ifndef _SOPHIA_WHEEL_H
#define	_SOPHIA_WHEEL_H

#include "GameObject.h"
#include "Sophia.h"

#define C_A_DEFAULT_KEY				"default"

#define V_LEFT_POSITION_IDLE		Vector2D(-8.0f, 0.0f)
#define V_LEFT_POSITION_TILE45		Vector2D(8.0f, 0.0f)
#define V_LEFT_POSITION_UP90		Vector2D(-6.5f, 0.0f)
#define V_RIGHT_POSITION_IDLE		Vector2D(6.5f, 0.0f)
#define V_RIGHT_POSITION_TILE45		Vector2D(-5.0f, 0.0f)
#define V_RIGHT_POSITION_UP90		Vector2D(5.0f, 0.0f)


class CSophia;
enum class SophiaDirectState;
enum class SophiaActionState;

class CSophiaWheel : public CGameObject {
private:
	CSophia* self;

public:
	CSophiaWheel(CSophia* target);

	void Update(DWORD dt);
	void Render();

	void HandleAnimationDirectState();
	void HandleAnimationActionState();

	void NotMove();
	void RightMove();
	void LeftMove();
};

#endif // !_SOPHIA_WHEEL_H

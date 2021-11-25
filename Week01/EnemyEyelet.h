#pragma once
#ifndef _ENEMY_EYELET_H
#define _ENEMY_EYELET_H

#include "GameObject.h"

#define C_EYELET			0
#define C_EYELET_REVERSE	1

class CEnemyEyelet : public CGameObject {
private:

public:
	CEnemyEyelet();

	void Update(DWORD dt);
	void Render();
};

#endif // !_ENEMY_EYELET_H

#pragma once
#ifndef _ENEMY_DRAP_H
#define _ENEMY_DRAP_H

#include "GameObject.h"

#define C_DRAP			0 // drap animation
#define C_DRAP_REVERSE	1

class CEnemyDrap : public CGameObject {
private:
	
public:
	CEnemyDrap();

	void Update(DWORD dt);
	void Render();
};

#endif // !_ENEMY_DRAP_H

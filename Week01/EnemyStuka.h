#pragma once
#ifndef _ENEMY_STUKA_H
#define _ENEMY_STUKA_H

#include "GameObject.h"

#define C_STUKA			0

class CEnemyStuka : public CGameObject {
private:

public:
	CEnemyStuka();

	void Update(DWORD dt);
	void Render();
};

#endif // !_ENEMY_STUKA_H

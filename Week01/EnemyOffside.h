#pragma once
#ifndef _ENEMY_OFFSIDE_H
#define _ENEMY_OFFSIDE_H

#include "GameObject.h"

#define CA_OFFSIDE			0

class CEnemyOffside : public CGameObject {
private:

public:
	CEnemyOffside();

	void Update(DWORD dt);
	void Render();
};

#endif // !_ENEMY_OFFSIDE_H

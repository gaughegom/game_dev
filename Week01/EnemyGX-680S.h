#pragma once
#ifndef _ENEMY_GX680S_H
#define _ENEMY_GX680S_H

#include "GameObject.h"

class CEnemyGX680S : public CGameObject {
private:

public:
	CEnemyGX680S();

	void Update(DWORD dt);
	void Render();

	void OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent);
};

#endif // !_ENEMY_GX680S_H

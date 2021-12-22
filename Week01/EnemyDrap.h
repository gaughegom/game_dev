#pragma once
#ifndef _ENEMY_DRAP_H
#define _ENEMY_DRAP_H

#include "EnemyBase.h"

#define C_DRAP			0 // drap animation
#define C_DRAP_REVERSE	1

class CEnemyDrap : public CEnemyBase {
private:
	
public:
	CEnemyDrap();

	void Update(DWORD dt) override;
	void Render() override;

	void OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent) override;
};

#endif // !_ENEMY_DRAP_H

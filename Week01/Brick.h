#pragma once
#ifndef _BRICK_H
#define _BRICK_H

#include "GameObject.h"

#define BRICK_WIDTH		16.0f

class CBrick : public CGameObject {
public:
	CBrick();
	void Update(DWORD dt);
	void Render();
};

#endif // !_BRICK_H

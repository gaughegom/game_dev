#pragma once
#ifndef _BRICK_H
#define _BRICK_H

#include "GameObject.h"

class CBrick : public CGameObject {
public:
	CBrick(); // WARM: not used anymore
	CBrick(Vector2D boundingBox);

	void Update(DWORD dt) override;
	void Render() override;

	void OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent) override;
	void OnTrigger(CCollider2D* self, LPCOLLISIONEVENT coEvent) override;
};

#endif // !_BRICK_H

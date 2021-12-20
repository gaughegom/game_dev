#pragma once
#ifndef _THORNY_BRICK_H
#define _THORNY_BRICK_H

#include "GameObject.h"

class CThornyBrick : public CGameObject {
private:
public:
	CThornyBrick(Vector2D boundingBox);

	void Update(DWORD dt);
	void Render();

	void OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent);
	void OnTrigger(CCollider2D* self, LPCOLLISIONEVENT coEvent);
};


#endif // !_THORNY_BRICK_H

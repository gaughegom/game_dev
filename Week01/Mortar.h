#pragma once
#ifndef _MORTAR_H
#define _MORTAR_H

#include "GameObject.h"

class CMortar : public CGameObject {
private:
public:
	CMortar(Vector2D boundingBox);

	void Update(DWORD dt) override;
	void Render() override;

	void OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent) override;
};


#endif // !_MORTAR_H

#pragma once
#ifndef _GX_680S_BULLET
#define _GX_680S_BULLET

#include "BulletBase.h"

class CGX680SBullet : public CBulletBase {
private:
public:
	CGX680SBullet();

	void Update(DWORD dt) override;
	void Render() override;

	void OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent) override;
};

#endif // !_GX_680S_BULLET

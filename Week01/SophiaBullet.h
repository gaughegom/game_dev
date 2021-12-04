#pragma once
#ifndef _SOPHIA_BULLET_H
#define _SOPHIA_BULLET_H

#include "GameObject.h"	
#include "SophiaGun.h"

class CSophiaBullet : public CGameObject {
private:
	CSophiaGun* gun;
	int bullets;

public:
	CSophiaBullet();
	CSophiaBullet(CSophiaGun* target);

	void SetTarget(CSophiaGun* target);

	void Update(DWORD dt);
	void Render();
};

#endif // !_SOPHIA_BULLET_H

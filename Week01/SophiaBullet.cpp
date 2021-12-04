#include "SophiaBullet.h"

CSophiaBullet::CSophiaBullet()
{
	// add sprite

	// set velocity

	// set colliders
}

CSophiaBullet::CSophiaBullet(CSophiaGun* target) : CSophiaBullet::CSophiaBullet()
{
	this->gun = target;
}

void CSophiaBullet::SetTarget(CSophiaGun* target)
{
	this->gun = target;
}

void CSophiaBullet::Update(DWORD dt)
{
}

void CSophiaBullet::Render()
{
}

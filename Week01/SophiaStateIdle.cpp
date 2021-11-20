#include "SophiaStateIdle.h"

void CSophiaStateIdle::Update(DWORD dt, int nx, CSophia& sophia)
{
	sophia.leftWheel = Vector2D(-8, 0);
	sophia.rightWheel = Vector2D(8, 0);
	sophia.body = Vector2D(0, 1);
	sophia.cabin = Vector2D(-3.5 * nx, 9);

	auto sprites = CSprites::GetInstance();
	sophia.lpsCabin = sprites->Get(SPRITE_SOPHIA_CABIN);
}

void CSophiaStateIdle::Render()
{
}

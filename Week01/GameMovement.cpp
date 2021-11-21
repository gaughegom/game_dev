#include "GameMovement.h"


void LinearMovement(Vector2D& position, Vector2D& velocity, DWORD dt)
{
	position += velocity * dt;
	position.y -= PLAYER_GRAVITY * dt;
}

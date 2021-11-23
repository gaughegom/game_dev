#include "GameMovement.h"

void LinearMoveWithGravity(Vector2D& position, Vector2D& velocity, DWORD dt)
{
	position.x += velocity.x * dt;
	position.y += velocity.y * dt;

	velocity.y += -PLAYER_GRAVITY;
}

void LinearMove(Vector2D& position, Vector2D& velocity, DWORD dt)
{
	position += velocity * dt;
}

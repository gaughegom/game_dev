#include "GameEnv.h"
#include "Jason.h"

void InGravityAffect(CGameObject* self, DWORD dt)
{
	if (self->GetColliders().at(0)->IsDynamic()) {
		Vector2D velocity = self->GetVelocity();
		velocity.y += -GAME_GRAVITY * dt;
		self->SetVelocity(velocity);
	}
}

void InHorizontalMove(CGameObject* self, DWORD dt)
{
	Vector2D position = self->GetPosition();
	position.x += self->GetVelocity().x * dt;
	self->SetPosition(position);
}

void InSinWaveXAsix(CGameObject* self, DWORD dt, float amplitude)
{
	self->duration += 0.2f * dt;
	if (self->duration > 360)
		self->duration = 0;	//reset omega
	Vector2D position = self->GetPosition();
	position.y += amplitude * sin(self->duration * PI / 180);
	self->SetPosition(position);
}

void InSinWaveYAsix(CGameObject* self, DWORD dt, float amplitude)
{
	self->duration += 0.2f * dt;
	if (self->duration > 360)
		self->duration = 0;	//reset omega
	Vector2D position = self->GetPosition();
	position.x += amplitude * sin(self->duration * PI / 180);
	self->SetPosition(position);
}

int RandomDirect()
{
	int randNx = rand() % 2;
	if (randNx == 0) randNx = -1;
	return randNx;
}

int Random(int begin, int end)
{
	return (rand() % (end - begin + 1) + begin);
}

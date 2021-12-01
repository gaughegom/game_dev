#include "SimulationEnvroment.h"

void InGravityAffect(CGameObject* self, DWORD dt)
{
	if (self->GetColliders().at(0)->GetDynamic()) {
		Vector2D velocity = self->GetVelocity();
		velocity.y += -PLAYER_GRAVITY * dt;
		self->SetVelocity(velocity);
	}
}

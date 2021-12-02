#include "SimulationEnvroment.h"
#include "Jason.h"

void InGravityAffect(CGameObject* self, DWORD dt)
{
	//if (static_cast<CJason*>(self)) {
	//	DebugOut(L"dynamic: %d\n", self->GetColliders().at(0)->GetDynamic());
	//}

	if (self->GetColliders().at(0)->GetDynamic()) {
		Vector2D velocity = self->GetVelocity();
		velocity.y += -PLAYER_GRAVITY * dt;
		self->SetVelocity(velocity);
	}
}

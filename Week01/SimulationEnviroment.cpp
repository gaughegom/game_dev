#include "SimulationEnvroment.h"
#include "Jason.h"

void InGravityAffect(CGameObject* self, DWORD dt)
{
	//if (static_cast<CJason*>(self)) {
	//	DebugOut(L"dynamic: %d\n", self->GetColliders().at(0)->IsDynamic());
	//}

	if (self->GetColliders().at(0)->IsDynamic()) {
		Vector2D velocity = self->GetVelocity();
		velocity.y += -GAME_GRAVITY * dt;
		self->SetVelocity(velocity);
	}
}

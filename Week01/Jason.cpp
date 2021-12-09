#include "Jason.h"

CJason::CJason()
{	
	this->AddAnimation(ANIMATION_JASON_STAY_ID, "aniJIdle");
	this->AddAnimation(ANIMATION_JASON_WALK_ID, "aniJWalk");

	this->directState = new CJasonDirectionState(this);
	this->directState->SetState(JasonDirectState::STAY);

	this->SetVelocity(VectorZero());
	this->hp = 100;
	this->damage = 10;
	this->active = false;
	this->ground = false;

	//
	this->colliders.clear();
	auto collider = new CCollider2D(this, true, false, VectorZero(), V_JASON_BOX_SIZE);
	this->colliders.push_back(collider);
	this->SetColliders(colliders);
}

void CJason::Update(DWORD dt)
{
	InGravityAffect(this, dt);

	if (CControllerObject::GetInstance()->GetSelectId() == ControllerObjectID::JASON) {
		ListenKeyEvent();
	}
}

void CJason::Render()
{
	std::string key = this->directState->MappingStateOfAnimation();
		
	this->animations.at(key)->
		Render(this->position, -this->nx, DRAW_COLOR_DEFAULT);
}

void CJason::UpdateColliders()
{

}

void CJason::ListenKeyEvent()
{
	auto input = CInputHandler::GetInstance();

	// map direct state
	if (input->IsKeyDown(DIK_RIGHT)) {
		this->directState->SetState(JasonDirectState::RIGHTWALK);
	}
	else if (input->IsKeyDown(DIK_LEFT)) {
		this->directState->SetState(JasonDirectState::LEFTWALK);
	}
	else {
		this->directState->SetState(JasonDirectState::STAY);
	}

	if (input->OnKeyDown(JUMP_KEYCODE) && this->ground) {
		this->ground = false;
		this->directState->SetState(JasonDirectState::JUMP);
	}

	if (input->OnKeyDown(SWITCH_CONTROLLER_KEYCODE)) {
		auto controller = CControllerObject::GetInstance();
		if (controller->GetSophia()->GetColliders().at(0)->GetBoundingBox()
			.Contain(this->colliders.at(0)->GetBoundingBox())) {
			controller->GetSophia()->SetActionState(SophiaActionState::OpenIn);
			controller->Select(ControllerObjectID::SOPHIA);
		}
	}

	// subcribe direct state
	this->SubcribeDirectionState(this->directState->GetState());
}

void CJason::SubcribeDirectionState(JasonDirectState directState)
{
	this->directState->SetState(directState);
	switch (directState)
	{
	case JasonDirectState::RIGHTWALK:
		this->SetVelocity(Vector2D(PLAYER_MOVING_SPEED, this->velocity.y));
		this->nx = 1;
		this->directState->MoveForward();
		break;

	case JasonDirectState::LEFTWALK:
		this->SetVelocity(Vector2D(-PLAYER_MOVING_SPEED, this->velocity.y));
		this->nx = -1;
		this->directState->MoveBackward();
		break;

	case JasonDirectState::STAY:
		this->SetVelocity(Vector2D(0, this->velocity.y));
		this->directState->Stay();
		break;

	case JasonDirectState::JUMP:
		this->SetVelocity(Vector2D(this->velocity.x, PLAYER_JUMP_FORCE));
		this->directState->Jump();
		break;
	}
}

void CJason::OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent)
{
	if (dynamic_cast<CBrick*>(coEvent->object)) {
		if (!this->ground && coEvent->ny == 1) {
			this->ground = true;
		}
	}
	else {
		this->OnCollisionWithEnemy(coEvent);
	}

}

void CJason::OnTrigger(CCollider2D* self, LPCOLLISIONEVENT coEvent)
{
}

void CJason::OnCollisionWithEnemy(LPCOLLISIONEVENT coEvent)
{
	bool isSuffered = false;
	if (dynamic_cast<CEnemyEyelet*>(coEvent->object)) isSuffered = true;
	// TODO: add more enemies later
	// TODO: make enemy go throw player, player take damage

	if (isSuffered) {
		this->hp -= coEvent->object->GetDamage();
		STriggerTag tag = STriggerTag(coEvent->object);
		this->AddTriggerTag(coEvent->object);
		coEvent->object->AddTriggerTag(this);
	}
}

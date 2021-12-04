#include "ControllerObject.h"

CControllerObject* CControllerObject::__instance = nullptr;

CControllerObject::CControllerObject()
{
}

void CControllerObject::SetSophiaAndJason(CSophia* sophia, CJason* jason)
{
	this->sophia = sophia;
	this->jason = jason;
}

void CControllerObject::Select(ControllerObjectID id)
{
	this->selectedId = id;
	if (id == ControllerObjectID::SOPHIA) {
		SelectSophia();
	}
	else {
		SelectJason();
	}
}

void CControllerObject::SelectSophia()
{
	auto camera = CCamera::GetInstance();
	camera->SetTarget(this->sophia);
	for (auto co : this->sophia->GetColliders()) {
		co->SetTrigger(false);
		co->SetDynamic(true);
	}
	this->jason->SetPosition(this->sophia->GetPosition());
	this->jason->SetVelocity(Vector2D(0, this->jason->GetVelocity().y));
	this->jason->SubcribeDirectionState(JasonDirectState::JUMP);
	this->jason->SetActive(false);
}

void CControllerObject::SelectJason()
{
	for (auto co : this->sophia->GetColliders()) {
		co->SetTrigger(true);
		co->SetDynamic(false);
	}
	auto camera = CCamera::GetInstance();
	camera->SetTarget(this->jason);
	this->jason->SetActive(true);
	this->jason->SetPosition(this->sophia->GetPosition());
	this->jason->SetNx(this->sophia->GetNx());
	this->jason->SubcribeDirectionState(JasonDirectState::JUMP);
}

CControllerObject* CControllerObject::GetInstance()
{
	if (__instance == nullptr) {
		__instance = new CControllerObject;
	}
	return __instance;
}

CControllerObject::~CControllerObject()
{
	delete this->sophia;
	delete this->jason;
}

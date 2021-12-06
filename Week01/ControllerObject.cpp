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
	if (id == ControllerObjectID::SOPHIA) {
		SelectSophia();
	}
	else if (id == ControllerObjectID::JASON) {
		SelectJason();
	}
}

void CControllerObject::SelectSophia()
{
	if (GetTickCount64() - lastSwitchTime < delaySwitch) {
		return;
	}

	for (auto co : this->sophia->GetColliders()) {
		co->SetTrigger(false);
		co->SetDynamic(true);
	}
	//
	auto camera = CCamera::GetInstance();
	camera->SetTarget(this->sophia);
	//
	this->jason->SetPosition(this->sophia->GetPosition());
	this->jason->SetVelocity(Vector2D(0, this->jason->GetVelocity().y));
	this->jason->SubcribeDirectionState(JasonDirectState::JUMP);
	this->jason->SetActive(false);

	this->selectedId = ControllerObjectID::SOPHIA;
	this->lastSwitchTime = GetTickCount64();
}

void CControllerObject::SelectJason()
{
	if (GetTickCount64() - lastSwitchTime < delaySwitch) {
		return;
	}

	for (auto co : this->sophia->GetColliders()) {
		co->SetTrigger(true);
		co->SetDynamic(false);
	}
	//
	auto camera = CCamera::GetInstance();
	camera->SetTarget(this->jason);
	//
	this->jason->SetActive(true);
	this->jason->SetPosition(this->sophia->GetPosition());
	this->jason->SetNx(this->sophia->GetNx());
	this->jason->SubcribeDirectionState(JasonDirectState::JUMP);
	
	this->selectedId = ControllerObjectID::JASON;
	this->lastSwitchTime = GetTickCount64();
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
}

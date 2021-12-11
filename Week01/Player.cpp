#include "Player.h"

CPlayer* CPlayer::__instance = nullptr;

CPlayer::CPlayer()
{
}

void CPlayer::AddPlayerCharacter(LPGAMEOBJECT character)
{
	if (character == nullptr) return;

	if (dynamic_cast<CSophia*>(character)) {
		this->sophia = (CSophia*)character;
	}
	else if (dynamic_cast<CJason*>(character)) {
		this->jason = (CJason*)character;
	}
}

void CPlayer::Select(PlayerCharacterId id)
{
	if (id == PlayerCharacterId::SOPHIA) {
		SelectSophia();
	}
	else if (id == PlayerCharacterId::JASON) {
		SelectJason();
	}
}

void CPlayer::SelectSophia()
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
	this->jason->SetVelocity(Vector2D(0, this->jason->GetVelocity().y));
	this->jason->SubcribeDirectionState(JasonDirectState::JUMP);
	this->jason->SetActive(false);
	this->jason->SetPosition(this->sophia->GetPosition());
	this->sophia->SetActionState(SophiaActionState::Idle);

	this->selectedId = PlayerCharacterId::SOPHIA;
	this->player = this->sophia;
	this->lastSwitchTime = GetTickCount64();
}

void CPlayer::SelectJason()
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
	this->sophia->SetActionState(SophiaActionState::Idle);

	this->selectedId = PlayerCharacterId::JASON;
	this->player = this->jason;
	this->lastSwitchTime = GetTickCount64();
}

CPlayer* CPlayer::GetInstance()
{
	if (__instance == nullptr) {
		__instance = new CPlayer;
	}
	return __instance;
}

CPlayer::~CPlayer()
{
}
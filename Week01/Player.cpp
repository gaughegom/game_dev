#include "Player.h"

CPlayer* CPlayer::__instance = nullptr;

CPlayer::CPlayer()
{
}

void CPlayer::AddPlayerCharacter(const LPGAMEOBJECT& character)
{
	if (character == nullptr) return;

	if (dynamic_cast<CSophia*>(character)) {
		this->sophia = (CSophia*)character;
	}
	else if (dynamic_cast<CJason*>(character)) {
		this->jason = (CJason*)character;
	}
	else if (dynamic_cast<CBigJason*>(character)) {
		this->bigJason = (CBigJason*)character;
	}
}

void CPlayer::SelectPlayer(const LPGAMEOBJECT& player)
{
	if (dynamic_cast<CSophia*>(player)) {
		this->SelectSophia();
	}
	else if (dynamic_cast<CJason*>(player)) {
		this->SelectJason();
	}
	else if (dynamic_cast<CBigJason*>(player)) {
		this->SelectBigJason();
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

	//this->sophia->SetActionState(SophiaActionState::Idle);
	this->sophia->SetActionState(SophiaActionState::OpenIn);
	this->sophia->prevInTime = GetTickCount64();

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

	//this->sophia->SetActionState(SophiaActionState::Idle);
	this->sophia->SetActionState(SophiaActionState::OpenOut);
	this->sophia->prevOutTime = GetTickCount64();

	this->selectedId = PlayerCharacterId::JASON;
	this->player = this->jason;
	this->lastSwitchTime = GetTickCount64();
}

void CPlayer::SelectBigJason()
{
	auto camera = CCamera::GetInstance();
	camera->SetTarget(this->bigJason);

	this->selectedId = PlayerCharacterId::BIGJASON;
	this->player = this->bigJason;
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

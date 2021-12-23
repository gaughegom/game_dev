#include "PlayerHealthHub.h"
#include "Camera.h"
#include "Player.h"

constexpr auto HubId0 = 0;
constexpr auto HubId1 = 1;
constexpr auto HubId2 = 2;
constexpr auto HubId3 = 3;
constexpr auto HubId4 = 4;
constexpr auto HubId5 = 5;
constexpr auto HubId6 = 6;
constexpr auto HubId7 = 7;
constexpr auto HubId8 = 8;

CPlayerHealthHub* CPlayerHealthHub::__instance = nullptr;

CPlayerHealthHub::CPlayerHealthHub()
{
	LPSPRITE sprite0 = CSprites::GetInstance()->Get("sprHealthHub0");
	LPSPRITE sprite1 = CSprites::GetInstance()->Get("sprHealthHub1");
	LPSPRITE sprite2 = CSprites::GetInstance()->Get("sprHealthHub2");
	LPSPRITE sprite3 = CSprites::GetInstance()->Get("sprHealthHub3");
	LPSPRITE sprite4 = CSprites::GetInstance()->Get("sprHealthHub4");
	LPSPRITE sprite5 = CSprites::GetInstance()->Get("sprHealthHub5");
	LPSPRITE sprite6 = CSprites::GetInstance()->Get("sprHealthHub6");
	LPSPRITE sprite7 = CSprites::GetInstance()->Get("sprHealthHub7");
	LPSPRITE sprite8 = CSprites::GetInstance()->Get("sprHealthHub8");


	this->sprites.insert(std::make_pair(HubId0, sprite0));
	this->sprites.insert(std::make_pair(HubId1, sprite1));
	this->sprites.insert(std::make_pair(HubId2, sprite2));
	this->sprites.insert(std::make_pair(HubId3, sprite3));
	this->sprites.insert(std::make_pair(HubId4, sprite4));
	this->sprites.insert(std::make_pair(HubId5, sprite5));
	this->sprites.insert(std::make_pair(HubId6, sprite6));
	this->sprites.insert(std::make_pair(HubId7, sprite7));
	this->sprites.insert(std::make_pair(HubId8, sprite8));
}

void CPlayerHealthHub::Render()
{
	CCamera* camera = CCamera::GetInstance();

	int hubId = (int)CPlayer::GetInstance()->GetPlayer()->GetHp() / 10;

	this->sprites.at(hubId)->Draw(camera->GetPosition() + (Vector2D(20.0f, -150.0f)), 1, DrawArgbColorDefault(), DrawLayer02);
}

CPlayerHealthHub* CPlayerHealthHub::GetInstance()
{
	if (__instance == nullptr) {
		__instance = new CPlayerHealthHub;
	}
	return __instance;
}

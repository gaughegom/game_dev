#pragma once
#ifndef _CONTROLLER_OBJECT_H
#define _CONTROLLER_OBJECT_H

#include "Sophia.h"
#include "Jason.h"
#include "BigJason.h"

#define SWITCH_CONTROLLER_KEYCODE	DIK_LSHIFT
#define JUMP_KEYCODE				DIK_SPACE
#define SHOTTING_KEYCODE			DIK_D

enum class PlayerCharacterId : int {
	SOPHIA		= 0,
	JASON		= 1,
	BIGJASON	= 2
};

class CSophia;
class CJason;
class CBigJason;
class CPlayer
{
private:
	static CPlayer* __instance;

	PlayerCharacterId selectedId;
	CGameObject* player;
	CSophia* sophia;
	CJason* jason;
	CBigJason* bigJason;

	void SelectSophia();
	void SelectJason();
	void SelectBigJason();
public:
	DWORD delaySwitch = 300;
	DWORD lastSwitchTime; // fix auto select jason

	CPlayer();

	void AddPlayerCharacter(const LPGAMEOBJECT& character);

	void SelectPlayer(const LPGAMEOBJECT& player);
	PlayerCharacterId GetSelectId() const { return this->selectedId; }
	CGameObject* GetPlayer() const { return this->player ? this->player : nullptr; }

	CSophia* GetSophia() const { return this->sophia; }
	CJason* GetJason() const { return this->jason; }
	CBigJason* GetBigJason() const { return this->bigJason; }

	static CPlayer* GetInstance();

	~CPlayer();
};

#endif // !_CONTROLLER_OBJECT_H

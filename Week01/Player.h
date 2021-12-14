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

	void AddPlayerCharacter(LPGAMEOBJECT character);

	void SelectPlayer(LPGAMEOBJECT player);
	PlayerCharacterId GetSelectId() { return this->selectedId; }
	CGameObject* GetPlayer() { 
		if (this->player == nullptr)
			return nullptr;
		return this->player;
	}

	CSophia* GetSophia() { return this->sophia; }
	CJason* GetJason() { return this->jason; }
	CBigJason* GetBigJason() { return this->bigJason; }

	static CPlayer* GetInstance();

	~CPlayer();
};

#endif // !_CONTROLLER_OBJECT_H

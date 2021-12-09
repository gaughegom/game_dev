#pragma once
#ifndef _CONTROLLER_OBJECT_H
#define _CONTROLLER_OBJECT_H

#include "Sophia.h"
#include "Jason.h"

#define SWITCH_CONTROLLER_KEYCODE	DIK_LSHIFT
#define JUMP_KEYCODE				DIK_SPACE
#define SHOTTING_KEYCODE			DIK_D

enum class ControllerObjectID : int {
	SOPHIA = 0,
	JASON = 1,
};

class CSophia;
class CJason;
class CControllerObject
{
private:
	static CControllerObject* __instance;

	ControllerObjectID selectedId;
	CGameObject* player;
	CSophia* sophia;
	CJason* jason;

	void SelectSophia();
	void SelectJason();
public:
	DWORD delaySwitch = 300;
	DWORD lastSwitchTime; // fix auto select jason
	CControllerObject();

	void SetSophiaAndJason(CSophia* sophia, CJason* jason);
	void Select(ControllerObjectID id);
	ControllerObjectID GetSelectId() { return this->selectedId; }
	CGameObject* GetPlayer() { return this->player; }

	CSophia* GetSophia() { return this->sophia; }
	CJason* GetJason() { return this->jason; }

	static CControllerObject* GetInstance();

	~CControllerObject();
};

#endif // !_CONTROLLER_OBJECT_H

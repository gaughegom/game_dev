#pragma once
#ifndef _CONTROLLER_OBJECT_H
#define _CONTROLLER_OBJECT_H

#include "Sophia.h"
#include "Jason.h"

#define SWITCH_CONTROLLER_KEYCODE	DIK_A

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
	CSophia* sophia;
	CJason* jason;

	void SelectSophia();
	void SelectJason();
public:
	DWORD delaySwitch = 300;
	DWORD lastSwitchTime;
	CControllerObject();

	void SetSophiaAndJason(CSophia* sophia, CJason* jason);
	void Select(ControllerObjectID id);
	ControllerObjectID GetSelectId() { return this->selectedId; }

	CSophia* GetSophia() { return this->sophia; }
	CJason* GetJason() { return this->jason; }

	static CControllerObject* GetInstance();

	~CControllerObject();
};

#endif // !_CONTROLLER_OBJECT_H

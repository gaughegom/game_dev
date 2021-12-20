#pragma once
#ifndef _TRIGGER_TAG_H
#define _TRIGGER_TAG_H

#include "GameObject.h"

class CGameObject;
typedef CGameObject* LPGAMEOBJECT;
struct STriggerTag {
	DWORD start;
	LPGAMEOBJECT target;

	// default
	STriggerTag(const LPGAMEOBJECT& target) {
		this->start = GetTickCount64();
		this->target = target;
	}

	STriggerTag(const DWORD& start, const LPGAMEOBJECT& target) {
		this->start = start;
		this->target = target;
	}
};

#endif // !_TRIGGER_TAG_H

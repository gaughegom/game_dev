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
	STriggerTag(LPGAMEOBJECT target) {
		this->start = 300;
		this->target = target;
	}

	STriggerTag(DWORD start, LPGAMEOBJECT target) {
		this->start = start;
		this->target = target;
	}
};

#endif // !_TRIGGER_TAG_H

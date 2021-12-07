#pragma once
#ifndef _TRIGGER_TAG_H
#define _TRIGGER_TAG_H

#include "GameObject.h"

class CGameObject;
typedef CGameObject* LPGAMEOBJECT;
struct STriggerTag {
	DWORD expires;
	LPGAMEOBJECT target;

	// default
	STriggerTag(LPGAMEOBJECT target) {
		this->expires = 300;
		this->target = target;
	}

	STriggerTag(DWORD expires, LPGAMEOBJECT target) {
		this->expires = expires;
		this->target = target;
	}
};

#endif // !_TRIGGER_TAG_H

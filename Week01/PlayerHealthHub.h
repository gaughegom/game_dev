#pragma once
#ifndef _PLAYER_HEALTH_HUB_C
#define _PLAYER_HEALTH_HUB_C

#include "Sprites.h"

class CPlayerHealthHub {
private:
	static CPlayerHealthHub* __instance;

	std::unordered_map<int, LPSPRITE> sprites;

public:
	CPlayerHealthHub();

	void Render();

	static CPlayerHealthHub* GetInstance();
};

#endif // !_PLAYER_HEALTH_HUB_C

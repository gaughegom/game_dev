#pragma once
#ifndef _SMALL_DESTROY_EFFECT_H
#define _SMALL_DESTROY_EFFECT_H

#include "GameObject.h"

class CSmallDestroyEffect : public CGameObject {
private:

public:
	CSmallDestroyEffect();

	void Update(DWORD dt);
	void Render();

};

#endif // !_SMALL_DESTROY_EFFECT_H

#pragma once
#ifndef _BIG_DESTROY_EFFECT_H
#define _BIG_DESTROY_EFFECT_H

#include "GameObject.h"

class CBigDestroyEffect : public CGameObject {
private:

public:
	CBigDestroyEffect();

	void Update(DWORD dt);
	void Render();
};

#endif // !_BIG_DESTROY_EFFECT_H

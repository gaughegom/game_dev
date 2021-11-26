#pragma once
#ifndef _SOPHIA_WHEEL_H
#define	_SOPHIA_WHEEL_H

#include "GameObject.h"

class CSophiaWheel : public CGameObject {
private:
	CGameObject* target;

public:
	CSophiaWheel(CGameObject* target);

	void Update(DWORD dt);
	void Render();
};

#endif // !_SOPHIA_WHEEL_H

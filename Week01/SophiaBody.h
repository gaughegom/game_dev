#pragma once
#ifndef _SOPHIA_BODY_H
#define _SOPHIA_BODY_H

#include "Sophia.h"

class CSophia;
enum SophiaActionState;

class CSophiaBody : public CGameObject {
private:
	CSophia* sophia;

public:
	CSophiaBody(CSophia* target);

	void Update(DWORD dt);
	void Render();

	void HandleAnimationActionState(SophiaActionState actionState);
};

#endif // !_SOPHIA_BODY_H

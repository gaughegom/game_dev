#pragma once
#ifndef _BOSS_TRIGGER_H
#define _BOSS_TRIGGER_H

#include "GameObject.h"

class CBossTrigger : public CGameObject {
private:
	DWORD startTrigger;
	bool triggering = false;

public:
	CBossTrigger();

	void Update(DWORD dt) override;
	void Render() override;
};


#endif // !_BOSS_TRIGGER_H

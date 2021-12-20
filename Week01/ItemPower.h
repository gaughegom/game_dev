#pragma once
#ifndef _ITEM_POWER_H
#define _ITEM_POWER_H

#include "ItemBase.h"

class CItemPower : public CItemBase {
private:
	float bonusDamage = 10;

public:
	CItemPower();

	void Update(DWORD dt) override;
	void Render() override;

	float GetBonusDamage() const { return this->bonusDamage; }
};

#endif // !_ITEM_POWER_H

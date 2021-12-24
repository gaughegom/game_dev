#pragma once
#ifndef _BIGJASON_FLASH_SHOOTING_Y_H
#define _BIGJASON_FLASH_SHOOTING_Y_H

#include "GameObject.h"

class CBigJasonFlashShootingY : public CGameObject {
private:
public:
	CBigJasonFlashShootingY();

	void Update(DWORD dt) override;
	void Render() override;
};

#endif // !_BIGJASON_FLASH_SHOOTING_Y_H

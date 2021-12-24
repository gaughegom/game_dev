#pragma once
#ifndef _BIGJASON_FLASH_SHOOTING_X_H
#define _BIGJASON_FLASH_SHOOTING_X_H

#include "GameObject.h"

class CBigJasonFlashShootingX : public CGameObject {
private:
public:
	CBigJasonFlashShootingX();

	void Update(DWORD dt) override;
	void Render() override;
};


#endif // !_BIGJASON_FLASH_SHOOTING_X_H

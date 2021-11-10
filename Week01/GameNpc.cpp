#include "GameNpc.h"

void CGameNpc::Update(DWORD dt)
{
	CGameObject::Update(dt);

	int backbufferWidth = CGame::Get_instance()->Get_backbuffer_width();
	int backbufferHeight = CGame::Get_instance()->Get_backbuffer_height();
	if (this->vx > 0 && this->x > backbufferWidth - PLAYER_WIDTH) {
		this->x = backbufferWidth - PLAYER_WIDTH;
	}
	if (this->vx < 0 && this->x < 0) {
		this->x = 0;
	}
	if (this->vy > 0 && this->y > backbufferHeight - PLAYER_HEIGHT) {
		this->y = backbufferHeight - PLAYER_HEIGHT;
	}
	if (this->vy < 0 && this->y < 0) {
		this->y = 0;
	}
}

void CGameNpc::Render()
{
}

int CGameNpc::Get_state()
{
	return 0;
}

void CGameNpc::Set_state(int state)
{
}

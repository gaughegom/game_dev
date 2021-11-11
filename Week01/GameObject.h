#pragma once
#ifndef _GAMEOBJECT_H

#include "resources.h"
#include "Sprites.h"
#include "Game.h"

using namespace std;

class CGameObject
{
protected:

	float x;
	float y;

	float vx;
	float vy;

	int nx;

	int state;

	static vector<LPANIMATION> animations;

public:
	void Set_position(float x, float y) { this->x = x, this->y = y; }
	void Set_speed(float vx, float vy) { this->vx = vx, this->vy = vy; }

	void Set_state(int state) { this->state = state; }
	int Get_state() { return this->state; }


	static void Add_animation(int aniId);

	CGameObject();

	void Update(DWORD dt);
	virtual void Render() = 0;
	~CGameObject();
};

#endif // !_GAMEOBJECT_H

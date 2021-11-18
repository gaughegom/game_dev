#pragma once
#ifndef _RESOURCES_H
#define _RESOURCES_H

#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <time.h>
#include <unordered_map>
#include <vector>
#include <dinput.h>
#include "debug.h"
#include "Transform.h"

#pragma region WINDOW SETTINGS

#define WINDOW_CLASS_NAME			L"Homework 01"
#define WINDOW_TITLE				L"Homework 01"

#define BACKGROUND_COLOR			D3DCOLOR_XRGB(0, 0, 0)
#define SCREEN_WIDTH				240
#define SCREEN_HEIGHT				180

#define MAX_FRAME_RATE				90

#pragma endregion

#pragma region TEXTURES ID

#define ID_TEXTURES_SOPHIA			0
#define ID_TEXTURES_ENEMY_ROBOT		1

#pragma endregion

#define MARIO_TEXTURE_PATH			L"resources//mario.png"
#define SOPHIA_TEXTURE_PATH			L"resources//player.png"
#define ENEMY_TEXTURE_PATH			L"resources//enemies.png"
#define TEXTURE_TRANS_COLOR			D3DCOLOR_XRGB(41, 255, 4)

#pragma region PLAYER SETTINGS

#define PLAYER_START_X				100.0f
#define PLAYER_START_Y				200.0f
#define PLAYER_WIDTH				30
#define PLAYER_HEIGHT				32
#define PLAYER_MOVING_SPEED			0.15f

#pragma endregion

#pragma region NPC SETTINGS

#define NPC_START_X					100.0f
#define NPC_START_Y					180.0f
#define NPC_WIDTH					30
#define NPC_HEIGHT					32
#define NPC_MOVING_SPEED			0.2f

#pragma endregion

#pragma region GAME OBJECT STATE

#define SOPHIA_LEFT_WHEEL			0
#define SOPHIA_WHEEL_RIGHT			5

#define SOPHIA_STATE_IDLE			10
#define SOPHIA_STATE_MOVING_RIGHT	15
#define SOPHIA_STATE_MOVING_LEFT	20

#define NPC_STATE_MOVING_RIGHT		50
#define NPC_STATE_MOVING_LEFT		60
#define NPC_STATE_MOVING_UP			70
#define NPC_STATE_MOVING_DOWN		80

#pragma endregion

#pragma region ANIMATION

#define SOPHIA_LEFT_WHEEL_ANIMATION			0
#define SOPHIA_RIGHT_WHEEL_ANIMATION		1

#define ENEMY_ROBOT_IDLE				2

#define PLAYER_ANIMATION_IDLE_RIGHT			2
#define PLAYER_ANIMATION_IDLE_LEFT			3
#define PLAYER_ANIMATION_MOVING_RIGHT		4
#define PLAYER_ANIMATION_MOVING_LEFT		5


#define NPC_ANIMATION_MOVING_RIGHT		8
#define NPC_ANIMATION_MOVING_LEFT		9
#define NPC_ANIMATION_MOVING_UP			10
#define NPC_ANIMATION_MOVING_DOWN		11

#pragma endregion

#define DIRECTINPUT_VERSION			0x0800
#define KEYBOARD_BUFFER_SIZE		1024

#endif // !_RESOURCES_H


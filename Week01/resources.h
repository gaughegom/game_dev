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

#define BACKGROUND_COLOR			D3DCOLOR_XRGB(172, 201, 223)
#define SCREEN_WIDTH				240
#define SCREEN_HEIGHT				180

#define MAX_FRAME_RATE				90

#pragma endregion

#pragma region TEXTURES ID

#define ID_TEXTURES_PLAYER			0
#define ID_TEXTURES_NPC				1

#pragma endregion

#define MARIO_TEXTURE_PATH			L"resources//mario.png"
#define TEXTURE_TRANS_COLOR			D3DCOLOR_XRGB(255, 255, 255)

#pragma region PLAYER SETTINGS

#define PLAYER_START_X				50.0f
#define PLAYER_START_Y				50.0f
#define PLAYER_WIDTH				30
#define PLAYER_HEIGHT				32
#define PLAYER_MOVING_SPEED			0.15f

#pragma endregion

#pragma region NPC SETTINGS

#define NPC_START_X					0.0f
#define NPC_START_Y					0.0f
#define NPC_WIDTH					30
#define NPC_HEIGHT					32
#define NPC_MOVING_SPEED			0.2f

#pragma endregion

#pragma region GAME OBJECT STATE

#define PLAYER_STATE_IDLE			0
#define PLAYER_STATE_MOVING_RIGHT	10
#define PLAYER_STATE_MOVING_LEFT	20
#define PLAYER_STATE_MOVING_UP		30
#define PLAYER_STATE_MOVING_DOWN	40

#define NPC_STATE_MOVING_RIGHT		50
#define NPC_STATE_MOVING_LEFT		60
#define NPC_STATE_MOVING_UP			70
#define NPC_STATE_MOVING_DOWN		80

#pragma endregion

#pragma region ANIMATION

#define PLAYER_ANIMATION_IDLE_RIGHT			0
#define PLAYER_ANIMATION_IDLE_LEFT			1
#define PLAYER_ANIMATION_IDLE_UP			2
#define PLAYER_ANIMAION_IDLE_DOWN			3	
#define PLAYER_ANIMATION_MOVING_RIGHT		4
#define PLAYER_ANIMATION_MOVING_LEFT		5
#define PLAYER_ANIMATION_MOVING_UP			6
#define PLAYER_ANIMATION_MOVING_DOWN		7

#define NPC_ANIMATION_MOVING_RIGHT		8
#define NPC_ANIMATION_MOVING_LEFT		9
#define NPC_ANIMATION_MOVING_UP			10
#define NPC_ANIMATION_MOVING_DOWN		11

#pragma endregion

#define DIRECTINPUT_VERSION			0x0800
#define KEYBOARD_BUFFER_SIZE		1024

#endif // !_RESOURCES_H


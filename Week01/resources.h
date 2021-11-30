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
#include <type_traits>
#include "Util.h"
#include "Transform.h"

#pragma region WINDOW SETTINGS

#define WINDOW_CLASS_NAME			L"Blaster master"
#define WINDOW_TITLE				L"Blaster master"

#define BACKGROUND_COLOR			D3DCOLOR_XRGB(0, 0, 0)
#define SCREEN_WIDTH				240
#define SCREEN_HEIGHT				180

#define MAX_FRAME_RATE				60

#define	QUADTREE_WIDTH				SCREEN_WIDTH * 10
#define QUADTREE_HEIGHT				SCREEN_HEIGHT * 3

#pragma endregion

#pragma region SCENE PATH

#define SCENE2_PATH				L"database\\scene2.txt"

#pragma endregion

#pragma region TEXTURES PATH

#define SOPHIA_JASON_TEXTURE_PATH			L"textures//player.png"
#define TEXTURE_TRANS_COLOR					D3DCOLOR_XRGB(41, 255, 4)

#pragma endregion

#pragma region PLAYER SETTINGS

#define PLAYER_START_X				100.0f
#define PLAYER_START_Y				50.0f
#define PLAYER_WIDTH				30
#define PLAYER_HEIGHT				32
#define PLAYER_MOVING_SPEED			0.05f
#define PLAYER_GRAVITY				0.018f
#define PLAYER_JUMP_FORCE			0.22f
#define GAME_GROUND					30

#pragma endregion

#pragma region KEYBOARD

#define DIRECTINPUT_VERSION			0x0800
#define KEYBOARD_BUFFER_SIZE		1024

#pragma endregion

#endif // !_RESOURCES_H
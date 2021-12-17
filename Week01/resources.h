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

#pragma region Windows

constexpr auto WINDOW_CLASS_NAME			= L"Blaster master";
constexpr auto WINDOW_TITLE					= L"Blaster master";
constexpr auto WINDOW_SCREEN_WIDTH			= 244;
constexpr auto WINDOW_SCREEN_HEIGHT			= 200;
constexpr auto MAX_FRAME_RATE				= 60;

#define BACKGROUND_COLOR					D3DCOLOR_XRGB(0, 0, 0)
constexpr auto BACKGROUND_LAYER_0			= 0;
constexpr auto BACKGROUND_LAYER_1			= 1;
constexpr auto BACKGROUND_LAYER_2			= 2;
constexpr auto BACKGROUND_LAYER_3			= 3;
constexpr auto BACKGROUND_LAYER_4			= 4;

#pragma endregion

#pragma region File path

constexpr auto GAME_RESOURCE_PATH			= L"database\\game.txt";
constexpr auto SCENE2_PATH					= L"database\\scene2.txt";

#pragma endregion

#pragma region Textures

#define TEXTURE_TRANS_COLOR					D3DCOLOR_XRGB(41, 255, 4)

#pragma endregion

#pragma region Player

constexpr auto PLAYER_MOVING_SPEED			= 0.1f;
constexpr auto PLAYER_JUMP_FORCE			= 0.29f;
constexpr auto GAME_GRAVITY					= 0.0007f;

constexpr auto SOPHIA_BASICBULLET_VELOCITY	= 0.2f;
constexpr auto TIME_SUFFERING_AFFECT		= 300;

#pragma endregion

#pragma region Keyboard

#define DIRECTINPUT_VERSION					0x0800
constexpr auto KEYBOARD_BUFFER_SIZE			= 1024;
#pragma endregion

#pragma region Tileset

constexpr auto TILESET_WIDTH				= 16;
constexpr auto TILESET_HEIGHT				= 16;

#pragma endregion

#define PI									atan(1)*4
constexpr auto ENEMY_VELOCITY_NORMAL		= 0.06f;
constexpr auto ENEMY_ACTIVE_DISTANCE		= 130;

#define	DRAW_COLOR_DEFAULT					D3DCOLOR_ARGB(255, 255, 255, 255)

#endif // !_RESOURCES_H
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
constexpr auto WINDOW_SCREEN_WIDTH			= 256;
constexpr auto WINDOW_SCREEN_HEIGHT			= 224;
constexpr auto MAX_FRAME_RATE				= 60;

#define BACKGROUND_COLOR					D3DCOLOR_XRGB(0, 0, 0)
constexpr auto DrawLayer00			= 0;
constexpr auto DrawLayer01			= 1;
constexpr auto DrawLayer02			= 2;
constexpr auto DrawLayer03			= 3;
constexpr auto DrawLayer04			= 4;

#pragma endregion

#pragma region File path

constexpr auto GameDatabasePath			= L"database\\game.txt";

#pragma endregion

#pragma region Textures

#define TEXTURE_TRANS_COLOR					D3DCOLOR_XRGB(41, 255, 4)

#pragma endregion

#pragma region Player

constexpr auto PlayerMovingSpeed			= 0.1f;
constexpr auto PlayerJumpForce			= 0.29f;
constexpr auto WorldGravity				= 0.0007f;

constexpr auto TimeInDameEffect	= 300;
constexpr auto EnemyNormalVelocity		= 0.06f;

#pragma endregion

#pragma region Keyboard

#define DIRECTINPUT_VERSION					0x0800
constexpr auto KEYBOARD_BUFFER_SIZE			= 1024;
#pragma endregion

#pragma region Tileset

constexpr auto TilesetWidth				= 16;
constexpr auto TilesetHeight				= 16;

#pragma endregion

#define PI									atan(1)*4

#define	DRAW_COLOR_DEFAULT					D3DCOLOR_ARGB(255, 255, 255, 255)

#endif // !_RESOURCES_H
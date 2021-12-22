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
constexpr auto WindowAppClassName			= L"Blaster master";
constexpr auto WindowAppTitle				= L"Blaster master";
constexpr auto MyWindowScreenWidth			= 256;
constexpr auto MyWindowScreenHeight			= 224;
constexpr auto FrameRatePerSecond			= 60;
#pragma endregion

/*
	Draw layer index
*/
constexpr auto DrawLayer00 = 0;
constexpr auto DrawLayer01 = 1;
constexpr auto DrawLayer02 = 2;
constexpr auto DrawLayer03 = 3;
constexpr auto DrawLayer04 = 4;

/*
	Filepath
*/
constexpr auto GameDatabasePath			= L"database\\game.txt";

/*
	Player
*/
constexpr auto PlayerMovingSpeed = 0.1f;
constexpr auto PlayerJumpForce = 0.29f;
constexpr auto WorldGravity	= 0.0007f;
constexpr auto TimeInDameEffect	= 300;
constexpr auto EnemyNormalVelocity = 0.06f;

/*
	Keyboard
*/
#define DIRECTINPUT_VERSION			0x0800
constexpr auto KEYBOARD_BUFFER_SIZE	= 1024;

/*
	Tileset
*/
constexpr auto TilesetWidth	= 16;
constexpr auto TilesetHeight = 16;


constexpr float Pi() { return 3.14f; }
constexpr D3DCOLOR DrawArgbColorDefault() { return D3DCOLOR_ARGB(255, 255, 255, 255); }
constexpr D3DCOLOR DrawBackgroundColor() { return D3DCOLOR_XRGB(0, 0, 0); }

#define OUTDOOR_MAP_FREEZE_CAMERA		SRect(104, 45, 152, 100)
#define INDOOR_MAP_FREEZE_CAMERA		SRect(104, 100, 152, 120)

#endif // !_RESOURCES_H
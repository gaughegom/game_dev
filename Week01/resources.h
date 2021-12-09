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

#define WINDOW_CLASS_NAME			L"Blaster master"
#define WINDOW_TITLE				L"Blaster master"
#define WINDOW_SCREEN_WIDTH			320
#define WINDOW_SCREEN_HEIGHT		280
#define MAX_FRAME_RATE				60

#define BACKGROUND_COLOR			D3DCOLOR_XRGB(0, 0, 0)

#pragma endregion

#pragma region Scence path

#define SCENE2_PATH					 L"database\\scene2.txt"

#pragma endregion

#pragma region Textures

#define SOPHIA_JASON_TEXTURE_PATH	L"textures//player.png"
#define TEXTURE_TRANS_COLOR			D3DCOLOR_XRGB(41, 255, 4)

#pragma endregion

#pragma region Player

#define PLAYER_MOVING_SPEED			0.1f
#define PLAYER_JUMP_FORCE			0.28f
#define GAME_GRAVITY				0.0007f

#define SOPHIA_BASICBULLET_VELOCITY				0.2f

#define	TIME_SUFFERING_AFFECT		300

#pragma endregion

#pragma region Keyboard

#define DIRECTINPUT_VERSION			0x0800
#define KEYBOARD_BUFFER_SIZE		1024
#pragma endregion

#pragma region Tileset

#define TILESET_WIDTH		16
#define TILESET_HEIGHT		16

#pragma endregion

#define PI			atan(1)*4
#define ENEMY_VELOCITY_NORMAL		0.06f
#define ENEMY_ACTIVE_DISTANCE		130

#define	DRAW_COLOR_DEFAULT		D3DCOLOR_ARGB(255, 255, 255, 255)

#endif // !_RESOURCES_H
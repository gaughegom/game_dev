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

#define	QUADTREE_WIDTH				SCREEN_WIDTH * 10
#define QUADTREE_HEIGHT				SCREEN_HEIGHT * 3

#pragma endregion

#pragma region TEXTURES ID

#define TEXTURES_SOPHIA_ID			0
#define TEXTURES_JASON_ID			1
#define TEXTURES_ENEMY_ROBOT_ID		2

#pragma endregion

#pragma region TEXTURES PATH

#define SOPHIA_JASON_TEXTURE_PATH	L"resources//player.png"
#define ENEMY_TEXTURE_PATH			L"resources//enemies.png"
#define TEXTURE_TRANS_COLOR			D3DCOLOR_XRGB(41, 255, 4)

#pragma endregion

#pragma region SPRITE, ANIMATION ID

// sprites
#define SPRITE_SOPHIA_WHEEL_1			0 // sophia 0 -19
#define SPRITE_SOPHIA_WHEEL_2			1
#define SPRITE_SOPHIA_WHEEL_3			2
#define SPRITE_SOPHIA_WHEEL_4			3
#define SPRITE_SOPHIA_BODY				4
#define SPRITE_SOPHIA_CABIN_00			5
#define SPRITE_SOPHIA_CABIN_OPEN		6
#define SPRITE_SOPHIA_CABIN_45			7
#define SPRITE_SOPHIA_GUN_00			8
#define SPRITE_SOPHIA_GUN_45			9
#define SPRITE_SOPHIA_GUN_90			10

#define SPRITE_JASON_LEFT_01			20 // jason 20 - 29
#define SPRITE_JASON_LEFT_02			21
#define SPRITE_JASON_LEFT_03			22
#define SPRITE_JASON_UP_01				23
#define SPRITE_JASON_UP_02				24
#define SPRITE_JASON_UP_03				25
#define SPRITE_JASON_DOWN_01			26
#define SPRITE_JASON_DOWN_02			27
#define SPRITE_JASON_DOWN_03			28

#define SPRITE_ENEMY_ROBOT				50 // enemy from 50

// animations
#define ANIMATION_SOPHIA_LEFT_WHEEL		0
#define ANIMATION_SOPHIA_RIGHT_WHEEL	1

#define ANIMATION_JASON_LEFT			20
#define ANIMATION_JASON_UP				21
#define	ANIMATION_JASON_DOWN			22

#define ANIMATION_ENEMY_ROBOT			50


#pragma endregion

#pragma region PLAYER SETTINGS

#define PLAYER_START_X				100.0f
#define PLAYER_START_Y				50.0f
#define PLAYER_WIDTH				30
#define PLAYER_HEIGHT				32
#define PLAYER_MOVING_SPEED			0.15f
#define PLAYER_GRAVITY				0.01f
#define PLAYER_JUMP_FORCE			0.22f

#pragma endregion

#pragma region SOPHIA STATE

#define SOPHIA_STATE_DIRECTION_STAY			0
#define SOPHIA_STATE_DIRECTION_FORWARD		3
#define SOPHIA_STATE_DIRECTION_BACKWARD		9

#define SOPHIA_STATE_ACTION_IDLE			00
#define SOPHIA_STATE_ACTION_TILE_45			45
#define SOPHIA_STATE_ACTION_UP_90			90

#pragma endregion

#pragma region JASON STATE

#define JASON_STATE_DIRECTION_IDLE			0
#define JASON_STATE_DIRECTION_FORWARD		1
#define JASON_STATE_DIRECTION_BACKWARD		2
#define JASON_STATE_DIRECTION_UPWARD		3
#define JASON_STATE_DIRECTION_DOWNWARD		4

#pragma endregion


#pragma region NPC SETTINGS

#define NPC_START_X					100.0f
#define NPC_START_Y					180.0f
#define NPC_WIDTH					30
#define NPC_HEIGHT					32
#define NPC_MOVING_SPEED			0.2f

#pragma endregion

#pragma region KEYBOARD

#define DIRECTINPUT_VERSION			0x0800
#define KEYBOARD_BUFFER_SIZE		1024

#pragma endregion


#endif // !_RESOURCES_H
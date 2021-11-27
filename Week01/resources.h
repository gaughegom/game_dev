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
#include "debug.h"
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

#pragma region TEXTURES ID

#define TEXTURES_PLAYER_ID			0
#define TEXTURES_ENEMY_ID			1


#pragma endregion

#pragma region TEXTURES PATH

#define SOPHIA_JASON_TEXTURE_PATH	L"resources//player.png"
#define ENEMY_TEXTURE_PATH			L"resources//enemies.png"
#define TEXTURE_TRANS_COLOR			D3DCOLOR_XRGB(41, 255, 4)
#define BACKGOUND_TEXTURE_PATH		L"map//sectionB.png"

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

#define SPRITE_BIG_JASON_LEFT_01			20 // big jason 20 - 29
#define SPRITE_BIG_JASON_LEFT_02			21
#define SPRITE_BIG_JASON_LEFT_03			22
#define SPRITE_BIG_JASON_UP_01				23
#define SPRITE_BIG_JASON_UP_02				24
#define SPRITE_BIG_JASON_UP_03				25
#define SPRITE_BIG_JASON_DOWN_01			26
#define SPRITE_BIG_JASON_DOWN_02			27
#define SPRITE_BIG_JASON_DOWN_03			28

#define SPRITE_SMALL_JASON_WALK_01		30 // small jason
#define SPRITE_SMALL_JASON_WALK_02		31
#define SPRITE_SMALL_JASON_WALK_03		32
#define SPRITE_SMALL_JASON_WALK_04		33

#define SPRITE_ENEMY_ROBOT				49 // enemy from 50

#define SPRITE_ENEMY_DRAP_01			50
#define SPRITE_ENEMY_DRAP_02			51
#define SPRITE_ENEMY_DRAP_03			52
#define SPRITE_ENEMY_DRAP_04			53
#define SPRITE_ENEMY_DRAP_05			54 // reverse
#define SPRITE_ENEMY_DRAP_06			55
#define SPRITE_ENEMY_DRAP_07			56
#define SPRITE_ENEMY_DRAP_08			57

#define SPRITE_ENEMY_EYELET_01			60
#define SPRITE_ENEMY_EYELET_02			61
#define SPRITE_ENEMY_EYELET_03			62
#define SPRITE_ENEMY_EYELET_04			63
#define SPRITE_ENEMY_EYELET_05			64
#define SPRITE_ENEMY_EYELET_06			65
#define SPRITE_ENEMY_EYELET_07			66
#define SPRITE_ENEMY_EYELET_08			67

#define SPRITE_ENEMY_GX680_01			70
#define SPRITE_ENEMY_GX680_02			71
#define SPRITE_ENEMY_GX680_03			72
#define SPRITE_ENEMY_GX680_04			73
#define SPRITE_ENEMY_GX680_05			74
#define SPRITE_ENEMY_GX680_06			75
#define SPRITE_ENEMY_GX680_07			76
#define SPRITE_ENEMY_GX680_08			77

#define SPRITE_ENEMY_STUKA_01			80
#define SPRITE_ENEMY_STUKA_02			81
#define SPRITE_ENEMY_STUKA_03			82
#define	SPRITE_ENEMY_STUKA_04			83
#define SPRITE_ENEMY_STUKA_05			84

#define SPRITE_ENEMY_OFFSIDE_01			90
#define SPRITE_ENEMY_OFFSIDE_02			91
#define SPRITE_ENEMY_OFFSIDE_03			92
#define SPRITE_ENEMY_OFFSIDE_04			93


// animations
#define ANIMATION_SOPHIA_LEFT_WHEEL		0
#define ANIMATION_SOPHIA_RIGHT_WHEEL	1

#define ANIMATION_JASON_LEFT			20
#define ANIMATION_JASON_UP				21
#define	ANIMATION_JASON_DOWN			22

#define ANIMATION_SMALL_JASON_WALK		30
#define ANIMATION_SMALL_JASON_STAY		31

#define ANIMATION_ENEMY_ROBOT			49

#define ANIMATION_ENEMY_DRAP			50
#define ANIMATION_ENEMY_DRAP_REVERSE	51

#define ANIMATION_ENEMY_EYELET			60
#define ANIMATION_ENEMY_EYELET_REVERSE	61

#define ANIMATION_ENEMY_GX680			70

#define ANIMATION_ENEMY_STUKA			80

#define ANIMATION_ENEMY_OFFSIDE			90


#pragma endregion

#pragma region PLAYER SETTINGS

#define PLAYER_START_X				100.0f
#define PLAYER_START_Y				50.0f
#define PLAYER_WIDTH				30
#define PLAYER_HEIGHT				32
#define PLAYER_MOVING_SPEED			0.15f
#define PLAYER_GRAVITY				0.018f
#define PLAYER_JUMP_FORCE			0.22f
#define GAME_GROUND					30

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
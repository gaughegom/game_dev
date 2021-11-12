#pragma once
#ifndef _TEXTURES_H
#define _TEXTUERS_H

#include "resources.h"

using namespace std;

/*
	Manage texture database
*/

class CTextures
{
	static CTextures* __instance;

	unordered_map<int, LPDIRECT3DTEXTURE9> textures;

public:
	CTextures();
	void Add(int id, LPCWSTR filePath, D3DCOLOR transparentColor);
	LPDIRECT3DTEXTURE9 Get(unsigned int i);

	static CTextures* Get_instance();
};

#endif // !_TEXTURES_H



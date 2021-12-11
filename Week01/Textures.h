#pragma once
#ifndef _TEXTURES_H
#define _TEXTUERS_H

#include "resources.h"

/*
	Manage texture database
*/

class CTextures
{
	static CTextures* __instance;

	std::unordered_map<std::string, LPDIRECT3DTEXTURE9> textures;

public:
	CTextures();
	void Add(std::string id, LPCWSTR filePath, D3DCOLOR transparentColor);
	LPDIRECT3DTEXTURE9 Get(std::string id);
	void Clear();

	static CTextures* GetInstance();
};

#endif // !_TEXTURES_H



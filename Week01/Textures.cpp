#include <Windows.h>

#include <d3d9.h>
#include <d3dx9.h>

#include "Game.h"
#include "Textures.h"

CTextures* CTextures::__instance = nullptr;

CTextures::CTextures()
{

}

CTextures* CTextures::GetInstance()
{
	if (__instance == NULL) __instance = new CTextures();
	return __instance;
}

void CTextures::Add(std::string id, LPCWSTR filePath, D3DCOLOR transparentColor)
{
	D3DXIMAGE_INFO info;
	HRESULT result = D3DXGetImageInfoFromFile(filePath, &info);
	if (result != D3D_OK)
	{
		DebugOut(L"[ERROR] GetImageInfoFromFile failed: %s\n", filePath);
		return;
	}

	LPDIRECT3DDEVICE9 d3ddv = CGame::GetInstance()->GetDirect3dDevice();
	LPDIRECT3DTEXTURE9 texture;

	result = D3DXCreateTextureFromFileEx(
		d3ddv,								// Pointer to Direct3D device object
		filePath,							// Path to the image to load
		info.Width,							// Texture width
		info.Height,						// Texture height
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		transparentColor,
		&info,
		NULL,
		&texture);								// Created texture pointer

	if (result != D3D_OK)
	{
		OutputDebugString(L"[ERROR] CreateTextureFromFile failed\n");
		return;
	}
	this->textures.insert(std::make_pair(id, texture));

	DebugOut(L"[INFO] Texture loaded Ok: %s \n", filePath);
}

LPDIRECT3DTEXTURE9 CTextures::Get(std::string id)
{
	return this->textures.at(id);
}

void CTextures::Clear()
{
	for (auto x : this->textures) {
		LPDIRECT3DTEXTURE9 tex = x.second;
		delete tex;
	}
	this->textures.clear();
}

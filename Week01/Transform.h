#pragma once
#ifndef _TRANSFORM_H
#define _TRANSFORM_H

#include <d3dx9.h>

typedef D3DXVECTOR2 Vector2D;
typedef D3DXVECTOR3 Vector3D;

struct SRect
{
	float left, top, right, bottom;
	SRect();
	SRect(float _left, float _top, float _right, float _bottom);
	bool Contain(const Vector2D& point);
	bool Contain(const SRect& rect);
	bool Overlap(const SRect& rect);
	void Empty();
};

Vector2D VectorInfinity();

Vector2D VectorZero();

Vector2D NormalizeVector();

#endif // !_TRANSFORM_H

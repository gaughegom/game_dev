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
	bool IsConstainPoint(const Vector2D& point);
	bool IsConstainRect(const SRect& rect);
	bool IsOverlap(const SRect& rect);
	void SetZero();
};

#endif // !_TRANSFORM_H

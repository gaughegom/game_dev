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
	SRect(float left, float top, float right, float bottom);
	bool Equal(const SRect& rect);
	bool Contain(const Vector2D& point);
	bool Contain(const SRect& rect);
	bool Overlap(const SRect& rect);
	void Empty();

	SRect operator+(const SRect& other) const;
	SRect operator*(const int& value) const;
};

Vector2D VectorInfinity();

Vector2D VectorZero();

Vector2D NormalizeVector();

float PositionsDistance(Vector2D vectorA, Vector2D vectorB);

#endif // !_TRANSFORM_H

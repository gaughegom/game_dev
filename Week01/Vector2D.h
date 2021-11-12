#pragma once
#ifndef _VECTOR2D_H
#define _VECTOR2D_H

#include <d3d9.h>

class CVector2D
{
public :
	float x, y;

	CVector2D() = default;
	CVector2D(float _x, float _y);
	CVector2D operator+(const CVector2D& vec);
	CVector2D& operator+=(const CVector2D& vec);
	CVector2D operator-(const CVector2D& vec);
	CVector2D& operator-=(const CVector2D& vec);
	CVector2D operator*(const CVector2D& vec);
	CVector2D& operator*=(const CVector2D& vec);
	
	CVector2D operator*(const int& _val);
	CVector2D operator*(const DWORD& _val);
};

#endif // !_VECTOR2D_H

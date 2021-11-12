#include "Vector2D.h"

CVector2D::CVector2D(float _x, float _y)
{
	this->x = _x;
	this->y = _y;
}

CVector2D CVector2D::operator+(const CVector2D& _vec)
{
	return CVector2D(this->x + _vec.x, this->y + _vec.y);
}

CVector2D& CVector2D::operator+=(const CVector2D& _vec)
{
	return *this = *this + _vec;
}

CVector2D CVector2D::operator-(const CVector2D& _vec)
{
	return CVector2D(this->x - _vec.x, this->y - _vec.y);
}

CVector2D& CVector2D::operator-=(const CVector2D& _vec)
{
	return *this = *this - _vec;
}

CVector2D CVector2D::operator*(const CVector2D& _vec)
{
	return CVector2D(this->x * _vec.x, this->y * y);
}

CVector2D& CVector2D::operator*=(const CVector2D& _vec)
{
	return *this = *this * _vec;
}

CVector2D CVector2D::operator*(const int& _val)
{
	return CVector2D(this->x * _val, this->y * _val);
}

CVector2D CVector2D::operator*(const DWORD& _val)
{
	return CVector2D(this->x * _val, this->y * _val);
}

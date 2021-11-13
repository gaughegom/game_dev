#include "Vector2D.h"

CVector2D::CVector2D(float newX, float newY)
{
	this->x = newX;
	this->y = newY;
}

CVector2D CVector2D::operator+(const CVector2D& vec)
{
	return CVector2D(this->x + vec.x, this->y + vec.y);
}

CVector2D& CVector2D::operator+=(const CVector2D& vec)
{
	return *this = *this + vec;
}

CVector2D CVector2D::operator-(const CVector2D& vec)
{
	return CVector2D(this->x - vec.x, this->y - vec.y);
}

CVector2D& CVector2D::operator-=(const CVector2D& vec)
{
	return *this = *this - vec;
}

CVector2D CVector2D::operator*(const CVector2D& vec)
{
	return CVector2D(this->x * vec.x, this->y * y);
}

CVector2D& CVector2D::operator*=(const CVector2D& vec)
{
	return *this = *this * vec;
}

CVector2D CVector2D::operator*(const int& val)
{
	return CVector2D(this->x * val, this->y * val);
}

CVector2D CVector2D::operator*(const DWORD& val)
{
	return CVector2D(this->x * val, this->y * val);
}

void CVector2D::Empty()
{
	this->x = this->y = 0;
}

void CVector2D::Set(float newX, float newY)
{
	this->x = newX;
	this->y = newY;
}

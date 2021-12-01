#include "Transform.h"

SRect::SRect()
{
	this->left = this->top = this->right = this->bottom = 0;
}

SRect::SRect(float _left, float _top, float _right, float _bottom)
{
	this->left = _left;
	this->top = _top;
	this->right = _right;
	this->bottom = _bottom;
}

bool SRect::Equal(const SRect& rect)
{
	if (this->left == rect.left && this->top == rect.top
		&& this->right == rect.right && this->bottom == rect.bottom) {
		return true;
	}
	return false;
}

bool SRect::Contain(const Vector2D& point)
{
	return point.x >= this->left && point.x <= this->right
		&& point.y >= this->bottom && point.y <= this->top;
}

bool SRect::Contain(const SRect& rect)
{
	return rect.left >= this->left && rect.right <= this->right
		&& rect.bottom >= this->bottom && rect.top <= this->top;
}

bool SRect::Overlap(const SRect& rect)
{
	if (this->right <= rect.left || this->left >= rect.right) {
		return false;
	}
	if (this->top <= rect.bottom || this->bottom >= rect.top) {
		return false;
	}
	return true;
}

void SRect::Empty()
{
	this->left = this->top = this->right = this->left = 0;
}

Vector2D VectorInfinity()
{
	return Vector2D(999999.0f, 999999.0f);
}

Vector2D VectorZero()
{
	return Vector2D(0.0f, 0.0f);
}

Vector2D NormalizeVector()
{
	return Vector2D(1.0f, 1.0f);
}

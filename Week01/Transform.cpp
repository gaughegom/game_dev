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

bool SRect::IsConstain(const Vector2D& point)
{
	return point.x >= this->left && point.x <= this->right
		&& point.y >= this->bottom && point.y <= this->top;
}

bool SRect::IsConstain(const SRect& rect)
{
	return rect.left >= this->left && rect.right <= this->right
		&& rect.bottom >= this->bottom && rect.top <= this->top;
}

bool SRect::IsOverlap(const SRect& rect)
{
	if (this->right <= rect.left && this->left >= rect.right) {
		return false;
	}
	if (this->top <= rect.bottom && this->bottom >= rect.top) {
		return false;
	}
	return true;
}

void SRect::Empty()
{
	this->left = this->top = this->right = this->left = 0;
}
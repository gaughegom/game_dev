#include "Transform.h"

SRect::SRect()
{
	this->left = this->top = this->right = this->bottom = 0;
}

SRect::SRect(const float& left, const float& top, const float& right, const float& bottom)
	: left(left), top(top), right(right), bottom(bottom) {

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
	return rect.left > this->left && rect.right < this->right
		&& rect.bottom > this->bottom && rect.top < this->top;
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

SRect SRect::operator+(const SRect& other) const
{
	return SRect(
		left + other.left,
		top + other.top,
		right + other.right,
		bottom + other.bottom
	);
}

SRect SRect::operator*(const int& value) const
{
	return SRect(
		this->left * value,
		this->top * value,
		this->right * value,
		this->bottom * value
	);
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

float PositionsDistance(const Vector2D& vectorA, const Vector2D& vectorB)
{
	float result = sqrt(pow(vectorA.x - vectorB.x, 2) + pow(vectorA.y - vectorB.y, 2));
	return result;
}

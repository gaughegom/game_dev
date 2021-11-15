#include "Camera.h"

// init camera width and height
CCamera::CCamera()
{
}

// set camera position
void CCamera::SetPosition(Vector2D posotion)
{
	this->position = position;
}

// set new size of camera
void CCamera::SetSize(int newWidth, int newHeight)
{
	this->width = newWidth;
	this->height = newHeight;
}

void CCamera::Update()
{
	Vector2D targetPosition = target->GetPosition();
	this->position.x = targetPosition.x - this->width / static_cast<float>(2);
	this->position.y = targetPosition.y + this->height / static_cast<float>(2);
}

// get and set field of camera
Vector2D CCamera::GetPosition()
{
	return Vector2D(this->position.x, this->position.y);
}

float CCamera::GetX()
{
	return this->position.x;
}

float CCamera::GetY()
{
	return this->position.y;
}

int CCamera::GetWidth()
{
	return this->width;
}

int CCamera::GetHeight()
{
	return this->height;
}

void CCamera::SetTarget(CGameObject* target)
{
	this->target = target;
}

CGameObject* CCamera::GetTarget()
{
	return this->target;
}

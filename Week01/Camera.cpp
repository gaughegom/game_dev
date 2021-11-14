#include "Camera.h"

// init camera width and height
CCamera::CCamera()
{
}

// set camera position
void CCamera::Set_position(float newX, float newY)
{
	this->position.x = newX;
	this->position.y = newY;
}

// set new size of camera
void CCamera::Set_size(int newWidth, int newHeight)
{
	this->width = newWidth;
	this->height = newHeight;
}

void CCamera::Update()
{
	Vector2D targetPosition = target->Get_position();
	this->position.x = targetPosition.x - this->width / static_cast<float>(2);
	this->position.y = targetPosition.y - this->height / static_cast<float>(2);
}

// get and set field of camera
Vector2D CCamera::Get_position()
{
	return Vector2D(this->position.x, this->position.y);
}

float CCamera::Get_x()
{
	return this->position.x;
}

float CCamera::Get_y()
{
	return this->position.y;
}

int CCamera::Get_width()
{
	return this->width;
}

int CCamera::Get_height()
{
	return this->height;
}

void CCamera::Set_target(CGameObject* target)
{
	this->target = target;
}

CGameObject* CCamera::Get_target()
{
	return this->target;
}

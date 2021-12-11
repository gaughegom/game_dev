#include "Camera.h"
#include "Player.h"

CCamera* CCamera::__instance = nullptr;

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
void CCamera::SetSize(Vector2D size)
{
	this->size = size;
}

void CCamera::Update()
{
	Vector2D targetPosition = target->GetPosition();
	this->position.x = (int)(targetPosition.x - this->size.x / 2);
	this->position.y = (int)(targetPosition.y + this->size.y / 2);

	if (this->position.x <= this->boundary.left)
		this->position.x = this->boundary.left;
	if (this->position.y >= this->boundary.top)
		this->position.y = this->boundary.top;
	if (this->position.x + this->size.x >= this->boundary.right)
		this->position.x = this->boundary.right - this->size.x;
	if (this->position.y - this->size.y <= this->boundary.bottom)
		this->position.y = this->boundary.bottom + size.y;
}

Vector2D CCamera::GetPosition()
{
	return this->position;
}

SRect CCamera::GetBoundingBox()
{
	SRect rect;
	rect.left = this->position.x;
	rect.top = this->position.y;
	rect.right = this->position.x + this->size.x;
	rect.bottom = this->position.y - this->size.y;

	return rect;
}

void CCamera::SetBoundary(SRect boundary)
{
	this->boundary = boundary;
}

void CCamera::SetTarget(CGameObject* target)
{
	this->target = target;
}

CGameObject* CCamera::GetTarget()
{
	return this->target;
}

Vector2D CCamera::TranslateWorldToScreen(Vector2D pos)
{
	Vector3D p = Vector3D(0, 0, 0);

	D3DXMATRIX mat;
	D3DXMatrixIdentity(&mat);

	// Translate
	D3DXMATRIX translate;
	D3DXMatrixTranslation(&translate, (pos.x - position.x), (-pos.y + position.y), 0.0f);

	mat *= translate;

	return Vector2D(mat._41, mat._42);
}

CCamera* CCamera::GetInstance()
{
	if (__instance == nullptr) {
		__instance = new CCamera;
	}
	return __instance;
}

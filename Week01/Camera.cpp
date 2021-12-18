#include "Camera.h"
#include "Player.h"

CCamera* CCamera::__instance = nullptr;

// init g_camera width and height
CCamera::CCamera()
{
}

// set g_camera position
void CCamera::SetPosition(Vector2D posotion)
{
	this->position = position;
}

// set new size of g_camera
void CCamera::SetSize(Vector2D size)
{
	this->size = size;
}

void CCamera::Update()
{
	Vector2D targetPosition = target->GetPosition();
	Vector2D vpPlayer = this->TranslateWorldToScreen(targetPosition);

	if (this->position == VectorInfinity()) {
		this->position.x = (int)(targetPosition.x - (this->size.x / 2));
		this->position.y = (int)(targetPosition.y + (this->size.y / 2));
	}
	else {
		if (vpPlayer.x <= this->freezeBoundary.left)
			this->position.x = (int)(targetPosition.x - this->freezeBoundary.left);
		if (vpPlayer.x >= this->freezeBoundary.right)
			this->position.x = (int)(targetPosition.x - this->freezeBoundary.right);
		if (vpPlayer.y <= this->freezeBoundary.top)
			this->position.y = (int)(targetPosition.y + this->freezeBoundary.top);
		if (vpPlayer.y >= this->freezeBoundary.bottom)
			this->position.y = (int)(targetPosition.y + this->freezeBoundary.bottom);
	}

	if (boundless == false) {
		if (this->position.x <= this->boundary.left)
			this->position.x = this->boundary.left;
		if (this->position.y >= this->boundary.top)
			this->position.y = this->boundary.top;
		if (this->position.x + this->size.x >= this->boundary.right)
			this->position.x = this->boundary.right - this->size.x;
		if (this->position.y - this->size.y <= this->boundary.bottom)
			this->position.y = this->boundary.bottom + this->size.y;
	}
}

Vector2D CCamera::GetPosition()
{
	return this->position;
}

SRect CCamera::GetBoundingBox()
{
	Vector2D nextPosition = this->position + target->GetVelocity() * CGame::GetDeltaTime();

	SRect boundingRect;
	boundingRect.left = min(position.x, nextPosition.x);
	boundingRect.top = max(position.y, nextPosition.y);
	boundingRect.right = max(position.x + size.x, nextPosition.x + size.x);
	boundingRect.bottom = min(position.y - size.y, nextPosition.y - size.y);

	return boundingRect;
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

	D3DXMATRIX translate;
	D3DXMatrixTranslation(&translate, (pos.x - position.x), (-pos.y + position.y), 0.0f);

	mat *= translate;

	return Vector2D((int)mat._41, (int)mat._42);
}

CCamera* CCamera::GetInstance()
{
	if (__instance == nullptr) {
		__instance = new CCamera;
	}
	return __instance;
}

#include "QuadTree.h"

CQuadTree::CQuadTree(const int level, const SRect& rect) 
{
	this->level = level;
	this->rect = rect;
}

void CQuadTree::DivideScreen()
{
	float posX = this->rect.left;
	float posY = this->rect.bottom;

	float camWidth = this->rect.right - this->rect.left;
	float camHeight = this->rect.top - this->rect.bottom;

	float halfWidth = camWidth / 2;
	float halfHeight = camHeight / 2;

	SRect s_left_bot = SRect(posX, posY + halfHeight, posX + halfWidth, posY);
	SRect s_left_top = SRect(posX, posY + camHeight, posX + halfWidth, posY + halfHeight);
	SRect s_right_bot = SRect(posX + halfWidth, posY + halfHeight, posX + camWidth, posY);
	SRect s_right_top = SRect(posX + halfWidth, posY + camHeight, posX + camWidth, posY + halfHeight);

	pChild[0] = std::make_unique<CQuadTree>(this->level + 1, s_left_bot);
	pChild[1] = std::make_unique<CQuadTree>(this->level + 1, s_right_bot);
	pChild[2] = std::make_unique<CQuadTree>(this->level + 1, s_right_top);
	pChild[3] = std::make_unique<CQuadTree>(this->level + 1, s_left_top);
}

void CQuadTree::MappingObjectRect(CGameObject* object)
{
	if (this->pChild[0].get() != nullptr) {
		AddObjectToRect(object);

		return;
	}

	this->pObject.emplace_back(object);
	if (this->pObject.size() >= 1 && ((rect.right - rect.left)/2 >= SCREEN_WIDTH/2)) {
		DivideScreen();
		for (auto obj : this->pObject) {
			/*if (this->pChild[0].get()->IsConstainObject(obj)) {
				this->pChild[0].get()->MappingObjectRect(obj);
			}
			else if (this->pChild[1].get()->IsConstainObject(obj)) {
				this->pChild[1].get()->MappingObjectRect(obj);
			}
			else if (this->pChild[2].get()->IsConstainObject(obj)) {
				this->pChild[2].get()->MappingObjectRect(obj);
			}
			else if (this->pChild[3].get()->IsConstainObject(obj)) {
				this->pChild[3].get()->MappingObjectRect(obj);
			}*/
			AddObjectToRect(object);
		}
		this->pObject.clear();
		this->pObject.shrink_to_fit();
	}
}

void CQuadTree::AddObjectToRect(CGameObject* object)
{
	if (this->pChild[0].get()->IsConstainObject(object)) {
		this->pChild[0].get()->MappingObjectRect(object);
	}
	else if (this->pChild[1].get()->IsConstainObject(object)) {
		this->pChild[1].get()->MappingObjectRect(object);
	}
	else if (this->pChild[2].get()->IsConstainObject(object)) {
		this->pChild[2].get()->MappingObjectRect(object);
	}
	else if (this->pChild[3].get()->IsConstainObject(object)) {
		this->pChild[3].get()->MappingObjectRect(object);
	}
}

bool CQuadTree::IsConstainObject(CGameObject* object)
{
	Vector2D objectPos = object->GetPosition();
	return this->rect.IsConstain(objectPos);
}

void CQuadTree::Update(std::vector<CGameObject*> objects)
{
	this->pObject.clear();

	this->pChild[0] = nullptr;
	this->pChild[1] = nullptr;
	this->pChild[2] = nullptr;
	this->pChild[3] = nullptr;

	for (auto& object : objects) {
		this->MappingObjectRect(object);
	}
}

void CQuadTree::ContainerizeObject(std::vector<CGameObject*>& container, const SRect& rect)
{
	if (this->pChild[0].get() != nullptr) {
		if (this->pChild[0]->rect.IsOverlap(rect)) {
			this->pChild[0]->ContainerizeObject(container, rect);
		}
		if (this->pChild[1]->rect.IsOverlap(rect)) {
			this->pChild[1]->ContainerizeObject(container, rect);
		}
		if (this->pChild[2]->rect.IsOverlap(rect)) {
			this->pChild[2]->ContainerizeObject(container, rect);
		}
		if (this->pChild[3]->rect.IsOverlap(rect)) {
			this->pChild[3]->ContainerizeObject(container, rect);
		}

		return;
	}

	for (auto& object : this->pObject) {
		container.emplace_back(object);
	}
}

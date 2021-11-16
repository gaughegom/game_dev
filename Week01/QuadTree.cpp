#include "QuadTree.h"

CQuadTree::CQuadTree(const int level, const SRect& rect) 
	: level(level), rect(rect), pChild {nullptr, nullptr, nullptr, nullptr}
{
}

void CQuadTree::DevideScreen()
{
	float posX = this->rect.left;
	float posY = this->rect.bottom;

	float camWidth = this->rect.right - this->rect.left;
	float camHeight = this->rect.top - this->rect.bottom;

	SRect s_left_bot = SRect(posX, posY + camHeight / 2, posX + camWidth / 2, posY);
	SRect s_left_top = SRect(posX, posY + camHeight, posX + camWidth / 2, posY);
	SRect s_right_bot = SRect(posX + camWidth / 2, posY, posX + camWidth, posY);
	SRect s_right_top = SRect(posX + camWidth / 2, posY + camHeight, posX + camWidth, posY + camHeight / 2);

	pChild[0] = std::make_unique<CQuadTree>(this->level + 1, s_left_bot);
	pChild[1] = std::make_unique<CQuadTree>(this->level + 1, s_right_bot);
	pChild[2] = std::make_unique<CQuadTree>(this->level + 1, s_right_top);
	pChild[3] = std::make_unique<CQuadTree>(this->level + 1, s_left_top);
}

void CQuadTree::AddObject(CGameObject* object)
{
	if (pChild[0] != nullptr) {
		if (pChild[0]->IsConstainObject(object)) {
			pChild[0]->AddObject(object);
		}
		else if (pChild[1]->IsConstainObject(object)) {
			pChild[1]->AddObject(object);
		}
		else if (pChild[2]->IsConstainObject(object)) {
			pChild[2]->AddObject(object);
		}
		else if (pChild[3]->IsConstainObject(object)) {
			pChild[3]->AddObject(object);
		}

		return;
	}

	pObject.emplace_back(object);
	if (pObject.size() >= 1 && ((rect.right - rect.left)/2 >= SCREEN_WIDTH/2)) {
		DevideScreen();
		for (auto obj : this->pObject) {
			if (pChild[0]->IsConstainObject(obj)) {
				pChild[0]->AddObject(obj);
			}
			else if (pChild[1]->IsConstainObject(obj)) {
				pChild[1]->AddObject(obj);
			}
			else if (pChild[2]->IsConstainObject(obj)) {
				pChild[2]->AddObject(obj);
			}
			else if (pChild[3]->IsConstainObject(obj)) {
				pChild[3]->AddObject(obj);
			}
		}
		pObject.clear();
		pObject.shrink_to_fit();
	}
}

bool CQuadTree::IsConstainObject(CGameObject* object)
{
	Vector2D objectPos = object->GetPosition();
	return rect.IsConstainPoint(objectPos);
}

void CQuadTree::Update(std::vector<CGameObject*> objects)
{
	this->pObject.clear();
	this->pObject.shrink_to_fit();

	this->pChild[0] = nullptr;
	this->pChild[1] = nullptr;
	this->pChild[2] = nullptr;
	this->pChild[3] = nullptr;

	for (auto& object : objects) {
		this->AddObject(object);
	}
}

void CQuadTree::BringBack(std::vector<CGameObject*>& container, const SRect& rect)
{
	if (pChild[0] != nullptr) {
		if (pChild[0]->rect.IsOverlap(rect)) {
			pChild[0]->BringBack(container, rect);
		}
		if (pChild[1]->rect.IsOverlap(rect)) {
			pChild[1]->BringBack(container, rect);
		}
		if (pChild[2]->rect.IsOverlap(rect)) {
			pChild[2]->BringBack(container, rect);
		}
		if (pChild[3]->rect.IsOverlap(rect)) {
			pChild[3]->BringBack(container, rect);
		}

		return;
	}

	for (auto& object : this->pObject) {
		container.emplace_back(object);
	}
}

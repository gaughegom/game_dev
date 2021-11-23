#pragma once
#ifndef _QUADTREE_H
#define _QUADTREE_H

#include <vector>
#include <memory>
#include <array>
#include "Transform.h"
#include "GameObject.h"

class CQuadTree
{
private:
	int level;
	SRect rect;
	std::unique_ptr<CQuadTree> pChild[4];
	std::vector<CGameObject*> pObject;

public:
	CQuadTree(const int level, const SRect& rect);
	void DivideScreen();
	void MappingObjectRect(CGameObject* object);
	void AddObjectToRect(CGameObject* object);
	bool IsConstainObject(CGameObject* object);

	void Update(std::vector<CGameObject*> objects);
	void ContainerizeObject(std::vector<CGameObject*>& container, const SRect& rect);

	bool HaveObject(CGameObject* object);
	CQuadTree* GetObjectNode(CGameObject* object);

	SRect GetRect() { return this->rect; }
};

#endif // !_QUADTREE_H

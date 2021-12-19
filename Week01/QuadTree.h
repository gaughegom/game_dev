#pragma once
#ifndef _QUADTREE_H
#define _QUADTREE_H

#include <vector>
#include <memory>
#include <array>
#include "GameObject.h"
#include "Transform.h"

constexpr auto MaxNodeEntities = 10;
constexpr auto MaxNodeLevel = 5;

class CQuadTree {
private:
	int level;
	SRect rect;
	std::unique_ptr<CQuadTree> nodes[4];
	std::vector<LPGAMEOBJECT> entities;

public:
	CQuadTree(const int level, SRect rect);

	bool HasChildren();
	bool Overlap(LPGAMEOBJECT& entity);
	
	void Insert(LPGAMEOBJECT entity);
	void SplitArea();
	void Retrieve(std::vector<LPGAMEOBJECT>& container, const SRect& targetRect);
	void Update(std::vector<LPGAMEOBJECT>& updateEntities);
	
	void RemoveEntityFromLeafNodes(LPGAMEOBJECT entity);
	void EmptyNodes();

	SRect GetBoundingBox() { return this->rect; }

	~CQuadTree();
};

#endif // !_QUADTREE_H

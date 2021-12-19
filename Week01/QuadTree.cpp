#include "QuadTree.h"

CQuadTree::CQuadTree(const int level, SRect rect)
{
	float w = rect.right - rect.left;
	float h = rect.top - rect.right;
	float diff = abs(w - h);
	if (w < h) {
		rect.right += diff;
	}
	else {
		h += diff;
	}

	this->level = level;
	this->rect = rect;
	this->EmptyNodes();


	this->entities.reserve(MaxNodeEntities);
}

bool CQuadTree::HasChildren()
{
	return this->nodes[0].get() != nullptr;
}

bool CQuadTree::Overlap(LPGAMEOBJECT& entity)
{
	bool result = this->rect.Overlap(entity->GetColliders().at(0)->GetBoundingBox());
	return result;
}

void CQuadTree::Insert(LPGAMEOBJECT entity)
{
	if (this->HasChildren()) {
		if (this->nodes[0].get()->Overlap(entity)) {
			this->nodes[0].get()->Insert(entity);
		}
		if (this->nodes[1].get()->Overlap(entity)) {
			this->nodes[1].get()->Insert(entity);
		}
		if (this->nodes[2].get()->Overlap(entity)) {
			this->nodes[2].get()->Insert(entity);
		}
		if (this->nodes[3].get()->Overlap(entity)) {
			this->nodes[3].get()->Insert(entity);
		}

		return;
	}

	this->entities.emplace_back(entity);
	entity->AddSelfNodeQt(this);
	entity->SetSelfIndexInNodeQt(this->entities.size() - 1);

	if (this->entities.size() > MaxNodeEntities && this->level < MaxNodeLevel) {
		if (!this->HasChildren()) {
			this->SplitArea();
		}
		entity->ClearSelfNodesQt();
		for (auto& object : this->entities) {
			if (this->HasChildren()) {
				if (this->nodes[0].get()->Overlap(object)) {
					this->nodes[0].get()->Insert(object);
				}
				if (this->nodes[1].get()->Overlap(object)) {
					this->nodes[1].get()->Insert(object);
				}
				if (this->nodes[2].get()->Overlap(object)) {
					this->nodes[2].get()->Insert(object);
				}
				if (this->nodes[3].get()->Overlap(object)) {
					this->nodes[3].get()->Insert(object);
				}
			}
		}

		// remove all entities in this node
		this->entities.clear();
		this->entities.shrink_to_fit();
	}
}

void CQuadTree::SplitArea()
{
	// get origin xy
	float ox = this->rect.left;
	float oy = this->rect.bottom;
	// get width, height of area
	float areaWidth = this->rect.right - this->rect.left;
	float areaHeight = this->rect.top - this->rect.bottom;

	float halfWidth = areaWidth / 2;
	float halfHeight = areaHeight / 2;

	// 0: left bot, 1: left top, 2: right top, 3: right bot
	SRect area_lb = SRect(ox, oy + halfHeight, ox + halfWidth, oy);
	SRect area_lt = SRect(ox, oy + areaHeight, ox + halfWidth, oy + halfHeight);
	SRect area_rb = SRect(ox + halfWidth, oy + halfHeight, ox + areaWidth, oy);
	SRect area_rt = SRect(ox + halfWidth, oy + areaHeight, ox + areaWidth, oy + halfHeight);

	this->nodes[0] = std::make_unique<CQuadTree>(this->level + 1, area_lb);
	this->nodes[1] = std::make_unique<CQuadTree>(this->level + 1, area_lt);
	this->nodes[2] = std::make_unique<CQuadTree>(this->level + 1, area_rt);
	this->nodes[3] = std::make_unique<CQuadTree>(this->level + 1, area_rb);
}

void CQuadTree::Retrieve(std::vector<LPGAMEOBJECT>& container, const SRect& targetRect)
{
	if (this->HasChildren()) {
		if (this->nodes[0].get()->rect.Overlap(targetRect)) {
			this->nodes[0].get()->Retrieve(container, targetRect);
		}
		if (this->nodes[1].get()->rect.Overlap(targetRect)) {
			this->nodes[1].get()->Retrieve(container, targetRect);
		}
		if (this->nodes[2].get()->rect.Overlap(targetRect)) {
			this->nodes[2].get()->Retrieve(container, targetRect);
		}
		if (this->nodes[3].get()->rect.Overlap(targetRect)) {
			this->nodes[3].get()->Retrieve(container, targetRect);
		}
	}

	for (const auto& obj : this->entities) {
		if (!obj->IsRendering()) {
			container.emplace_back(obj);
			obj->SetRendering(true);
		}
	}
}

void CQuadTree::Update(std::vector<LPGAMEOBJECT>& updateEntities)
{
	for (LPGAMEOBJECT& entity : updateEntities) {
		entity->SetRendering(false);

		if (entity->IsLive() == false) continue;
		if (entity->IsActive() == false) continue;

		for (auto colliders : entity->GetColliders()) {
			if (colliders->IsDynamic() == true) {

				std::vector<CQuadTree*> entityNodes = entity->GetSelfNodesQt();

				for (auto entityNode : entityNodes) {
					if (!entityNode->rect.Overlap(entity->GetColliders().at(0)->GetBoundingBox())) {
						entityNode->entities.erase(
							std::remove(entityNode->entities.begin(), entityNode->entities.end(), entity), entityNode->entities.end());
						entity->ClearSelfNodesQt();
						Insert(entity);
					}
				}
			}
		}
	}
}

void CQuadTree::RemoveEntityFromLeafNodes(LPGAMEOBJECT entity) {
	std::vector<CQuadTree*> entityNodes = entity->GetSelfNodesQt();

	for (auto entityNode : entityNodes) {
		entityNode->entities.erase(std::remove(entityNode->entities.begin(), entityNode->entities.end(), entity), entityNode->entities.end());
	}
	entity->ClearSelfNodesQt();
}

void CQuadTree::EmptyNodes() {
	this->nodes[0] = nullptr;
	this->nodes[1] = nullptr;
	this->nodes[2] = nullptr;
	this->nodes[3] = nullptr;
}

CQuadTree::~CQuadTree()
{
	this->entities.clear();
	this->entities.shrink_to_fit();
	this->EmptyNodes();
}
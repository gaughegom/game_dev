#include "Scene.h"
#include "Textures.h"
#include "Sprites.h"

#include "Brick.h"
#include "ThornyBrick.h"
#include "EnemyBallot.h"
#include "EnemyBallcarry.h"
#include "EnemyDrap.h"
#include "EnemyEyelet.h"
#include "EnemyGX-680.h"
#include "EnemyGX-680S.h"
#include "EnemyInterrupt.h"
#include "EnemyStuka.h"
#include "Player.h"
#include "Gate.h"
#include "Mortar.h"

constexpr auto MaxFileLine = 2048;

#pragma region Parse section

void CScene::__ParseSection_MAP__(std::string line)
{
	std::vector<std::string> tokens = SplitLine(line);
	if (tokens.size() < 2)
		return;

	//  fetch from file
	std::string sceneMapPath = tokens[0];
	float sceneWidth = atoi(tokens[1].c_str()) * TilesetWidth;
	float sceneHeight = atoi(tokens[2].c_str()) * TilesetHeight;
	std::string sceneMapType = tokens[3].c_str();

	// set mapBoundary
	this->mapBoundary = SRect(0, sceneHeight, sceneWidth, 0);
	std::string texMapId = sceneMapPath;
	std::string sprMapId = sceneMapPath;

	if (sceneMapType == "outdoor") {
		this->mapType = SceneMapType::OUTDOOR;
	}
	else if (sceneMapType == "indoor") {
		this->mapType = SceneMapType::INDOOR;
	}

	// add to textures, sprites
	CTextures::GetInstance()->Add(texMapId, ToWSTR(sceneMapPath).c_str(), D3DCOLOR_XRGB(0, 0, 0));
	LPDIRECT3DTEXTURE9 texMap = CTextures::GetInstance()->Get(texMapId);
	CSprites::GetInstance()->Add(sprMapId, 0, 0, sceneWidth, sceneHeight, texMap);

	this->map = CSprites::GetInstance()->Get(sprMapId);
}

void CScene::__ParseSection_FOREMAP__(std::string line)
{
	std::vector<std::string> tokens = SplitLine(line);
	if (tokens.size() < 3)
		return;

	std::string foreMapPath = tokens[0];
	float foreMapWidth = atoi(tokens[1].c_str()) * TilesetWidth;
	float foreMapHeight = atoi(tokens[2].c_str()) * TilesetHeight;

	std::string texForeMapId = foreMapPath;
	std::string sprForeMapId = foreMapPath;

	// add to textures, sprites
	CTextures::GetInstance()->Add(texForeMapId, ToWSTR(foreMapPath).c_str(), D3DCOLOR_XRGB(0, 0, 0));
	LPDIRECT3DTEXTURE9 texForeMap = CTextures::GetInstance()->Get(texForeMapId);
	CSprites::GetInstance()->Add(sprForeMapId, 0, 0, foreMapWidth, foreMapHeight, texForeMap);

	this->foreMap = CSprites::GetInstance()->Get(sprForeMapId);
}

void CScene::__ParseSection_PLATFORMS__(std::string line)
{
	std::vector<std::string> tokens = SplitLine(line);
	if (tokens.size() < 4)
		return;

	float x = atoi(tokens[0].c_str()) * TilesetWidth;
	float y = (atoi(tokens[1].c_str()) + 1) * TilesetHeight;
	float width = atoi(tokens[2].c_str()) * TilesetWidth;
	float height = atoi(tokens[3].c_str()) * TilesetHeight;
	std::string type = tokens[4];

	LPGAMEOBJECT platformObject = nullptr;
	if (type == "brick") platformObject = new CBrick(Vector2D(width, height));
	else if (type == "thorny") platformObject = new CThornyBrick(Vector2D(width, height));
	else if (type == "mortar") platformObject = new CMortar(Vector2D(width, height));
	else {
		DebugOut(L"[WARN] undefined platform object %s\n", type);
		return;
	}


	platformObject->SetPosition(Vector2D(x + width / 2, this->mapBoundary.top - y + height / 2));
	this->sceneObjects.push_back(platformObject);
}

void CScene::__ParseSection_OBJECTS__(std::string line)
{
	std::vector<std::string> tokens = SplitLine(line);
	if (tokens.size() < 3)
		return;

	LPGAMEOBJECT object = nullptr;
	std::string type = tokens[0];

	if (type == "eyelet") object = new CEnemyEyelet;
	else if (type == "ballot") object = new CEnemyBallot;
	else if (type == "stuka") object = new CEnemyStuka;
	else if (type == "interrupt") object = new CEnemyInterrupt;
	else if (type == "ballcarry") object = new CEnemyBallcarry;
	else if (type == "gx680") object = new CEnemyGX680;
	else if (type == "gx680s") object = new CEnemyGX680S;
	else if (type == "drap") object = new CEnemyDrap;
	else {
		DebugOut(L"[ERROR] Unknowed object type: %s\n", type); // catch undefined object
		return;
	}

	int nx = atoi(tokens[1].c_str());
	float x = atoi(tokens[2].c_str());
	float y = atoi(tokens[3].c_str());
	float width = atoi(tokens[4].c_str());
	float height = atoi(tokens[5].c_str());
	object->SetPosition(Vector2D(x + width / 2, this->mapBoundary.top - y + height / 2));
	object->SetNx(nx);

	this->sceneObjects.push_back(object);
}

void CScene::__ParseSection_PLAYERS__(std::string line)
{
	std::vector<std::string> tokens = SplitLine(line);
	if (tokens.size() < 1)
		return;
	
	std::string name = tokens[0];
	if (name == "sophia") {
		this->sceneObjects.push_back(CPlayer::GetInstance()->GetSophia());
	}
	else if (name == "jason") {
		this->sceneObjects.push_back(CPlayer::GetInstance()->GetJason());
	}
}

void CScene::__ParseSection_GATES__(std::string line)
{
	std::vector<std::string> tokens = SplitLine(line);
	if (tokens.size() < 5)
		return;

	std::string way = tokens[0];
	float x = atoi(tokens[1].c_str()) * TilesetWidth;
	float y = (atoi(tokens[2].c_str()) + 1) * TilesetHeight;
	float width = atoi(tokens[3].c_str()) * TilesetWidth;
	float height = atoi(tokens[4].c_str()) * TilesetHeight;
	int nextScene = atoi(tokens[5].c_str());

	CGate* gate = new CGate(Vector2D(width, height), nextScene);

	gate->SetPosition(Vector2D(x + width / 2, this->mapBoundary.top - y + height / 2));
	this->sceneObjects.push_back(gate);
	this->gates.push_back(gate);
}

#pragma endregion

CScene::CScene(LPCWSTR filePath)
{
	this->filePath = filePath;
}

void CScene::LoadScene()
{
	DebugOut(L"[INFO] Start parsing scene %s\n", this->filePath);

	if (this->filePath == nullptr) {
		DebugOut(L"[ERROR] Filepath is nullptr\n");
		return;
	}

	std::ifstream fs;
	fs.open(this->filePath);

	SceneSection section = SceneSection::SCENE_SECTION_UNKNOW;
	char str[MaxFileLine];

	while (fs.getline(str, MaxFileLine))
	{
		std::string line(str);

		// set section
		if (line[0] == '#') continue; // skip comment line
		if (line == "[MAP]") {
			section = SceneSection::SCENE_SECTION_MAP;
			continue;
		}
		if (line == "[FOREMAP]") {
			section = SceneSection::SCENE_SECTION_FOREMAP;
			continue;
		}
		if (line == "[PLATFORMS]") {
			section = SceneSection::SCENE_SECTION_PLATFORMS;
			continue;
		}
		if (line == "[OBJECTS]") {
			section = SceneSection::SCENE_SECTION_OBJECTS;
			continue;
		}
		if (line == "[PLAYER]") {
			section = SceneSection::SCENE_SECTION_PLAYERS;
			continue;
		}
		if (line == "[GATES]") {
			section = SceneSection::SCENE_SECTION_GATES;
			continue;
		}

		switch (section)
		{
		case SceneSection::SCENE_SECTION_UNKNOW:
			break;
		case SceneSection::SCENE_SECTION_MAP:
			this->__ParseSection_MAP__(line);
			break;
		case SceneSection::SCENE_SECTION_FOREMAP:
			this->__ParseSection_FOREMAP__(line);
			break;
		case SceneSection::SCENE_SECTION_PLATFORMS:
			this->__ParseSection_PLATFORMS__(line);
			break;
		case SceneSection::SCENE_SECTION_OBJECTS:
			this->__ParseSection_OBJECTS__(line);
			break;
		case SceneSection::SCENE_SECTION_PLAYERS:
			this->__ParseSection_PLAYERS__(line);
			break;
		case SceneSection::SCENE_SECTION_GATES:
			this->__ParseSection_GATES__(line);
			break;
		default:
			break;
		}
	}

	fs.close();
	DebugOut(L"[INFO] Parse section scene %s done\n", this->filePath);
}

void CScene::UnloadScene()
{
}

Vector2D CScene::GetPositionOfGate(int id)
{
	for (auto gate : this->gates) {
		if (gate->GetNextScene() == id)
			return gate->GetPosition();
	}
	return VectorZero();
}

#include "Scene.h"
#include "Textures.h"
#include "Sprites.h"

#include "Brick.h"
#include "EnemyBallot.h"
#include "EnemyEyelet.h"
#include "EnemyStuka.h"
#include "Player.h"

#define MAX_FILE_LINE		2048

#pragma region Parse section

void CScene::__ParseSection_MAP__(std::string line)
{
	std::vector<std::string> tokens = SplitLine(line);
	if (tokens.size() < 2)
		return;

	//  fetch from file
	std::string sceneMapPath = tokens[0].c_str();
	float sceneWidth = atoi(tokens[1].c_str()) * TILESET_WIDTH;
	float sceneHeight = atoi(tokens[2].c_str()) * TILESET_HEIGHT;

	// set mapBoundary
	this->mapBoundary = SRect(0, sceneHeight, sceneWidth, 0);
	std::string texMapId = sceneMapPath;
	std::string sprMapId = sceneMapPath;

	// add to textures, sprites
	CTextures::GetInstance()->Add(texMapId, ToWSTR(sceneMapPath).c_str(), D3DCOLOR_XRGB(0, 0, 0));
	LPDIRECT3DTEXTURE9 texMap = CTextures::GetInstance()->Get(texMapId);
	CSprites::GetInstance()->Add(sprMapId, 0, 0, sceneWidth, sceneHeight, texMap);

	this->map = CSprites::GetInstance()->Get(sprMapId);
}

void CScene::__ParseSection_PLATFORMS__(std::string line)
{
	std::vector<std::string> tokens = SplitLine(line);
	if (tokens.size() < 4)
		return;

	float x = atoi(tokens[0].c_str()) * TILESET_WIDTH;
	float y = (atoi(tokens[1].c_str()) + 1) * TILESET_HEIGHT;
	float width = atoi(tokens[2].c_str()) * TILESET_WIDTH;
	float height = atoi(tokens[3].c_str()) * TILESET_HEIGHT;
	LPGAMEOBJECT platformObject = new CBrick(Vector2D(width, height));
	platformObject->SetPosition(Vector2D(x + width / 2, this->mapBoundary.top - y + height / 2));
	this->sceneObjects.push_back(platformObject);
}

void CScene::__ParseSection_OBJECTS__(std::string line)
{
	std::vector<std::string> tokens = SplitLine(line);
	if (tokens.size() < 3)
		return;

	LPGAMEOBJECT object = nullptr;
	std::string type = tokens[0].c_str();

	if (type == "eyelet") object = new CEnemyEyelet;
	else if (type == "ballot") object = new CEnemyBallot;
	else if (type == "stuka") object = new CEnemyStuka;
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
	
	std::string name = tokens[0].c_str();
	if (name == "sophia") {
		this->players.push_back(CPlayer::GetInstance()->GetSophia());
	}
	else if (name == "jason") {
		this->players.push_back(CPlayer::GetInstance()->GetJason());
	}
}

#pragma endregion

CScene::CScene(int id, LPCWSTR filePath)
{
	this->id = id;
	this->filePath = filePath;
}

void CScene::LoadScene()
{
	DebugOut(L"[INFO] Start loading scene %s\n", this->filePath);

	if (this->filePath == nullptr) {
		DebugOut(L"[ERROR] Filepath is nullptr\n");
		return;
	}

	std::ifstream fs;
	fs.open(this->filePath);

	SceneSection section = SceneSection::SCENE_SECTION_UNKNOW;
	char str[MAX_FILE_LINE];

	while (fs.getline(str, MAX_FILE_LINE))
	{
		std::string line(str);

		// set section
		if (line[0] == '#') continue; // skip comment line
		if (line == "[MAP]") {
			section = SceneSection::SCENE_SECTION_MAP;
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

		switch (section)
		{
		case SceneSection::SCENE_SECTION_UNKNOW:
			break;
		case SceneSection::SCENE_SECTION_MAP:
			this->__ParseSection_MAP__(line);
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
		default:
			break;
		}
	}

	fs.close();
	DebugOut(L"[INFO] Load scene %s done\n", this->filePath);
}

void CScene::UnloadScene()
{
}

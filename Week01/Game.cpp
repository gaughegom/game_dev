#include "Game.h"
#include "Animations.h"
#include "Camera.h"
#include "KeyEventHandler.h"
#include "InputHandler.h"
#include "QuadTree.h"
#include "Textures.h"

#include "Sophia.h"
#include "Jason.h"
#include "Brick.h"
#include "EnemyDrap.h"
#include "EnemyEyelet.h"
#include "EnemyGX-680.h"
#include "EnemyOffside.h"
#include "EnemyStuka.h"
#include "EnemyBallot.h"
#include "SophiaBullet.h"

#define MAX_SCENE_LINE	2048

CSophia* sophia;
CJason* jason;
CCamera* camera = CCamera::GetInstance();
CQuadTree* quadtree;

std::vector<CGameObject*> worldObjects;
std::vector<CGameObject*> renderedObjects;

CTextures* g_textures = CTextures::GetInstance();
CSprites* g_sprites = CSprites::GetInstance();
CAnimations* g_animations = CAnimations::GetInstance();
CInputHandler* g_inputHandler = CInputHandler::GetInstance();

CGame* CGame::__instance = nullptr;
DWORD CGame::dt = 0;

#pragma region Keyboard

class CKeyHander : public CKeyEventHandler
{
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	virtual void IsKeyDown(int keyCode);
};

void CKeyHander::OnKeyDown(int keyCode)
{
	
}

void CKeyHander::IsKeyDown(int keyCode) {

}

void CKeyHander::OnKeyUp(int keyCode)
{
}

void CKeyHander::KeyState(BYTE* states)
{
	// switch selected object by key
	// empty
}

#pragma endregion

#pragma region DirectX

void CGame::InitDirectX(HWND hWnd)
{
	LPDIRECT3D9 d3d = Direct3DCreate9(D3D_SDK_VERSION);

	this->hWnd = hWnd;

	D3DPRESENT_PARAMETERS d3dpp;

	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferCount = 1;

	RECT r;
	GetClientRect(hWnd, &r);	// retrieve Window width & height 

	d3dpp.BackBufferHeight = r.bottom + 1;
	d3dpp.BackBufferWidth = r.right + 1;

	this->camWidth = d3dpp.BackBufferWidth;
	this->camHeight = d3dpp.BackBufferHeight;

	d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddv);

	if (d3ddv == NULL)
	{
		OutputDebugString(L"[ERROR] CreateDevice failed\n");
		return;
	}

	d3ddv->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backBuffer);

	// Initialize sprite helper from Direct3DX helper library
	D3DXCreateSprite(d3ddv, &spriteHandler);

	DebugOut(L"[INFO] InitGame done;\n");
	DebugOut(L"[INFO] Screen: %d, %d\n", this->camWidth, this->camHeight);
}

/*
	Utility function to wrap LPD3DXSPRITE::Draw
*/
void CGame::Draw(Vector2D position, int nx, LPDIRECT3DTEXTURE9 texture, int left, int top, int right, int bottom, D3DCOLOR color)
{

	Vector2D cameraPos = camera->GetPosition();

	Vector3D p(0, 0, 0);
	RECT r;
	r.left = left;
	r.top = top;
	r.right = right;
	r.bottom = bottom;

	Vector3D center = Vector3D((right - left) / 2, (bottom - top) / 2, 0.0f);

	D3DXMATRIX matrix;
	D3DXMatrixIdentity(&matrix);

	// flip X
	D3DXMATRIX dmFlipX;
	D3DXMatrixScaling(&dmFlipX, nx, 1.0f, 1.0f);

	// translate 
	D3DXMATRIX dmTranslation;
	D3DXMatrixTranslation(&dmTranslation, (position.x - cameraPos.x), (-position.y + cameraPos.y), 0.0f);

	matrix *= dmFlipX;
	matrix *= dmTranslation;

	spriteHandler->SetTransform(&matrix);

	spriteHandler->Draw(texture, &r, &center, &p, color);
}

#pragma endregion

#pragma region Game process

void CGame::InitGame(HWND hWnd)
{
	this->InitDirectX(hWnd);

	// TODO: This is only for test
	#pragma region Texture bbox

	g_textures->Add("bbox", L"textures//bbox.png", D3DCOLOR_XRGB(0, 0, 0));

	#pragma endregion

	this->LoadResource();

	#pragma region Player instance
	
	auto playerInstance = CPlayer::GetInstance();
	playerInstance->AddPlayerCharacter(sophia);
	playerInstance->AddPlayerCharacter(jason);

	#pragma endregion
	
	this->PlayScene();

	#pragma region Start keyboard
	
	this->keyHandler = new CKeyHander();
	g_inputHandler->SetHandleWindow(this->hWnd);
	g_inputHandler->SetKeyHandler(keyHandler);
	g_inputHandler->InitKeyboard();

	#pragma endregion
}

void CGame::PlayScene()
{
	worldObjects.clear();
	renderedObjects.clear();
	DebugOut(L"[INFO] playing scene %d\n", this->currentScene);

	CPlayer::GetInstance()->SelectPlayer(this->scenes.at(this->currentScene)->GetScenePlayers().at(0));

	SRect sceneBoundary = this->scenes.at(this->currentScene)->GetMapBoundary();
	this->map = this->scenes.at(this->currentScene)->GetMapSrite();
	this->mapWidth = sceneBoundary.right;
	this->mapHeight = sceneBoundary.top;

	camera->SetBoundary(sceneBoundary);
	quadtree = new CQuadTree(0, sceneBoundary);

	std::vector<LPGAMEOBJECT> sceneObjects = this->scenes.at(this->currentScene)->GetSceneObjects();
	std::vector<LPGAMEOBJECT> scenePlayers = this->scenes.at(this->currentScene)->GetScenePlayers();
	for (const auto& object : scenePlayers) {
		worldObjects.push_back(object);
		quadtree->Insert(object);
	}
	for (const auto& object : sceneObjects) {
		worldObjects.push_back(object);
		quadtree->Insert(object);
	}
}

void CGame::SwicthScene(int id)
{
	int prevScene = this->currentScene;
	this->reset = true;
	this->currentScene = id;
	this->PlayScene();

	auto player = CPlayer::GetInstance()->GetPlayer();
	player->SetPosition(this->scenes.at(this->currentScene)->GetPositionOfGate(prevScene));
}

void CGame::UpdateGame(DWORD dt)
{
	camera->Update();
	quadtree->Update(worldObjects);
	renderedObjects.clear();
	quadtree->Retrieve(renderedObjects, camera->GetBoundingBox());

	for (auto object : worldObjects) {
		if (reset)
			return;

		if (object->IsActive() == true) {
			object->CleanTriggerTag();
			object->PhysicalUpdate(&worldObjects);
		}
	}

	for (auto object : worldObjects) {
		object->Update(dt);
	}
}

void CGame::RenderGame()
{
	LPDIRECT3DDEVICE9 d3ddv = CGame::GetInstance()->GetDirect3dDevice();
	LPDIRECT3DSURFACE9 bb = CGame::GetInstance()->GetBackbuffer();
	LPD3DXSPRITE spriteHandler = CGame::GetInstance()->GetSpriteHandler();

	if (d3ddv->BeginScene())
	{
		// Clear back buffer with a color
		d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		this->map->Draw(Vector2D(this->mapWidth / 2, this->mapHeight / 2), 1, DRAW_COLOR_DEFAULT);
		for (auto object : renderedObjects) {
			if (!object->IsLive() || !object->IsActive()) {
				continue;
			}

			object->Render();
		}

		// render collider
		for (auto object : renderedObjects) {
			if (!object->IsActive()) {
				continue;
			}

			for (auto co : object->GetColliders()) {
				co->RenderBoundingBox();
			}
		}

		spriteHandler->End();
		d3ddv->EndScene();
	}

	// Display back buffer content to the screen
	d3ddv->Present(NULL, NULL, NULL, NULL);
}

void CGame::RunGame()
{
	MSG msg;
	int done = 0;
	DWORD frameStart = GetTickCount64();
	DWORD tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount64();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		this->dt = now - frameStart;

		if (this->dt >= tickPerFrame)
		{
			frameStart = now;

			g_inputHandler->ProcessKeyboard();

			this->UpdateGame(this->dt);
			this->RenderGame();
			this->CleanGameObject();
			if (reset) {
				reset = false;
			}
		}
		else
			Sleep(tickPerFrame - this->dt);
	}
}

CGame::~CGame()
{
	if (spriteHandler != NULL) {
		this->spriteHandler->Release();
	}

	if (backBuffer != NULL) {
		this->backBuffer->Release();
	}

	if (d3ddv != NULL) {
		this->d3ddv->Release();
	}

	if (d3d != NULL) {
		this->d3d->Release();
	}
}

CGame* CGame::GetInstance()
{
	if (__instance == NULL) __instance = new CGame();
	return __instance;
}

#pragma endregion

#pragma region Load Resources

void CGame::LoadResource()
{
	LPCWSTR resourcePath = GAME_RESOURCE_PATH;
	DebugOut(L"[INFO] Start loading game resouce %s\n", resourcePath);

	// start game camera
	camera->SetSize(Vector2D(this->camWidth, this->camHeight));

	// open scene file path
	std::ifstream fs;
	fs.open(resourcePath);

	SceneSection section = SceneSection::SCENE_SECTION_UNKNOW;
	char str[2048];
	while (fs.getline(str, 2048))
	{
		std::string line(str);

		// set section
		if (line[0] == '#') continue; // skip comment line
		if (line == "[TEXTURES]") {
			section = SceneSection::SCENE_SECTION_TEXTURES;
			continue;
		}
		if (line == "[SPRITES]") {
			section = SceneSection::SCENE_SECTION_SPRITES;
			continue;
		}
		if (line == "[ANIMATIONS]") {
			section = SceneSection::SCENE_SECTION_ANIMATIONS;
			continue;
		}
		if (line == "[CHARACTERS]") {
			section = SceneSection::SCENE_SECTION_CHARACTERS;
			continue;
		}
		if (line == "[SCENES]") {
			section = SceneSection::LOAD_SCENE;
			continue;
		}
		if (line[0] == '[') {
			section = SceneSection::SCENE_SECTION_UNKNOW;
			continue;
		}

		switch (section)
		{
		case SceneSection::SCENE_SECTION_UNKNOW:
			break;
		case SceneSection::SCENE_SECTION_TEXTURES:
			this->__ParseSection_TEXTURES__(line);
			break;
		case SceneSection::SCENE_SECTION_SPRITES:
			this->__ParseSection_SPRITES__(line);
			break;
		case SceneSection::SCENE_SECTION_ANIMATIONS:
			this->__ParseSection_ANIMATIONS__(line);
			break;
		case SceneSection::SCENE_SECTION_CHARACTERS:
			this->__ParseSection_CHARACTERS__(line);
			break;
		case SceneSection::LOAD_SCENE:
			this->__LoadSceneResource__(line);
			break;
		default:
			break;
		}
	}
	fs.close();
	DebugOut(L"[INFO] Load game resource done\n");
}

void CGame::__LoadSceneResource__(std::string line)
{
	std::vector<std::string> tokens = SplitLine(line);
	if (tokens.size() < 2)
		return;

	int sceneId = atoi(tokens[0].c_str());
	LPCWSTR scenePath = ToLPCWSTR(tokens[1]);

	DebugOut(L"[INFO] Start loading scene %s\n", scenePath);

	LPSCENE newScene = nullptr;
	newScene = new CScene(scenePath);
	newScene->LoadScene();

	this->scenes.insert(std::make_pair(sceneId, newScene));
	DebugOut(L"[INFO] Loading scene %s done\n", scenePath);
}

void CGame::__ParseSection_TEXTURES__(std::string line)
{
	std::vector<std::string> tokens = SplitLine(line);
	if (tokens.size() < 5)
		return;

	std::string texId = (tokens[0].c_str());
	std::wstring texPath = ToWSTR(tokens[1]);
	int R = atoi(tokens[2].c_str());
	int G = atoi(tokens[3].c_str());
	int B = atoi(tokens[4].c_str());

	g_textures->Add(texId, texPath.c_str(), D3DCOLOR_XRGB(R, G, B));
}

void CGame::__ParseSection_SPRITES__(std::string line)
{
	std::vector<std::string> tokens = SplitLine(line);
	if (tokens.size() < 3)
		return; // skip

	std::string id = tokens[0].c_str();
	int left = atoi(tokens[1].c_str());
	int top = atoi(tokens[2].c_str());
	int width = atoi(tokens[3].c_str());
	int height = atoi(tokens[4].c_str());
	std::string texId = (tokens[5].c_str());

	LPDIRECT3DTEXTURE9 texOfThis = g_textures->Get(texId);
	if (texOfThis == nullptr) {
		DebugOut(L"[ERROR] TexId %d is not existed\n", texId);
		return; // skip
	}

	g_sprites->Add(id, left, top, width, height, texOfThis);
}

void CGame::__ParseSection_ANIMATIONS__(std::string line)
{
	std::vector<std::string> tokens = SplitLine(line);
	if (tokens.size() < 3)
		return; // skip
	LPANIMATION lpAni = new CAnimation();
	std::string id = tokens[0].c_str();
	for (int i = 1; i < tokens.size(); i += 2) {
		std::string spriteId = tokens[i].c_str();
		int frameTime = atoi(tokens[i + 1].c_str());
		lpAni->Add(spriteId, frameTime);
	}

	g_animations->Add(id, lpAni);
}

void CGame::__ParseSection_CHARACTERS__(std::string line)
{
	std::vector<std::string> tokens = SplitLine(line);
	if (tokens.size() < 6)
		return;

	LPGAMEOBJECT player = nullptr;
	std::string playerName = tokens[0].c_str();

	if (playerName == "sophia") {
		player = new CSophia;
		sophia = (CSophia*)player;
		CPlayer::GetInstance()->AddPlayerCharacter(sophia);
	}
	else if (playerName == "jason") {
		player = new CJason;
		jason = (CJason*)player;
		CPlayer::GetInstance()->AddPlayerCharacter(jason);
	}
	else {
		DebugOut(L"[ERROR] Unknow player name: %s\n", playerName);
		return;
	}

	// prepare player
	int nx = atoi(tokens[1].c_str());
	float x = atoi(tokens[2].c_str());
	float y = atoi(tokens[3].c_str());
	float width = atoi(tokens[4].c_str());
	float height = atoi(tokens[5].c_str());
	player->SetPosition(Vector2D(x, y));
	player->SetNx(nx);
}

void CGame::NewGameObject(LPGAMEOBJECT& newObject)
{
	worldObjects.push_back(newObject);
	quadtree->Insert(newObject);
}

std::vector<LPGAMEOBJECT> CGame::GetRenderedObjects()
{
	return renderedObjects;
}

void CGame::CleanGameObject()
{
	for (int i = 0; i < worldObjects.size(); i++) {
		auto object = worldObjects.at(i);

		bool removed = false;
		if (object->IsLive() == false) {
			removed = true; // remove when hp lower than 0
		}
		else if (!quadtree->GetBoundingBox().Contain(object->GetColliders().at(0)->GetBoundingBox())) {
			removed = true; // remove when out of quadtree
		}

		if (removed) {
			worldObjects.erase(std::next(worldObjects.begin() + i - 1));
			quadtree->RemoveEntityFromLeafNodes(object);
			continue;
		}
	}
}

#pragma endregion
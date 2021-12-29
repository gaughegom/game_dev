#include "Game.h"

#include "Animations.h"
#include "Camera.h"
#include "KeyHandler.h"
#include "QuadTree.h"
#include "Textures.h"
#include "PlayerHealthHub.h"
#include "Sound.h"

#include "BigJason.h"
#include "Jason.h"
#include "Sophia.h"
#include "SophiaBullet.h"

CSophia* sophia;
CJason* jason;
CBigJason* bigJason;
CQuadTree* quadtree;

CCamera* g_camera = CCamera::GetInstance();
CTextures* g_textures = CTextures::GetInstance();
CSprites* g_sprites = CSprites::GetInstance();
CAnimations* g_animations = CAnimations::GetInstance();
CInputHandler* g_inputHandler = CInputHandler::GetInstance();
CPlayer* g_player = CPlayer::GetInstance();

CGame* CGame::__instance = nullptr;
DWORD CGame::dt = 0;

void CGame::AddGameObjectToWorld(LPGAMEOBJECT const& newObject)
{
	this->worldObjects.push_back(newObject);
	quadtree->Insert(newObject);
}

// DirectX

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

	if (d3ddv == nullptr)
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
void CGame::Draw(Vector2D position, int nx, 
	LPDIRECT3DTEXTURE9 texture, 
	int left, int top, int right, int bottom, 
	D3DCOLOR color, int layer, float rotate)
{
	Vector2D cameraPos = g_camera->GetPosition();

	Vector3D p(0, 0, 0);
	RECT r{
		left,
		top,
		right,
		bottom
	};
	

	Vector3D center = Vector3D((right - left) / 2, (bottom - top) / 2, 1.0f);

	D3DXMATRIX matrix;
	D3DXMatrixIdentity(&matrix);

	// rotateZ
	D3DXMATRIX dmRotateZ;
	D3DXMatrixRotationZ(&dmRotateZ, rotate * 3.14 / 180);

	// flip X
	D3DXMATRIX dmFlipX;
	D3DXMatrixScaling(&dmFlipX, nx, 1.0f, 1.0f);

	// translate 
	D3DXMATRIX dmTranslation;
	D3DXMatrixTranslation(&dmTranslation, (position.x - cameraPos.x), (-position.y + cameraPos.y), layer);

	matrix *= dmRotateZ;
	matrix *= dmFlipX;
	matrix *= dmTranslation;

	spriteHandler->SetTransform(&matrix);

	spriteHandler->Draw(texture, &r, &center, &p, color);
}

// Game loop

void CGame::InitGame(HWND hWnd)
{
	srand(time(0));
	this->InitDirectX(hWnd);

	// TODO: This is only for test
	#pragma region Texture bbox

	g_textures->Add("bbox", L"textures//bbox.png", D3DCOLOR_XRGB(0, 0, 0));

	#pragma endregion

	this->LoadResource();
	this->PlayScene();

	#pragma region Start keyboard

	this->keyHandler = new CKeyHandler();
	g_inputHandler->SetHandleWindow(this->hWnd);
	g_inputHandler->SetKeyHandler(keyHandler);
	g_inputHandler->InitKeyboard();

	#pragma endregion
}

void CGame::UpdateGame(DWORD dt)
{
	// pop from queue
	while (!this->queueObjects.empty()) {
		this->AddGameObjectToWorld(this->queueObjects.front());
		this->queueObjects.pop();
	}

	g_camera->Update();
	quadtree->Update(this->worldObjects);
	this->renderedObjects.clear();
	quadtree->Retrieve(this->renderedObjects, g_camera->GetBoundingBox());

	for (LPGAMEOBJECT& object : this->renderedObjects) {
		if (reset)
			return;

		if (object->IsActive() == true) {
			object->CleanTriggerTag();
			object->PhysicalUpdate(&this->renderedObjects);
		}
	}

	for (LPGAMEOBJECT& object : this->renderedObjects) {
		object->Update(dt);
	}
}

void CGame::RenderGame()
{
	LPDIRECT3DDEVICE9 d3ddv = CGame::GetInstance()->GetDirect3dDevice();
	LPDIRECT3DSURFACE9 bb = CGame::GetInstance()->GetBackbuffer();
	LPD3DXSPRITE spriteHandler = CGame::GetInstance()->GetSpriteHandler();

	if (d3ddv->BeginScene() == D3D_OK)
	{
		// Clear back buffer with a color
		d3ddv->ColorFill(bb, nullptr, DrawBackgroundColor());

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_DEPTH_BACKTOFRONT);

		this->map->Draw(Vector2D(this->mapWidth / 2, this->mapHeight / 2), 1, DrawArgbColorDefault());
		for (LPGAMEOBJECT& object : this->renderedObjects) {
			if (!object->IsActive()) {
				continue;
			}

			object->Render();
		}

		if (this->foreMap != nullptr) {
			this->foreMap->Draw(Vector2D(this->mapWidth / 2, this->mapHeight / 2), 1, DrawArgbColorDefault(), DrawLayer02);
		}

		// render hub
		CPlayerHealthHub::GetInstance()->Render();

		// render collider
		for (LPGAMEOBJECT& object : this->renderedObjects) {
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
	d3ddv->Present(nullptr, nullptr, nullptr, nullptr);
}

void CGame::RunGame()
{
	MSG msg;
	int done = 0;
	DWORD frameStart = GetTickCount64();
	DWORD tickPerFrame = 1000 / FrameRatePerSecond;

	while (!done)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
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

// Load Resources

void CGame::LoadResource()
{
	LPCWSTR resourcePath = GameDatabasePath;
	DebugOut(L"[INFO] Start loading game resouce %s\n", resourcePath);

	// start game g_camera
	g_camera->SetSize(Vector2D(this->camWidth, this->camHeight));

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
		if (line == "[SETTINGS]") {
			section = SceneSection::SETTINGS;
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
		case SceneSection::SETTINGS:
			this->__ParseSection_SETTINGS__(line);
			break;
		default:
			break;
		}
	}
	fs.close();

	// load sound
	CSound::GetInstance()->Init(this->hWnd);

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
		g_player->AddPlayerCharacter(sophia);
	}
	else if (playerName == "jason") {
		player = new CJason;
		jason = (CJason*)player;
		g_player->AddPlayerCharacter(jason);
	}
	else if (playerName == "bJason") {
		player = new CBigJason;
		bigJason = (CBigJason*)player;
		// TODO: Add bigjason to playerInstance
		g_player->AddPlayerCharacter(bigJason);
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

void CGame::__ParseSection_SETTINGS__(std::string line)
{
	std::vector<std::string> tokens = SplitLine(line);
	
	int beginScene = atoi(tokens[0].c_str());

	this->currentScene = beginScene;
}

// GameObject

void CGame::CleanGameObject()
{
	this->worldObjects.erase(std::remove_if(this->worldObjects.begin(), this->worldObjects.end(),
		[](LPGAMEOBJECT& obj) {
			bool removable = false;
			if (obj->IsLive() == false) {
				removable = true; // remove when hp lower than 0
			}
			else if (!quadtree->GetBoundingBox().Contain(obj->GetPosition())) {
				if (dynamic_cast<CJason*>(obj) || dynamic_cast<CSophia*>(obj))
					removable = false;
				else
					removable = true; // remove when out of quadtree
			}

			if (removable) {
				if (dynamic_cast<CSophiaBullet*>(obj)) {
					CSophiaBullet* bullet = (CSophiaBullet*)obj;
					bullet->OnDelete();
				}
				quadtree->RemoveEntityFromLeafNodes(obj);
			}
			return removable;
		}), this->worldObjects.end());
}

// Scene

void CGame::PlayScene()
{
	this->worldObjects.clear();
	this->renderedObjects.clear();
	DebugOut(L"[INFO] playing scene %d\n", this->currentScene);

	if (g_player->GetPlayer() == nullptr) {
		g_player->SelectPlayer(g_player->GetSophia());
	}

	SRect sceneBoundary = this->scenes.at(this->currentScene)->GetMapBoundary();
	this->map = this->scenes.at(this->currentScene)->GetMapSrite();
	this->foreMap = this->scenes.at(this->currentScene)->GetForeMapSprite();
	this->mapWidth = sceneBoundary.right;
	this->mapHeight = sceneBoundary.top;

	SceneMapType mapType = this->scenes.at(this->currentScene)->GetMapType();
	switch (mapType)
	{
	case SceneMapType::OUTDOOR:
		// set outdoor
		g_camera->SetFreezeBoundary(OUTDOOR_MAP_FREEZE_CAMERA);
		break;

	case SceneMapType::INDOOR:
		g_camera->SetFreezeBoundary(INDOOR_MAP_FREEZE_CAMERA);
		break;
	}
	g_camera->SetBoundary(sceneBoundary);



	quadtree = new CQuadTree(0, sceneBoundary);

	// loading sceneObject to worldObjects
	std::vector<LPGAMEOBJECT> sceneObjects = this->scenes.at(this->currentScene)->GetSceneObjects();
	for (auto& object : sceneObjects) {
		this->AddGameObjectToWorld(object);
	}

	// select player
	this->MappingPlayerScene();
}

void CGame::SwitchScene(int id)
{
	DebugOut(L"[INFO] Switch scene: %d -> %d\n", this->currentScene, id);
	int prevScene = this->currentScene;
	std::vector<LPGAMEOBJECT> preWorldObject = this->worldObjects;
	this->reset = true;
	this->currentScene = id;

	this->PlayScene();

	auto player = g_player->GetPlayer();
	Vector2D playerPosition = this->scenes.at(this->currentScene)->GetPositionOfGate(prevScene) - Vector2D(0, 16);
	player->SetPosition(playerPosition);

	this->scenes.at(prevScene)->SetSceneObjects(preWorldObject);
}

void CGame::MappingPlayerScene()
{
	// TODO: check scene when add BigJason
	LPGAMEOBJECT player = g_player->GetPlayer();
	LPGAMEOBJECT playerSophia = g_player->GetSophia();
	LPGAMEOBJECT playerJason = g_player->GetJason();
	LPGAMEOBJECT playerBigJason = g_player->GetBigJason();
	bool sophiaExist = false;
	bool jasonExist = false;
	bool bigJasonExist = false;

	// check player already in worldObjects
	for (int i = this->worldObjects.size() - 1; i > this->worldObjects.size() - 3; i--) {
		if (this->worldObjects.at(i) == playerSophia) {
			sophiaExist = true;
			continue;
		}
		else if (this->worldObjects.at(i) == playerJason) {
			jasonExist = true;
			continue;
		}
		else if (this->worldObjects.at(i) == playerBigJason) {
			bigJasonExist = true;
			continue;
		}
	}

	// add player to worldObjects
	if (this->scenes.at(this->currentScene)->GetMapType() == SceneMapType::OUTDOOR) {
		if (dynamic_cast<CSophia*>(CPlayer::GetInstance()->GetPlayer())) {
			if (sophiaExist == false) {
				this->AddGameObjectToWorld(playerSophia);
			}

			if (jasonExist == false) {
				this->AddGameObjectToWorld(playerJason);
			}
		}
		else if (dynamic_cast<CJason*>(CPlayer::GetInstance()->GetPlayer())) {
			if (jasonExist == false) {
				this->AddGameObjectToWorld(playerJason);
			}
		}
		else {
			this->AddGameObjectToWorld(playerSophia);
			this->AddGameObjectToWorld(playerJason);
		}

		if (player == playerBigJason) {
			if (playerJason->IsActive()) {
				g_player->SelectPlayer(playerJason);
			}
			else {
				g_player->SelectPlayer(playerSophia);
			}
		}
	}
	else if (this->scenes.at(this->currentScene)->GetMapType() == SceneMapType::INDOOR) {
		if (player == playerJason || player == playerSophia) {
			g_player->SelectPlayer(playerBigJason);
			g_player->GetPlayer()->
				SetPosition(this->scenes.at(this->currentScene)
					->GetPositionOfGate(this->currentScene - 1));
		}
		
		if (bigJasonExist == false) {
			this->AddGameObjectToWorld(playerBigJason);
		}
	}
}

CGame* CGame::GetInstance()
{
	if (__instance == nullptr) __instance = new CGame();
	return __instance;
}

CGame::~CGame()
{
	if (this->spriteHandler != nullptr) { this->spriteHandler->Release(); }
	if (this->backBuffer != nullptr) { this->backBuffer->Release(); }
	if (this->d3ddv != nullptr) { this->d3ddv->Release(); }
	if (this->d3d != nullptr) { this->d3d->Release(); }
}

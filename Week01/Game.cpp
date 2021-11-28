#include <fstream>
#include "Game.h"
#include "Textures.h"
#include "Animations.h"
#include "Camera.h"
#include "QuadTree.h"
#include "InputHandler.h"

#include "Sophia.h"
#include "Jason.h"
#include "EnemyDrap.h"
#include "EnemyEyelet.h"
#include "EnemyGX-680.h"
#include "EnemyOffside.h"
#include "EnemyStuka.h"

#include "rapidjson/include/rapidjson/document.h"
#include "rapidjson/include/rapidjson/writer.h"
#include "rapidjson/include/rapidjson/stringbuffer.h"
#include "rapidjson/include/rapidjson/filereadstream.h"

CSophia* pSophia;
CJason* pJason;
CCamera* pCamera;
CQuadTree* pQuadtree;

std::vector<CGameObject*> pGameObjects;
std::vector<CGameObject*> pRenderObjects;

CTextures* g_textures = CTextures::GetInstance();
CSprites* g_sprites = CSprites::GetInstance();
CAnimations* g_animations = CAnimations::GetInstance();
CInputHandler* g_inputHandler = CInputHandler::GetInstance();

CGame* CGame::__instance = NULL;

#pragma region KEYBOARD

class CKeyHander : public CKeyEventHandler
{
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};

void CKeyHander::OnKeyDown(int keyCode)
{
	if (keyCode == DIK_A) {
		pSophia->AlterSelect();
		pJason->AlterSelect();
		if (pSophia->IsSelected()) {
			pCamera->SetTarget(pSophia);
			pCamera->Update();
			pRenderObjects.clear();
			pQuadtree->Update(pGameObjects);
			pQuadtree->Retrieve(pRenderObjects, pCamera->GetBoundingBox());
		}
		else {
			pCamera->SetTarget(pJason);
			pCamera->Update();
			pRenderObjects.clear();
			pQuadtree->Update(pGameObjects);
			pQuadtree->Retrieve(pRenderObjects, pCamera->GetBoundingBox());
		}
	}
}

void CKeyHander::OnKeyUp(int keyCode)
{
	DebugOut(L"[INFO] KeyUp: %d\n", keyCode);
}

void CKeyHander::KeyState(BYTE* states)
{
	// switch selected object by key
	// empty
}

#pragma endregion

#pragma region DIRECTX

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

	backBufferWidth = d3dpp.BackBufferWidth;
	backBufferHeight = d3dpp.BackBufferHeight;

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
	DebugOut(L"[INFO] Screen: %d, %d\n", backBufferWidth, backBufferHeight);
}

/*
	Utility function to wrap LPD3DXSPRITE::Draw
*/
void CGame::Draw(Vector2D position, int nx, LPDIRECT3DTEXTURE9 texture, int left, int top, int right, int bottom)
{

	Vector2D cameraPos = pCamera->GetPosition();

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
	D3DXMatrixScaling(&dmFlipX, -nx, 1.0f, 1.0f);

	// translate 
	D3DXMATRIX dmTranslation;
	D3DXMatrixTranslation(&dmTranslation, (position.x - cameraPos.x), (-position.y + cameraPos.y), 0.0f);

	matrix *= dmFlipX;
	matrix *= dmTranslation;

	spriteHandler->SetTransform(&matrix);

	spriteHandler->Draw(texture, &r, &center, &p, D3DCOLOR_XRGB(255, 255, 255));
}

#pragma endregion

#pragma region GAME PROCESS

void CGame::InitGame(HWND hWnd)
{
	this->InitDirectX(hWnd);

	// For only test
	g_textures->Add(10, SOPHIA_JASON_TEXTURE_PATH, D3DCOLOR_XRGB(0, 0, 0));
	g_textures->Add(100, BACKGOUND_TEXTURE_PATH, TEXTURE_TRANS_COLOR);
	LPDIRECT3DTEXTURE9 texTestDebug = g_textures->Get(10);
	LPDIRECT3DTEXTURE9 texBackground = g_textures->Get(100);

	g_sprites->Add(1000, 0, 0, 1376, 528, texBackground);
	this->lpsBackground = CSprites::GetInstance()->Get(1000);
	this->backgound = Vector2D(550, 200);
	
	g_sprites->Add(2000, 0, 0, 1, 1, texTestDebug);

	#pragma region KEYBOARD
	
	g_inputHandler->SetHandleWindow(this->hWnd);

	this->keyHandler = new CKeyHander();
	g_inputHandler->SetKeyHandler(keyHandler);
	g_inputHandler->InitKeyboard();

	#pragma endregion

	this->LoadResource();
	this->CreateGameObject();

	// start camera
	#pragma region CAMERA START
	
	pCamera = new CCamera();
	pCamera->SetTarget(pSophia);
	pCamera->SetSize(this->backBufferWidth, this->backBufferHeight);
	pCamera->Update();

	#pragma endregion

	// start quadtree
	#pragma region QUADTREE START
	
	pQuadtree = new CQuadTree(0, SRect(0, QUADTREE_HEIGHT, QUADTREE_WIDTH * 5, 0));
	pQuadtree->Update(pGameObjects);
	pRenderObjects.clear();
	pQuadtree->Retrieve(pRenderObjects, pCamera->GetBoundingBox());

	#pragma endregion
}

void CGame::CreateGameObject()
{
	// create sophia
	pSophia = new CSophia();
	pSophia->Select(true);

	// create jason
	pJason = new CJason();

	// create drap
	auto pDrap = new CEnemyDrap();
	pGameObjects.push_back(pDrap);

	// create eyelet
	auto pEyelet = new CEnemyEyelet();
	pGameObjects.push_back(pEyelet);

	// create gx680
	auto pGX680 = new CEnemyGX680();
	pGameObjects.push_back(pGX680);

	// create stuka
	auto pStuka = new CEnemyStuka();
	pGameObjects.push_back(pStuka);

	auto pOffside = new CEnemyOffside();
	pGameObjects.push_back(pOffside);

	// push sophia in gameObject vector
	pGameObjects.push_back(pSophia);
	pGameObjects.push_back(pJason);
}

void CGame::LoadResource()
{
	LPCWSTR sceneFilePath = SCENE2_PATH;
	DebugOut(L"[INFO] Start loading scene resouce %s\n", sceneFilePath);

	// Load camera
	pCamera = new CCamera();
	pCamera->SetTarget(pSophia);
	pCamera->SetSize(this->backBufferWidth, this->backBufferHeight);

	// open scene file path
	ifstream fs;
	fs.open(sceneFilePath);

	SceneSection section = SceneSection::SCENE_SECTION_UNKNOW;
	char str[1024];
	while (fs.getline(str, 1024))
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
		if (line[0] == '[') {
			section = SceneSection::SCENE_SECTION_UNKNOW;
			continue;
		}

		switch (section)
		{
		case SceneSection::SCENE_SECTION_UNKNOW:
			break;
		case SceneSection::SCENE_SECTION_TEXTURES:
			__ParseSection_TEXTURES__(line);
			break;
		case SceneSection::SCENE_SECTION_SPRITES:
			__ParseSection_SPRITES__(line);
			break;
		case SceneSection::SCENE_SECTION_ANIMATIONS:
			__ParseSection_ANIMATIONS__(line);
			break;
		case SceneSection::SCENE_SECTION_MAP:
			break;
		default:
			break;
		}
	}
	fs.close();
	DebugOut(L"[INFO] Load scene resource done\n");
}

void CGame::__ParseSection_TEXTURES__(std::string line)
{
	std::vector<std::string> tokens = SplitLine(line);
	if (tokens.size() < 5)
		return;

	int texId = atoi(tokens[0].c_str());
	wstring texPath = ToWSTR(tokens[1]);
	int R = atoi(tokens[2].c_str());
	int G = atoi(tokens[3].c_str());
	int B = atoi(tokens[4].c_str());

	g_textures->Add(texId, texPath.c_str(), D3DCOLOR_XRGB(R, G, B));
}

void CGame::__ParseSection_SPRITES__(std::string line)
{
	std::vector<std::string> tokens = SplitLine(line);
	if (tokens.size() < 6)
		return; // skip

	int id = atoi(tokens[0].c_str());
	int left = atoi(tokens[1].c_str());
	int top = atoi(tokens[2].c_str());
	int width = atoi(tokens[3].c_str());
	int height = atoi(tokens[4].c_str());
	int texId = atoi(tokens[5].c_str());

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
	int id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2) {
		int spriteId = atoi(tokens[i].c_str());
		int frameTime = atoi(tokens[i + 1].c_str());
		lpAni->Add(spriteId, frameTime);
	}

	g_animations->Add(id, lpAni);
}

void CGame::UpdateGame(DWORD dt)
{
	pCamera->Update();
	pQuadtree->Update(pGameObjects);
	pRenderObjects.clear();
	pQuadtree->Retrieve(pRenderObjects, pCamera->GetBoundingBox());
	DebugOut(L"render objects: %d\n", pRenderObjects.size());
	for (auto object : pRenderObjects) {
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

		this->lpsBackground->Draw(this->backgound, 1);
		for (auto object : pRenderObjects) {
			object->Render();
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

		DWORD now = GetTickCount();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		DWORD dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;

			g_inputHandler->ProcessKeyboard();

			UpdateGame(dt);
			RenderGame();
		}
		else
			Sleep(tickPerFrame - dt);
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
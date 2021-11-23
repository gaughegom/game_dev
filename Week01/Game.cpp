#include "Game.h"
#include "Textures.h"
#include "Animations.h"
#include "Sophia.h"
#include "Jason.h"
#include "EnemyLib.h"
#include "Camera.h"
#include "QuadTree.h"
#include "InputHandler.h"

CSophia* pSophia;
CJason* pJason;
CCamera* pCamera;
CTextures* pTextures = CTextures::GetInstance();
CQuadTree* pQuadTree;

std::vector<CGameObject*> pGameObjects;
std::vector<CGameObject*> pRenderObjects;

CSprites* g_sprites = CSprites::GetInstance();
CAnimations* g_animations = CAnimations::GetInstance();

CGame* CGame::__instance = NULL;
CInputHandler* g_inputHandler = CInputHandler::GetInstance();

#pragma region KEYBOARD

class CKeyHander : public CKeyEventHandler
{
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};

void CKeyHander::OnKeyDown(int keyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", keyCode);
}

void CKeyHander::OnKeyUp(int keyCode)
{
	DebugOut(L"[INFO] KeyUp: %d\n", keyCode);
}

void CKeyHander::KeyState(BYTE* states)
{
	// empty
}

int CGame::IsKeyDown(int KeyCode)
{
	return 0;
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

	pTextures->Add(TEXTURES_SOPHIA_ID, SOPHIA_JASON_TEXTURE_PATH, TEXTURE_TRANS_COLOR);
	pTextures->Add(TEXTURES_JASON_ID, SOPHIA_JASON_TEXTURE_PATH, TEXTURE_TRANS_COLOR);
	pTextures->Add(TEXTURES_ENEMY_ROBOT_ID, ENEMY_TEXTURE_PATH, TEXTURE_TRANS_COLOR);
	LPDIRECT3DTEXTURE9 texSophia = pTextures->Get(TEXTURES_SOPHIA_ID);
	LPDIRECT3DTEXTURE9 texJason = pTextures->Get(TEXTURES_JASON_ID);
	LPDIRECT3DTEXTURE9 texRobot = pTextures->Get(TEXTURES_ENEMY_ROBOT_ID);

	#pragma region SOPHIA SPRITES
	
	// Add 2 wheel
	g_sprites->Add(SPRITE_SOPHIA_WHEEL_1, 3, 21, 11, 29, texSophia);
	g_sprites->Add(SPRITE_SOPHIA_WHEEL_2, 21, 21, 29, 29, texSophia);
	g_sprites->Add(SPRITE_SOPHIA_WHEEL_3, 12, 21, 20, 29, texSophia);
	g_sprites->Add(SPRITE_SOPHIA_WHEEL_4, 30, 21, 38, 29, texSophia);

	// Add sophia body
	g_sprites->Add(SPRITE_SOPHIA_BODY, 3, 12, 11, 20, texSophia);

	// Add cabin
	g_sprites->Add(SPRITE_SOPHIA_CABIN_00, 39, 3, 55, 11, texSophia);
	//g_sprites->Add(SPRITE_SOPHIA_CABIN_OPEN, 56, 3, 72, 11, texSophia); // fix open later
	g_sprites->Add(SPRITE_SOPHIA_CABIN_45, 73, 4, 89, 19, texSophia);

	// add gun
	g_sprites->Add(SPRITE_SOPHIA_GUN_00, 12, 5, 19, 9, texSophia);
	g_sprites->Add(SPRITE_SOPHIA_GUN_45, 21, 3, 29, 11, texSophia);
	g_sprites->Add(SPRITE_SOPHIA_GUN_90, 32, 3, 36, 10, texSophia);


	LPANIMATION lpAni;
	// add sophia left wheel
	lpAni = new CAnimation(5);
	lpAni->Add(SPRITE_SOPHIA_WHEEL_1);
	lpAni->Add(SPRITE_SOPHIA_WHEEL_3);
	lpAni->Add(SPRITE_SOPHIA_WHEEL_2);
	lpAni->Add(SPRITE_SOPHIA_WHEEL_4);
	g_animations->Add(ANIMATION_SOPHIA_LEFT_WHEEL, lpAni);

	lpAni = new CAnimation(5);
	// add sophia right wheel
	lpAni->Add(SPRITE_SOPHIA_WHEEL_2);
	lpAni->Add(SPRITE_SOPHIA_WHEEL_4);
	lpAni->Add(SPRITE_SOPHIA_WHEEL_1);
	lpAni->Add(SPRITE_SOPHIA_WHEEL_3);
	g_animations->Add(ANIMATION_SOPHIA_RIGHT_WHEEL, lpAni);

	#pragma endregion

	#pragma region JASON SPRITES

	// jason left
	g_sprites->Add(SPRITE_JASON_LEFT_01, 208, 69, 232, 100, texJason);
	g_sprites->Add(SPRITE_JASON_LEFT_02, 233, 69, 257, 101, texJason);
	g_sprites->Add(SPRITE_JASON_LEFT_03, 258, 69, 282, 100, texJason);
	// jason up
	g_sprites->Add(SPRITE_JASON_UP_01, 210, 36, 230, 67, texJason);
	g_sprites->Add(SPRITE_JASON_UP_02, 235, 36, 255, 68, texJason);
	g_sprites->Add(SPRITE_JASON_UP_03, 260, 36, 280, 67, texJason);
	// jason down
	g_sprites->Add(SPRITE_JASON_DOWN_01, 210, 3, 230, 34, texJason);
	g_sprites->Add(SPRITE_JASON_DOWN_02, 235, 3, 255, 35, texJason);
	g_sprites->Add(SPRITE_JASON_DOWN_03, 280, 3, 280, 34, texJason);

	// add animation jason left
	lpAni = new CAnimation(5);
	lpAni->Add(SPRITE_JASON_LEFT_01);
	lpAni->Add(SPRITE_JASON_LEFT_02);
	lpAni->Add(SPRITE_JASON_LEFT_03);
	g_animations->Add(ANIMATION_JASON_LEFT, lpAni);
	// add animation jason up
	lpAni = new CAnimation(5);
	lpAni->Add(SPRITE_JASON_UP_01);
	lpAni->Add(SPRITE_JASON_UP_02);
	lpAni->Add(SPRITE_JASON_UP_03);
	g_animations->Add(ANIMATION_JASON_UP, lpAni);
	// add aniamtion jason down
	lpAni = new CAnimation(5);
	lpAni->Add(SPRITE_JASON_DOWN_01);
	lpAni->Add(SPRITE_JASON_DOWN_02);
	lpAni->Add(SPRITE_JASON_DOWN_03);
	g_animations->Add(ANIMATION_JASON_DOWN, lpAni);

	#pragma endregion

	#pragma region ENEMY SPRITES

	g_sprites->Add(SPRITE_ENEMY_ROBOT, 104, 0, 118, 26, texRobot);
	lpAni = new CAnimation(5);
	lpAni->Add(SPRITE_ENEMY_ROBOT);
	g_animations->Add(ANIMATION_ENEMY_ROBOT, lpAni);

	#pragma endregion

	#pragma region KEYBOARD
	
	g_inputHandler->SetHandleWindow(this->hWnd);

	this->keyHandler = new CKeyHander();
	g_inputHandler->SetKeyHandler(keyHandler);
	g_inputHandler->InitKeyboard();
	//this->InitKeyboard(keyHandler);

	#pragma endregion

	CreateGameObject();

	// create camera
	#pragma region CAMERA START
	
	pCamera = new CCamera();
	pCamera->SetTarget(pSophia);
	pCamera->SetSize(this->backBufferWidth, this->backBufferHeight);
	pCamera->Update();

	#pragma endregion

	// InitGame quadtree
	#pragma region QUADTREE START
	
	pQuadTree = new CQuadTree(0, SRect(0, this->backBufferHeight * 10, this->backBufferWidth * 10, 0));
	ObserverGame();

	#pragma endregion
}

void CGame::ObserverGame()
{
	pRenderObjects.clear();
	pQuadTree->Update(pGameObjects);
	pQuadTree->ContainerizeObject(pRenderObjects, pCamera->GetBoundingBox());
}

void CGame::CreateGameObject()
{
	// create sophia
	pSophia = new CSophia();
	pSophia->SetVelocity(0, 0);

	// create jason
	pJason = new CJason();

	// create 10 enemy robot at random position
	CEnemyRobot* pRobot;
	srand(time(0));
	for (int i = 0; i < 20; i++) {
		pRobot = new CEnemyRobot();
		pRobot->SetVelocity(0, 0);
		pRobot->SetPosition(PLAYER_START_X + i * 100, PLAYER_START_Y - 10);
		pGameObjects.push_back(pRobot);
	}

	// push sophia in gameObject vector
	pGameObjects.push_back(pSophia);
	pGameObjects.push_back(pJason);
}

void CGame::UpdateGame(DWORD dt)
{
	pCamera->Update();

	bool activeObserver = false;
	for (auto pObject : pRenderObjects) {
		Vector2D prevPos = pObject->GetPosition();
		pObject->Update(dt);
		if (pObject->GetPosition() != prevPos) {
			activeObserver = true;
		}
		
		/*auto pObjectNode = pQuadTree->GetObjectNode(pObject);
		SRect objRect = SRect(
			pObject->GetX(),
			pObject->GetY() + pObject->GetHeight(),
			pObject->GetX() + pObject->GetWidth(),
			pObject->GetY());
		if (!pObjectNode->GetRect().IsConstain(objRect)) {
			activeObserver = true;
		}*/

	}
	if (activeObserver) {
		ObserverGame();
		DebugOut(L"[INFO] render object: %d\n", pRenderObjects.size());
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
	DWORD frameStart = GetTickCount();
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

// get game instance 
CGame* CGame::GetInstance()
{
	if (__instance == NULL) __instance = new CGame();
	return __instance;
}

#pragma endregion
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

	g_textures->Add(TEXTURES_PLAYER_ID, SOPHIA_JASON_TEXTURE_PATH, TEXTURE_TRANS_COLOR);
	g_textures->Add(TEXTURES_ENEMY_ID, ENEMY_TEXTURE_PATH, TEXTURE_TRANS_COLOR);
	LPDIRECT3DTEXTURE9 texPlayer = g_textures->Get(TEXTURES_PLAYER_ID);
	LPDIRECT3DTEXTURE9 texEnemy = g_textures->Get(TEXTURES_ENEMY_ID);

	g_textures->Add(10, SOPHIA_JASON_TEXTURE_PATH, D3DCOLOR_XRGB(0, 0, 0));
	g_textures->Add(100, BACKGOUND_TEXTURE_PATH, TEXTURE_TRANS_COLOR);
	LPDIRECT3DTEXTURE9 texTestDebug = g_textures->Get(10);
	LPDIRECT3DTEXTURE9 texBackground = g_textures->Get(100);

	g_sprites->Add(1000, 0, 0, 1376, 528, texBackground);
	this->lpsBackground = CSprites::GetInstance()->Get(1000);
	this->backgound = Vector2D(550, 200);
	
	g_sprites->Add(2000, 0, 0, 1, 1, texTestDebug);

	#pragma region SOPHIA SPRITES
	
	// Add 2 wheel
	g_sprites->Add(SPRITE_SOPHIA_WHEEL_1, 3, 21, 11, 29, texPlayer);
	g_sprites->Add(SPRITE_SOPHIA_WHEEL_2, 21, 21, 29, 29, texPlayer);
	g_sprites->Add(SPRITE_SOPHIA_WHEEL_3, 12, 21, 20, 29, texPlayer);
	g_sprites->Add(SPRITE_SOPHIA_WHEEL_4, 30, 21, 38, 29, texPlayer);

	// Add sophia body
	g_sprites->Add(SPRITE_SOPHIA_BODY, 3, 12, 11, 20, texPlayer);

	// Add cabin
	g_sprites->Add(SPRITE_SOPHIA_CABIN_00, 39, 3, 55, 11, texPlayer);
	//g_sprites->Add(SPRITE_SOPHIA_CABIN_OPEN, 56, 3, 72, 11, texPlayer); // fix open later
	g_sprites->Add(SPRITE_SOPHIA_CABIN_45, 73, 4, 89, 19, texPlayer);

	// add gun
	g_sprites->Add(SPRITE_SOPHIA_GUN_00, 12, 5, 19, 9, texPlayer);
	g_sprites->Add(SPRITE_SOPHIA_GUN_45, 21, 3, 29, 11, texPlayer);
	g_sprites->Add(SPRITE_SOPHIA_GUN_90, 32, 3, 36, 10, texPlayer);


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

	// small jason
	g_sprites->Add(SPRITE_SMALL_JASON_WALK_01, 3, 30, 11, 46, texPlayer);
	g_sprites->Add(SPRITE_SMALL_JASON_WALK_02, 12, 31, 20, 46, texPlayer);
	g_sprites->Add(SPRITE_SMALL_JASON_WALK_03, 21, 30, 29, 46, texPlayer);
	g_sprites->Add(SPRITE_SMALL_JASON_WALK_04, 30, 31, 38, 46, texPlayer);

	lpAni = new CAnimation(5);
	lpAni->Add(SPRITE_SMALL_JASON_WALK_01);
	lpAni->Add(SPRITE_SMALL_JASON_WALK_02);
	lpAni->Add(SPRITE_SMALL_JASON_WALK_03);
	lpAni->Add(SPRITE_SMALL_JASON_WALK_04);
	g_animations->Add(ANIMATION_SMALL_JASON_WALK, lpAni);
	lpAni = new CAnimation(5);
	lpAni->Add(SPRITE_SMALL_JASON_WALK_03);
	g_animations->Add(ANIMATION_SMALL_JASON_STAY, lpAni);

	// big jason left
	g_sprites->Add(SPRITE_BIG_JASON_LEFT_01, 208, 69, 232, 100, texPlayer);
	g_sprites->Add(SPRITE_BIG_JASON_LEFT_02, 233, 69, 257, 101, texPlayer);
	g_sprites->Add(SPRITE_BIG_JASON_LEFT_03, 258, 69, 282, 100, texPlayer);
	// big jason up
	g_sprites->Add(SPRITE_BIG_JASON_UP_01, 210, 36, 230, 67, texPlayer);
	g_sprites->Add(SPRITE_BIG_JASON_UP_02, 235, 36, 255, 68, texPlayer);
	g_sprites->Add(SPRITE_BIG_JASON_UP_03, 260, 36, 280, 67, texPlayer);
	// big jason down
	g_sprites->Add(SPRITE_BIG_JASON_DOWN_01, 210, 3, 230, 34, texPlayer);
	g_sprites->Add(SPRITE_BIG_JASON_DOWN_02, 235, 3, 255, 35, texPlayer);
	g_sprites->Add(SPRITE_BIG_JASON_DOWN_03, 280, 3, 280, 34, texPlayer);

	// add animation jason left
	lpAni = new CAnimation(5);
	lpAni->Add(SPRITE_BIG_JASON_LEFT_01);
	lpAni->Add(SPRITE_BIG_JASON_LEFT_02);
	lpAni->Add(SPRITE_BIG_JASON_LEFT_03);
	g_animations->Add(ANIMATION_JASON_LEFT, lpAni);
	// add animation jason up
	lpAni = new CAnimation(5);
	lpAni->Add(SPRITE_BIG_JASON_UP_01);
	lpAni->Add(SPRITE_BIG_JASON_UP_02);
	lpAni->Add(SPRITE_BIG_JASON_UP_03);
	g_animations->Add(ANIMATION_JASON_UP, lpAni);
	// add aniamtion jason down
	lpAni = new CAnimation(5);
	lpAni->Add(SPRITE_BIG_JASON_DOWN_01);
	lpAni->Add(SPRITE_BIG_JASON_DOWN_02);
	lpAni->Add(SPRITE_BIG_JASON_DOWN_03);
	g_animations->Add(ANIMATION_JASON_DOWN, lpAni);

	#pragma endregion

	#pragma region ENEMY SPRITES

		#pragma region DRAP

	g_sprites->Add(SPRITE_ENEMY_DRAP_01, 40, 276, 58, 292, texEnemy);
	g_sprites->Add(SPRITE_ENEMY_DRAP_02, 60, 274, 78, 292, texEnemy);
	g_sprites->Add(SPRITE_ENEMY_DRAP_03, 80, 276, 98, 292, texEnemy);
	g_sprites->Add(SPRITE_ENEMY_DRAP_04, 100, 274, 118, 292, texEnemy);
	g_sprites->Add(SPRITE_ENEMY_DRAP_05, 128, 274, 146, 292, texEnemy);
	g_sprites->Add(SPRITE_ENEMY_DRAP_06, 148, 276, 166, 292, texEnemy);
	g_sprites->Add(SPRITE_ENEMY_DRAP_07, 168, 274, 186, 292, texEnemy);
	g_sprites->Add(SPRITE_ENEMY_DRAP_08, 188, 276, 206, 292, texEnemy);
	lpAni = new CAnimation(20);
	lpAni->Add(SPRITE_ENEMY_DRAP_01);
	lpAni->Add(SPRITE_ENEMY_DRAP_02);
	lpAni->Add(SPRITE_ENEMY_DRAP_03);
	lpAni->Add(SPRITE_ENEMY_DRAP_04);
	g_animations->Add(ANIMATION_ENEMY_DRAP, lpAni);
	lpAni = new CAnimation(20);
	lpAni->Add(SPRITE_ENEMY_DRAP_05);
	lpAni->Add(SPRITE_ENEMY_DRAP_06);
	lpAni->Add(SPRITE_ENEMY_DRAP_07);
	lpAni->Add(SPRITE_ENEMY_DRAP_08);
	g_animations->Add(ANIMATION_ENEMY_DRAP_REVERSE, lpAni);

		#pragma endregion

		#pragma region EYELET

	g_sprites->Add(SPRITE_ENEMY_EYELET_01, 40, 36, 58, 46, texEnemy);
	g_sprites->Add(SPRITE_ENEMY_EYELET_02, 60, 31, 78, 46, texEnemy);
	g_sprites->Add(SPRITE_ENEMY_EYELET_03, 80, 28, 98, 46, texEnemy);
	g_sprites->Add(SPRITE_ENEMY_EYELET_04, 100, 31, 118, 46, texEnemy);
	g_sprites->Add(SPRITE_ENEMY_EYELET_05, 128, 31, 146, 46, texEnemy);
	g_sprites->Add(SPRITE_ENEMY_EYELET_06, 148, 28, 166, 46, texEnemy);
	g_sprites->Add(SPRITE_ENEMY_EYELET_07, 168, 31, 186, 46, texEnemy);
	g_sprites->Add(SPRITE_ENEMY_EYELET_08, 188, 36, 206, 46, texEnemy);
	lpAni = new CAnimation(20);
	lpAni->Add(SPRITE_ENEMY_EYELET_01);
	lpAni->Add(SPRITE_ENEMY_EYELET_02);
	lpAni->Add(SPRITE_ENEMY_EYELET_03);
	lpAni->Add(SPRITE_ENEMY_EYELET_04);
	g_animations->Add(ANIMATION_ENEMY_EYELET, lpAni);
	lpAni = new CAnimation(20);
	lpAni->Add(SPRITE_ENEMY_EYELET_05);
	lpAni->Add(SPRITE_ENEMY_EYELET_06);
	lpAni->Add(SPRITE_ENEMY_EYELET_07);
	lpAni->Add(SPRITE_ENEMY_EYELET_08);

		#pragma endregion

		#pragma region GX680

	g_sprites->Add(SPRITE_ENEMY_GX680_01, 80, 295, 98, 312, texEnemy);
	g_sprites->Add(SPRITE_ENEMY_GX680_02, 100, 296, 118, 312, texEnemy);
	g_sprites->Add(SPRITE_ENEMY_GX680_03, 128, 296, 146, 312, texEnemy);
	g_sprites->Add(SPRITE_ENEMY_GX680_04, 148, 295, 166, 312, texEnemy);
	lpAni = new CAnimation(10);
	lpAni->Add(SPRITE_ENEMY_GX680_01);
	lpAni->Add(SPRITE_ENEMY_GX680_02);
	lpAni->Add(SPRITE_ENEMY_GX680_03);
	lpAni->Add(SPRITE_ENEMY_GX680_04);
	g_animations->Add(ANIMATION_ENEMY_GX680, lpAni);

		#pragma endregion

		#pragma region STUKA

	g_sprites->Add(SPRITE_ENEMY_STUKA_01, 74, 386, 92, 404, texEnemy);
	g_sprites->Add(SPRITE_ENEMY_STUKA_02, 94, 386, 112, 404, texEnemy);
	g_sprites->Add(SPRITE_ENEMY_STUKA_03, 114, 386, 132, 404, texEnemy);
	g_sprites->Add(SPRITE_ENEMY_STUKA_04, 134, 386, 152, 404, texEnemy);
	g_sprites->Add(SPRITE_ENEMY_STUKA_05, 154, 386, 172, 404, texEnemy);
	lpAni = new CAnimation(10);
	lpAni->Add(SPRITE_ENEMY_STUKA_01);
	lpAni->Add(SPRITE_ENEMY_STUKA_02);
	lpAni->Add(SPRITE_ENEMY_STUKA_03);
	lpAni->Add(SPRITE_ENEMY_STUKA_04);
	lpAni->Add(SPRITE_ENEMY_STUKA_05);
	g_animations->Add(ANIMATION_ENEMY_STUKA, lpAni);
		#pragma endregion

		#pragma region OFFSIDE

	g_sprites->Add(SPRITE_ENEMY_OFFSIDE_01, 26, 56, 44, 74, texEnemy);
	g_sprites->Add(SPRITE_ENEMY_OFFSIDE_02, 46, 56, 60, 74, texEnemy);
	g_sprites->Add(SPRITE_ENEMY_OFFSIDE_03, 186, 56, 200, 74, texEnemy);
	g_sprites->Add(SPRITE_ENEMY_OFFSIDE_04, 202, 56, 220, 74, texEnemy);
	lpAni = new CAnimation(5);
	lpAni->Add(SPRITE_ENEMY_OFFSIDE_01);
	lpAni->Add(SPRITE_ENEMY_OFFSIDE_02);
	lpAni->Add(SPRITE_ENEMY_OFFSIDE_03);
	lpAni->Add(SPRITE_ENEMY_OFFSIDE_04);
	g_animations->Add(ANIMATION_ENEMY_OFFSIDE, lpAni);

		#pragma endregion


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
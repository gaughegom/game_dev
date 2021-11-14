#include "prepare.h"

CGame* game;
CGamePlayer* player;
std::vector<CGameObject*> gameObjects;
CGameNpc* npc;
CTextures* textures = CTextures::Get_instance();
CCamera* camera;

class CKeyHander : public CKeyEventHandler
{
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};

CKeyHander* keyHandler;

void CKeyHander::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
}

void CKeyHander::OnKeyUp(int KeyCode)
{
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
}

void CKeyHander::KeyState(BYTE* states)
{
	if (game->IsKeyDown(DIK_RIGHT)) {
		player->SetState(PLAYER_STATE_MOVING_RIGHT);
	}
	else if (game->IsKeyDown(DIK_LEFT)) {
		player->SetState(PLAYER_STATE_MOVING_LEFT);
	}
	else if (game->IsKeyDown(DIK_UP)) {
		player->SetState(PLAYER_STATE_MOVING_UP);
	}
	else if (game->IsKeyDown(DIK_DOWN)) {
		player->SetState(PLAYER_STATE_MOVING_DOWN);
	}
	else player->SetState(PLAYER_STATE_IDLE);
}

/*
	Load all game resources
	In this example: load textures, sprites, animations and mario object
*/
void LoadResources()
{
	textures->Add(ID_TEXTURES_PLAYER, MARIO_TEXTURE_PATH, TEXTURE_TRANS_COLOR);
	textures->Add(ID_TEXTURES_NPC, MARIO_TEXTURE_PATH, TEXTURE_TRANS_COLOR);
	LPDIRECT3DTEXTURE9 texPlayer = textures->Get(ID_TEXTURES_PLAYER);
	LPDIRECT3DTEXTURE9 texNpc = textures->Get(ID_TEXTURES_NPC);

	AddMarioSprites(texPlayer);
	AddMarioAnimations();
	AddMarioSprites(texNpc);
	AddNpcAnimations();

	player = new CGamePlayer();
	CGamePlayer::AddAnimation(400);		// idle right
	CGamePlayer::AddAnimation(401);		//		left
	CGamePlayer::AddAnimation(402);		//		up
	CGamePlayer::AddAnimation(403);		//		down
	CGamePlayer::AddAnimation(500);		// walk right
	CGamePlayer::AddAnimation(501);		//		left
	CGamePlayer::AddAnimation(502);		//		up
	CGamePlayer::AddAnimation(503);		//		down

	player->SetPosition(PLAYER_START_X, PLAYER_START_Y);
	player->SetVelocity(0, 0);

	npc = new CGameNpc();
	CGameNpc::AddAnimation(600);
	CGameNpc::AddAnimation(601);
	CGameNpc::AddAnimation(602);
	CGameNpc::AddAnimation(603);

	npc->SetPosition(NPC_START_X, NPC_START_Y);
	npc->Set_state(NPC_STATE_MOVING_RIGHT);
	npc->Set_state(NPC_STATE_MOVING_DOWN);
	npc->SetVelocity(0, 0);

	gameObjects.push_back(player);
	gameObjects.push_back(npc);

	camera = new CCamera();
	camera->Set_target(player);
	camera->Set_size(SCREEN_WIDTH, SCREEN_HEIGHT);
}

/*
	Update world status for this frame
	dt: time period between beginning of last frame and beginning of this frame
*/
void Update(DWORD dt)
{
	camera->Update();
	for (auto object : gameObjects) {
		object->Update(dt);
	}
}

/*
	Render a frame
*/
void Render()
{
	LPDIRECT3DDEVICE9 d3ddv = game->GetDirect3dDevice();
	LPDIRECT3DSURFACE9 bb = game->GetBackbuffer();
	LPD3DXSPRITE spriteHandler = game->GetSpriteHandler();

	if (d3ddv->BeginScene())
	{
		// Clear back buffer with a color
		d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		for (auto object : gameObjects) {
			object->Render();
		}

		spriteHandler->End();
		d3ddv->EndScene();
	}

	// Display back buffer content to the screen
	d3ddv->Present(NULL, NULL, NULL, NULL);
}

int Run()
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

			game->ProcessKeyboard();

			Update(dt);
			Render();
		}
		else
			Sleep(tickPerFrame - dt);
	}

	return 1;
}

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

HWND Create_game_window(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			hInstance,
			NULL);

	if (!hWnd)
	{
		OutputDebugString(L"[ERROR] CreateWindow failed");
		DWORD ErrCode = GetLastError();
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd = Create_game_window(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);

	game = CGame::GetInstance();
	game->InitDirectX(hWnd);

	keyHandler = new CKeyHander();
	game->InitKeyboard(keyHandler);
	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);


	LoadResources();
	Run();

	return 0;
}
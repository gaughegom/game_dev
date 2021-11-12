#include "prepare.h"

CSprites* sprites = CSprites::Get_instance();
CAnimations* animations = CAnimations::Get_instance();

void Add_mario_sprites(LPDIRECT3DTEXTURE9 texture) {
	// mario move left
	sprites->Add(10001, 246, 154, 260, 181, texture);
	sprites->Add(10002, 275, 154, 290, 181, texture);
	sprites->Add(10003, 304, 154, 321, 181, texture);

	// mario move right
	sprites->Add(10011, 186, 154, 200, 181, texture);
	sprites->Add(10012, 155, 154, 170, 181, texture);
	sprites->Add(10013, 125, 154, 140, 181, texture);

	// mario move up
	sprites->Add(10021, 215, 194, 232, 222, texture);
	sprites->Add(10022, 92, 275, 111, 300, texture);
	sprites->Add(10023, 335, 275, 351, 300, texture);

	// mario move down
	sprites->Add(10031, 215, 154, 231, 181, texture);
	sprites->Add(10032, 215, 234, 231, 251, texture);
}

void Add_mario_animations() {
	LPANIMATION lpani;

	// 0 - 9
	lpani = new CAnimation(10);
	lpani->Add(10001);
	animations->Add(400, lpani);

	// 10 - 19
	lpani = new CAnimation(10);
	lpani->Add(10011);
	animations->Add(401, lpani);

	// 20 - 29
	lpani = new CAnimation(10);
	lpani->Add(10021);
	animations->Add(402, lpani);

	// 30 - 39
	lpani = new CAnimation(10);
	lpani->Add(10031);
	animations->Add(403, lpani);
	
	// 40 - 49
	lpani = new CAnimation(10);
	lpani->Add(10001);
	lpani->Add(10002);
	lpani->Add(10003);
	animations->Add(500, lpani);

	// 50 - 59
	lpani = new CAnimation(10);
	lpani->Add(10011);
	lpani->Add(10012);
	lpani->Add(10013);
	animations->Add(501, lpani);

	// 60 - 69
	lpani = new CAnimation(10);
	lpani->Add(10021);
	lpani->Add(10022);
	lpani->Add(10023);
	animations->Add(502, lpani);

	// 70 - 79
	lpani = new CAnimation(10);
	lpani->Add(10031);
	lpani->Add(10032);
	animations->Add(503, lpani);
}

//void Add_npc_animations() {
//	LPANIMATION lpani;
//	// 80 - 89
//	lpani = new CAnimation(10);
//	lpani->Add(10001);
//	lpani->Add(10002);
//	lpani->Add(10003);
//	animations->Add(600, lpani);
//
//	// 90 - 99
//	lpani = new CAnimation(10);
//	lpani->Add(10011);
//	lpani->Add(10012);
//	lpani->Add(10013);
//	animations->Add(601, lpani);
//
//	// 100 - 109
//	lpani = new CAnimation(10);
//	lpani->Add(10021);
//	lpani->Add(10022);
//	lpani->Add(10023);
//	animations->Add(602, lpani);
//
//	// 110 - 119
//	lpani = new CAnimation(10);
//	lpani->Add(10031);
//	lpani->Add(10032);
//	animations->Add(603, lpani);
//}

#include"main.h"
#include"renderer.h"
#include"gametexturemanager.h"
#include"textureload.h"
#include"Loading.h"
#include"title.h"
#include"game.h"
//ローディングテクスチャ
//TextureLoad* texture_N = new TextureLoad;
//TextureLoad* texture_O = new TextureLoad;
//TextureLoad* texture_W = new TextureLoad;
//TextureLoad* texture_L = new TextureLoad;
//TextureLoad* texture_O2 = new TextureLoad;
//TextureLoad* texture_D = new TextureLoad;
//TextureLoad* texture_I = new TextureLoad;
//TextureLoad* texture_N2 = new TextureLoad;
//TextureLoad* texture_G = new TextureLoad;


//ゲームUI
TextureLoad* texture_Dragon = new TextureLoad;
TextureLoad* texture_Clock = new TextureLoad;
TextureLoad* texture_TimeLimit = new TextureLoad;
TextureLoad* texture_TimeHand = new TextureLoad;
TextureLoad* texture_GageBase = new TextureLoad;

void GameTexture::Init()
{

	//ローディングテクスチャ
	/*if()
	texture_N->Init("asset/texture/LoadTexture/N.png");
	texture_O->Init("asset/texture/LoadTexture/O.png");
	texture_W->Init("asset/texture/LoadTexture/W.png");
	texture_L->Init("asset/texture/LoadTexture/L.png");
	texture_O2->Init("asset/texture/LoadTexture/O.png");
	texture_D->Init("asset/texture/LoadTexture/D.png");
	texture_I->Init("asset/texture/LoadTexture/I.png");
	texture_N2->Init("asset/texture/LoadTexture/N.png");
	texture_G->Init("asset/texture/LoadTexture/G.png");*/
	//ゲームUI
	texture_Dragon->Init("asset/texture/UI/dragonUI.png");
	texture_Clock->Init("asset/texture/UI/clock.png");
	texture_TimeLimit->Init("asset/texture/UI/ClockHandLimit2.png");
	texture_TimeHand->Init("asset/texture/UI/ClockHand2.png");
	texture_GageBase->Init("asset/texture/UI/gagebase.png");
}

void GameTexture::Uninit()
{
	/*delete texture_N;
	delete texture_O;
	delete texture_W;
	delete texture_L;
	delete texture_O2;
	delete texture_D;
	delete texture_I;
	delete texture_N2;
	delete texture_G;*/


}

void GameTexture::Update()
{
	
}

void GameTexture::Draw()
{
	////ローディングテクスチャ
	//texture_N->Draw(430, 400);
	//texture_O->Draw(480, 400);
	//texture_W->Draw(530, 400);
	//texture_L->Draw(600, 400);
	//texture_O2->Draw(650, 400);
	//texture_D->Draw(700, 400);
	//texture_I->Draw(750, 400);
	//texture_N2->Draw(800, 400);
	//texture_G->Draw(850, 400);


	//ゲームUI
	texture_Dragon->SetTextureScale(180.0f, 180.0f);
	texture_Dragon->Draw(0.0f,0.0f);

	texture_Clock->SetTextureScale(150.0f,150.0f);
	texture_Clock->Draw(5.0f, 8.0f);
	
	texture_TimeLimit->SetTextureScale(150.0f, 150.0f);
	texture_TimeLimit->Draw(5.0f, 8.0f);
	texture_TimeLimit->SetOffset(33.0f, -105.0f);
	texture_TimeLimit->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 1.0f));

	texture_TimeHand->SetTextureScale(150.0f, 150.0f);
	texture_TimeHand->Draw(5.0f, 8.0f);
	texture_TimeHand->SetOffset(0.0f, 0.0f);
	
	
	texture_GageBase->SetTextureScale(800.0f, 50.0f);
	texture_GageBase->Draw(80.0f, 5.0f);
	
}

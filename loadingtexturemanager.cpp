#include"main.h"
#include"renderer.h"
#include"loadingtexturemanager.h"
#include"textureload.h"
TextureLoad* texture_N = new TextureLoad;
TextureLoad* texture_O = new TextureLoad;
TextureLoad* texture_W = new TextureLoad;

TextureLoad* texture_L = new TextureLoad;
TextureLoad* texture_O2 = new TextureLoad;
TextureLoad* texture_D = new TextureLoad;
TextureLoad* texture_I = new TextureLoad;
TextureLoad* texture_N2 = new TextureLoad;
TextureLoad* texture_G = new TextureLoad;

TextureLoad* texture_Load = new TextureLoad;

void LoadingTexture::Init()
{
	texture_N->Init("asset/texture/LoadTexture/N.png");	
	texture_O->Init("asset/texture/LoadTexture/O.png");
	texture_W->Init("asset/texture/LoadTexture/W.png");
	texture_L->Init("asset/texture/LoadTexture/L.png");
	texture_O2->Init("asset/texture/LoadTexture/O.png");
	texture_D->Init("asset/texture/LoadTexture/D.png");
	texture_I->Init("asset/texture/LoadTexture/I.png");
	texture_N2->Init("asset/texture/LoadTexture/N.png");
	texture_G->Init("asset/texture/LoadTexture/G.png");

	texture_Load->Init("asset/texture/LoadTexture/loadUI.png");
	texture_Load->SetTextureScale(1000.0f, 200.0f);
}

void LoadingTexture::Uninit()
{
	texture_N->Uninit();
	texture_O->Uninit();
	texture_W->Uninit();
	texture_L->Uninit();
	texture_O2->Uninit();
	texture_D->Uninit();
	texture_I->Uninit();
	texture_N2->Uninit();
	texture_G->Uninit();

	texture_Load->Uninit();

	
}

void LoadingTexture::Update()
{
	
	texture_N->TextureFlashing(90,0.01f);
	texture_O->TextureFlashing(90, 0.01f);
	texture_W->TextureFlashing(90, 0.01f);
	texture_L->TextureFlashing(90, 0.01f);
	texture_O2->TextureFlashing(90, 0.01f);
	texture_D->TextureFlashing(90, 0.01f);
	texture_I->TextureFlashing(90, 0.01f);
	texture_N2->TextureFlashing(90, 0.01f);
	texture_G->TextureFlashing(90, 0.01f);
}

void LoadingTexture::Draw()
{
	texture_N->Draw(430, 400);
	texture_O->Draw(480, 400);
	texture_W->Draw(530, 400);
	texture_L->Draw(600, 400);
	texture_O2->Draw(650, 400);
	texture_D->Draw(700, 400);
	texture_I->Draw(750, 400);
	texture_N2->Draw(800, 400);
	texture_G->Draw(850, 400);

	texture_Load->Draw(250,200);
}

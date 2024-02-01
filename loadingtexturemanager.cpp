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
}

void LoadingTexture::Uninit()
{
	
}

void LoadingTexture::Update()
{
	
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
}

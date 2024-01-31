#include"main.h"
#include"renderer.h"
#include"loadingtexture.h"
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
	texture_N->SetTexturePostion(50, 100);
	texture_O->Init("asset/texture/LoadTexture/O.png");
	texture_O->SetTexturePostion(100, 100);
	texture_W->Init("asset/texture/LoadTexture/W.png");
	texture_W->SetTexturePostion(150, 100);
	texture_L->Init("asset/texture/LoadTexture/L.png");
	texture_L->SetTexturePostion(200, 100);
	texture_O2->Init("asset/texture/LoadTexture/O.png");
	texture_O2->SetTexturePostion(250, 100);
	texture_D->Init("asset/texture/LoadTexture/D.png");
	texture_D->SetTexturePostion(300, 100);
	texture_I->Init("asset/texture/LoadTexture/I.png");
	texture_I->SetTexturePostion(350, 100);
	texture_N2->Init("asset/texture/LoadTexture/N.png");
	texture_N2->SetTexturePostion(400, 100);
	texture_G->Init("asset/texture/LoadTexture/G.png");
	texture_G->SetTexturePostion(450, 100);
}

void LoadingTexture::Uninit()
{
	
}

void LoadingTexture::Update()
{
	
}

void LoadingTexture::Draw()
{
	texture_N->Draw();
	texture_O->Draw();
	texture_W->Draw();
	texture_L->Draw();
	texture_O2->Draw();
	texture_D->Draw();
	texture_I->Draw();
	texture_N2->Draw();
	texture_G->Draw();
}

#include"main.h"
#include"renderer.h"
#include"scene.h"
#include"manager.h"
#include"resulttexturemanager.h"
#include"textureload.h"

TextureLoad* texture_ThanksLogo = new TextureLoad;

void ResultTexture::Init()
{
	texture_ThanksLogo->Init("asset/texture/UI/ResultThanksTexture.png");
	texture_ThanksLogo->SetTextureScale(SCREEN_WIDTH, SCREEN_HEIGHT);
}

void ResultTexture::Uninit()
{
	texture_ThanksLogo->SetDestroy();
}

void ResultTexture::Update()
{

}

void ResultTexture::Draw()
{
	texture_ThanksLogo->Draw(0.0f,0.0f);
}
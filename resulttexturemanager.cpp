#include"main.h"
#include"renderer.h"
#include"scene.h"
#include"manager.h"
#include"resulttexturemanager.h"
#include"textureload.h"

TextureLoad* texture_ThanksLogo = new TextureLoad;
TextureLoad* texture_ButtonUI = new TextureLoad;

void ResultTexture::Init()
{
	texture_ThanksLogo->Init("asset/texture/UI/ResultThanksTexture.png");
	texture_ThanksLogo->SetTextureScale(SCREEN_WIDTH, SCREEN_HEIGHT);
	texture_ButtonUI->Init("asset/texture/UI/PushSpacetoB2.png");
	texture_ButtonUI->SetTextureScale(950.0f, 120.0f);
}

void ResultTexture::Uninit()
{
	texture_ThanksLogo->SetDestroy();
	texture_ButtonUI->SetDestroy();
}

void ResultTexture::Update()
{
	texture_ButtonUI->TextureFlashing(90, 0.01f);
}

void ResultTexture::Draw()
{
	texture_ThanksLogo->Draw(0.0f,0.0f);
	texture_ButtonUI->Draw(550.0f, 420.0f);
}
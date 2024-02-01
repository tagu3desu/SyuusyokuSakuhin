#include"main.h"
#include"renderer.h"
#include"gametexturemanager.h"
#include"textureload.h"

TextureLoad* texture_Dragon = new TextureLoad;
TextureLoad* texture_Clock = new TextureLoad;
TextureLoad* texture_TimeLimit = new TextureLoad;
TextureLoad* texture_TimeHand = new TextureLoad;
TextureLoad* texture_GageBase = new TextureLoad;

void GameTexture::Init()
{
	texture_Dragon->Init("asset/texture/UI/dragonUI.png");
	texture_Clock->Init("asset/texture/UI/clock.png");
	texture_TimeLimit->Init("asset/texture/UI/ClockHandLimitBeta.png");
	texture_TimeHand->Init("asset/texture/UI/ClockHand.png");
	texture_GageBase->Init("asset/texture/UI/gagebase.png");
}

void GameTexture::Uninit()
{
	
}

void GameTexture::Update()
{
	
}

void GameTexture::Draw()
{
	texture_Dragon->SetTextureScale(180.0f, 180.0f);
	texture_Dragon->Draw(0.0f,0.0f);

	texture_Clock->SetTextureScale(150.0f,150.0f);
	texture_Clock->Draw(5.0f, 8.0f);
	
	texture_TimeLimit->SetTextureScale(40.0f, 40.0f);
	texture_TimeLimit->Draw(40.0f, 30.0f);

	texture_TimeHand->SetTextureScale(30.0f, 70.0f);
	texture_TimeHand->Draw(35.0f, 15.0f);
	
	texture_GageBase->SetTextureScale(800.0f, 50.0f);
	texture_GageBase->Draw(80.0f, 5.0f);
	
}

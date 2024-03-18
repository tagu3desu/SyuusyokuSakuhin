#include"main.h"
#include"renderer.h"
#include"scene.h"
#include"manager.h"
#include"resulttexturemanager.h"
#include"textureload.h"
#include"clearrank.h"

TextureLoad* texture_ThanksLogo = new TextureLoad;
TextureLoad* texture_TimeBG = new TextureLoad;
TextureLoad* texture_ButtonUI = new TextureLoad;
TextureLoad* texture_MinPeriod = new TextureLoad;
TextureLoad* texture_SecondPeriod = new TextureLoad;

void ResultTexture::Init()
{
	Scene* scene = Manager::GetScene();
	

	texture_ThanksLogo->Init("asset/texture/UI/ResultThanksTexture2.png");
	texture_ThanksLogo->SetTextureScale(SCREEN_WIDTH, SCREEN_HEIGHT);
	texture_ButtonUI->Init("asset/texture/UI/PushSpacetoB.png");
	texture_ButtonUI->SetTextureScale(950.0f, 120.0f);

	texture_TimeBG->Init("asset/texture/UI/TimeBG.png");
	texture_TimeBG->SetTextureScale(920.0f, 140.0f);
	texture_MinPeriod->Init("asset/texture/UI/TimePeriod.png");
	texture_SecondPeriod->Init("asset/texture/UI/TimePeriod.png");
	
	
	
	
}

void ResultTexture::Uninit()
{
	texture_ThanksLogo->SetDestroy();
	texture_ButtonUI->SetDestroy();

	
	texture_TimeBG->SetDestroy();
	texture_MinPeriod->SetDestroy();
	texture_SecondPeriod->SetDestroy();
	
	
	
}

void ResultTexture::Update()
{
	texture_ButtonUI->TextureFlashing(90, 0.01f);
}

void ResultTexture::Draw()
{
	

	texture_ThanksLogo->Draw(0.0f,0.0f);
	texture_ButtonUI->Draw(550.0f, 420.0f);

	
	texture_TimeBG->Draw(235.0f, 325.0f);
	texture_MinPeriod->Draw(465.0f, 335.0f);
	texture_SecondPeriod->Draw(425.0f, 335.0f);
	
	
	
	
}
#include"main.h"
#include"renderer.h"
#include"gametexturemanager.h"
#include"textureload.h"
#include"Loading.h"
#include"title.h"
#include"game.h"



//ƒQ[ƒ€UI
TextureLoad* texture_Dragon = new TextureLoad;
TextureLoad* texture_Clock = new TextureLoad;
TextureLoad* texture_TimeLimit = new TextureLoad;
TextureLoad* texture_TimeHand = new TextureLoad;
TextureLoad* texture_GageBase = new TextureLoad;
TextureLoad* texture_TimelimitUI = new TextureLoad;


void GameTexture::Init()
{
	texture_Dragon->Init("asset/texture/UI/dragonUI.png");
	texture_Clock->Init("asset/texture/UI/clock.png");
	texture_TimeLimit->Init("asset/texture/UI/ClockHandLimit2.png");
	texture_TimeHand->Init("asset/texture/UI/ClockHand2.png");
	texture_GageBase->Init("asset/texture/UI/gagebase.png");
	texture_TimelimitUI->Init("asset/texture/UI/timelimit.png");
}

void GameTexture::Uninit()
{
	delete texture_Dragon;
	delete texture_Clock;
	delete texture_TimeLimit;
	delete texture_TimeHand;
	delete texture_GageBase;
}

void GameTexture::Update()
{
	
	ImGui::SetNextWindowSize(ImVec2(300, 250));
	ImGui::Begin("Texture");
	ImGui::InputFloat("frame", &m_Framwait);
	ImGui::End();

	m_y = texture_TimelimitUI->UiMove(160, texture_TimelimitUI);


}

void GameTexture::Draw()
{
	
	//ƒQ[ƒ€UI
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

	texture_TimelimitUI->SetTextureScale(300.0f, 80.0f);
	texture_TimelimitUI->Draw(400.0f, m_y);
	
}

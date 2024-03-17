#include"main.h"
#include"renderer.h"
#include"manager.h"
#include"title.h"
#include"polygon2D.h"
#include"input.h"
#include"scene.h"
#include"result.h"
#include"resulttexturemanager.h"
#include"inputx.h"
#include"timenumber.h"
#include"timer.h"
#include"timer.h"
#include"clearrank.h"
void Result::Init()
{
	Scene* scene = Manager::GetScene();

	ResultTexture* resulttexture = AddGameObject<ResultTexture>(SPRITE_LAYER);
	ClockTimeHand* cleartime = GetGameObject<ClockTimeHand>();

	TimeCount* minTime = AddGameObject<TimeCount>(SPRITE_LAYER); //ï™1
	minTime->SetCount(cleartime->GetTimeMin());
	minTime->SetTexturePostion(850.0f, 683.0f);

	TimeCount* secondTime = AddGameObject<TimeCount>(SPRITE_LAYER);	//ïb
	secondTime->SetCount(cleartime->GetTimeSecond());
	secondTime->SetTexturePostion(930.0f, 683.0f);

	TimeCount* milliSecondTime  = AddGameObject<TimeCount>(SPRITE_LAYER);	//É~Éäïb
	milliSecondTime->SetCount(cleartime->GetTimeMilliSecond());
	milliSecondTime->SetTexturePostion(1015.0f, 683.0f);

	ClearRank* clearrank = AddGameObject<ClearRank>(SPRITE_LAYER);
	//clearrank->SetRank(cleartime->GetRank());
	clearrank->SetTexturePostion(1150.0f, 635.0f);
}




void Result::Update()
{
	Scene::Update();

	//ÉLÅ[ì¸óÕÇ≈ÉQÅ[ÉÄâÊñ Ç…ëJà⁄
	if (Input::GetKeyTrigger(VK_SPACE) || InputX::IsButtonTriggered(0,XINPUT_GAMEPAD_B))
	{
		Manager::SetScene<Title>();
	}
}




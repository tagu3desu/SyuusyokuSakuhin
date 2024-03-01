#include"main.h"
#include"renderer.h"
#include"manager.h"
#include"Loading.h"
#include"polygon2D.h"
#include"input.h"
#include"scene.h"
#include"game.h"
#include"tutorial.h"
#include"fade.h"
#include"loadingtexturemanager.h"
#include<thread>
#include"textureload.h"


bool Loading::m_GameLoad = false;
bool Loading::m_TutorialLoad = false;

void Loading::Init()
{
	AddGameObject<LoadingTexture>(SPRITE_LAYER);
	if (m_GameLoad)
	{
		std::thread th(&Game::Load);
		th.detach();
	}
	if (m_TutorialLoad)
	{
		std::thread th(&Tutorial::Load);
		th.detach();
	}
}


void Loading::Update()
{
	Scene::Update();
	
	

	//キー入力でゲーム画面に遷移
	if (Game::GetLoadFinish()) //Enterキー
	{
		Manager::SetScene<Game>();
	} 
	if (Tutorial::GetLoadFinish())
	{
		Manager::SetScene<Tutorial>();
	}
	
}



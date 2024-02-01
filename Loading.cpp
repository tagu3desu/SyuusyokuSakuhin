#include"main.h"
#include"renderer.h"
#include"manager.h"
#include"Loading.h"
#include"polygon2D.h"
#include"input.h"
#include"scene.h"
#include"game.h"
#include"fade.h"
#include"LoadingLogo.h"
#include"loadingtexturemanager.h"
#include<thread>
#include"textureload.h"

void Loading::Init()
{
	AddGameObject<LoadingLogo>(SPRITE_LAYER);
	AddGameObject<LoadingTexture>(SPRITE_LAYER);
	std::thread th(&Game::Load);
	th.detach();
}


void Loading::Update()
{
	Scene::Update();
	
	m_MouseposX = GetMouseCursorPosXinWnd();
	m_MouseposY = GetMouseCursorPosYinWnd();


	//�L�[���͂ŃQ�[����ʂɑJ��
	if (Game::GetLoadFinish()) //Enter�L�[
	{
		Manager::SetScene<Game>();
	} 
	
}



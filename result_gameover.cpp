#include"main.h"
#include"renderer.h"
#include"manager.h"
#include"title.h"
#include"polygon2D.h"
#include"input.h"
#include"scene.h"
#include"result_gameover.h"

void GameOver::Init()
{
	AddGameObject<Polygon2D>(SPRITE_LAYER);

}


void GameOver::Update()
{
	Scene::Update();

	//�L�[���͂ŃQ�[����ʂɑJ��
	if (Input::GetKeyTrigger(VK_RETURN))//Enter�L�[
	{
		Manager::SetScene<Title>();

	}
}



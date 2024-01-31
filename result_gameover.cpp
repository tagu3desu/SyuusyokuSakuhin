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

	//キー入力でゲーム画面に遷移
	if (Input::GetKeyTrigger(VK_RETURN))//Enterキー
	{
		Manager::SetScene<Title>();

	}
}



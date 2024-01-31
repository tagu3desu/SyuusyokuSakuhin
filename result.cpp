#include"main.h"
#include"renderer.h"
#include"manager.h"
#include"title.h"
#include"polygon2D.h"
#include"input.h"
#include"scene.h"
#include"result.h"

void Result::Init()
{
	AddGameObject<Polygon2D>(SPRITE_LAYER);

}


void Result::Update()
{
	Scene::Update();

	//キー入力でゲーム画面に遷移
	if (Input::GetKeyTrigger(VK_RETURN))//Enterキー
	{
		Manager::SetScene<Title>();

	}
}



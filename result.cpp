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

	//�L�[���͂ŃQ�[����ʂɑJ��
	if (Input::GetKeyTrigger(VK_RETURN))//Enter�L�[
	{
		Manager::SetScene<Title>();

	}
}



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




void Result::Init()
{
	Scene* scene = Manager::GetScene();

	ResultTexture* resulttexture = AddGameObject<ResultTexture>(SPRITE_LAYER);
}




void Result::Update()
{
	Scene::Update();

	//�L�[���͂ŃQ�[����ʂɑJ��
	if (Input::GetKeyTrigger(VK_RETURN) || InputX::IsButtonTriggered(0,XINPUT_GAMEPAD_B))//Enter�L�[
	{
		Manager::SetScene<Title>();
	}
}




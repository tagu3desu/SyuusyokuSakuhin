#include"main.h"
#include"renderer.h"
#include"manager.h"
#include"title.h"


#include"camera.h"
#include"floar.h"
#include"watersurface.h"
#include"door.h"
#include"doorframe.h"


#include"meshField.h"
#include"polygon2D.h"
#include"input.h"
#include"scene.h"
#include"game.h"
#include"titleLogo.h"
#include"fade.h"
#include"titlebutton.h"
#include"Loading.h"
#include"sky.h"
#include"cylinder.h"

#include"player.h"
#include"field.h"
#include"wepon_sword.h"
#include"wepon_shield.h"

#include"wood.h"
#include"treeobj.h"
#include"titletexturemanager.h"
#include"rock.h"
bool Title::m_TitleCheck = false;
bool Title::menucontrol = false;

void Title::Init()
{
	

	Scene::Init();
	m_framecount = 0;
	m_FloarPosition = 0;
	m_TitleCheck = true;

	//�J����
	Camera* camera = AddGameObject<Camera>(CAMERA_LAYER);

	Sky* skydome = AddGameObject<Sky>();
	skydome->SetScale(D3DXVECTOR3(300.0f, 300.0f, 300.0f));

	Field* meshfield = AddGameObject<Field>();
	
	Player* player = AddGameObject<Player>();
	player->SetRotation(D3DXVECTOR3(0.0f, -2.4f, 0.0f));
	AddGameObject<Sword>();
	AddGameObject<Shield>();

	Wood* wood =AddGameObject<Wood>();
	wood->SetPosition(D3DXVECTOR3(-0.3f, 0.3f, 0.0f));
	wood->SetRotation(D3DXVECTOR3(0.0f, -0.9f, 0.0f));


	AddGameObject<TitleTexture>(SPRITE_LAYER);
	m_Fade = AddGameObject<Fade>(SPRITE_LAYER);
	buttonOverLapping = false;
	int num = 0;
}


void Title::Update()
{
	Scene::Update();
	
	Scene* scene = Manager::GetScene();

	//m_MouseposX = GetMouseCursorPosXinWnd();
	//m_MouseposY = GetMouseCursorPosYinWnd();

	//ImGui::Begin("Mouse");
	//ImGui::InputFloat3("PositionX", &m_MouseposX);
	//ImGui::InputFloat3("PositionY", &m_MouseposY);
	//ImGui::End();

	//if (430 <= m_MouseposX && m_MouseposX<= 930 && 425 <= m_MouseposY&& m_MouseposY <= 515)
	//{
	//	buttonOverLapping = true;
	//}
	//else
	//{
	//	buttonOverLapping = false;
	//}

	
	//�L�[���͂ŃQ�[����ʂɑJ��
	if (Input::GetKeyTrigger(VK_SPACE)  && menucontrol ||  Input::GetKeyTrigger(VK_LBUTTON) && buttonOverLapping && menucontrol) //Enter�L�[
	{
		m_Fade->FadeOut();
	} 
	if (m_Fade->GetFadeFinish())
	{
		m_TitleCheck = false;
	
		Manager::SetScene<Loading>();
	}

	//�ŏ��̉�ʂ���I����ʂ�
	if (Input::GetKeyTrigger(VK_SPACE) && !menucontrol || Input::GetKeyTrigger(VK_LBUTTON) && !menucontrol )
	{
		menucontrol = true;
	}

	


}

void Title::Uninit()
{
	
	Scene::Uninit();

	
}

void Title::Draw()
{
	
	Scene* scene = Manager::GetScene();
	D3DXVECTOR3 objpos;
	Field* player= GetGameObject<Field>();
	objpos = player->GetPosition();

	//���C�g�J�����\���̂̏�����
	LIGHT light;
	light.Enable = true;
	light.Direction = D3DXVECTOR4(1.0f, -1.0f, 1.0f, 0.0f);	//����
	D3DXVec4Normalize(&light.Direction, &light.Direction);
	light.Ambient = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);	//�����̐F
	light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//�g�U���̐F

	//���C�g�J�����̃r���[�s����쐬
	D3DXVECTOR3 lightPos = D3DXVECTOR3(-50.0f + objpos.x, 100.0f, -50.0f + objpos.z);
	D3DXVECTOR3 lightTarget = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 lightUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&light.ViewMatrix, &lightPos, &lightTarget, &lightUp);
	//���C�g�J�����̃v���W�F�N�V�����s����쐬(�}�g���b�N�X,����p,�A�X�y�N�g��,�j�A�N���b�v,�t�@�[�N���b�v(�`�拗��))
	D3DXMatrixPerspectiveFovLH(&light.ProjectionMatrix, 1.0f, (float)1.0f, 35.0f, 400.0f);
	Renderer::SetLight(light);

	//** 1�p�X�� �V���h�E�o�b�t�@�̍쐬 **//
	Renderer::BeginDepth();
	Renderer::SetDepthViewport();

	//���C�g�J�����̍s����Z�b�g
	Renderer::SetViewMatrix(&light.ViewMatrix);
	Renderer::SetProjectionMatrix(&light.ProjectionMatrix);

	//�e�𗎂Ƃ������I�u�W�F�N�g�̕`��
	Scene::DepthDraw();

	//2�p�X�ځ@�ʏ�̍쐬
	Renderer::Begin();

	Renderer::SetDefaultViewport();

	//�{���̃J����&�v���W�F�N�V�����s����Z�b�g


	light.Enable = false;
	Renderer::SetLight(light);
	Scene::Draw();
}



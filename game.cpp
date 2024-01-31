#include"main.h"
#include"manager.h"
#include"renderer.h"
#include"game.h"
#include "polygon2D.h"
#include "field.h"
#include"camera.h"
#include"player.h"	
#include"enemy.h"
#include"Cylinder.h"
#include"bullet.h"
#include"explosion.h"
#include"box.h"
#include"result.h"
#include"input.h"
#include"score.h"
#include"audio.h"
#include"sky.h"
#include"fade.h"
#include"child.h"
#include"meshField.h"
#include"rock.h"
#include"treetexture.h"
#include"playerHPGage.h"
#include"potion.h"
#include"enemy2.h"
#include"collider.h"
#include"animationModel.h"
#include"collisionHit.h"
#include"torus.h"
#include"hpgage.h"
#include"staminagage.h"
#include"healItem.h"
#include"potioncount.h"
#include"wepon_sword.h"
#include"swordtrail.h"
#include"wepon_gun.h"
#include"wepon_galbert.h"
#include"wepon_shield.h"
#include"treeobj.h"
#include"howleffect.h"
#include"watersurface.h"
#include"wepon_axe.h"
#include"collider.h"
#include"trailtexture.h"
#include"trail.h"

Torus* torus;
Player* player;

bool Game::m_LoadFinish = false;

void Game::Load()
{
	Bullet::Load();
	Enemy::Load();
	//Enemy2::Load();
	Child::Load();
	Rock::Load();
	TreeTexture::Load();
	HowlEffect::Load();
	TrailTexture::Load();

	m_LoadFinish = true;
}

void Game::Unload()
{
	m_LoadFinish = false;

	Bullet::Unload();
	Enemy::Unload();
	//Enemy2::Unload();
	Child::Unload();
	Rock::Unload();
	TreeTexture::Unload();
	HowlEffect::Unload();
	TrailTexture::Unload();

}

void Game::Init()
{
	
	
	//�J����
	Camera* camera = AddGameObject<Camera>(CAMERA_LAYER);
	//�X�J�C�h�[��
	Sky*  skydome = AddGameObject<Sky>();
	skydome->SetScale(D3DXVECTOR3(300.0f,300.0f,300.0f));

	//�t�B�[���h�֘A
	//field = AddGameObject<Field>(1);
	MeshField*  meshfield = AddGameObject<MeshField>();

	
	//WaterSurFace* watersurface = AddGameObject<WaterSurFace>();
	//watersurface->SetPosition(D3DXVECTOR3(0.0f, -1.3f, 0.0f));

	//TreeOBJ* treeobj = AddGameObject<TreeOBJ>();
	//treeobj->SetPosition(D3DXVECTOR3(0.0f, 0.0f, -1.0f));

	player =  AddGameObject<Player>();
	player->SetPosition(D3DXVECTOR3(-1.0f,0.0f, -4.0f));

	//Gun* gun = AddGameObject<Gun>();
	Sword*sword =AddGameObject<Sword>();
	Shield* shield = AddGameObject<Shield>();

	//Axe* axe = AddGameObject<Axe>();
	// 
	// 
	//Galbert* galbert = AddGameObject<Galbert>();
	/*SwordTrail* swordtrial = AddGameObject<SwordTrail>();
	D3DXVECTOR3 pos = sword->GetPosition();
	swordtrial->SetPosition(pos);*/

	//AddGameObject<Child>()->SetParent(player);

	/*collider = AddGameObject<Collider>(COLLIDER_LAYER);
	collider->SetScale(D3DXVECTOR3(30.0f, 30.0f, 30.0f));
	collider->m_collisionSize = 0.1f;
	collider->gameObject = player;
	collider->boneMatrix = Collider::MatrixConvert(player->m_Model->GetBone("mixamorig:Spine")->WorldMatrix);
	collider->boneEnable = true;*/

	Enemy* enemy = AddGameObject<Enemy>();
	enemy->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 15.0f));
	
	TrailTexture* trailtexture = AddGameObject<TrailTexture>();


	/*if (!getvertex)
	{
		
		getvertex = true;
	}*/
	
	//trailtexture->SetPosition(D3DXVECTOR3(0.0f, 2.0f, 0.0f));

	/*
	Trail* trail = AddGameObject<Trail>();
	trail->SetPosition(D3DXVECTOR3(0.0f,2.0f,0.0f));
	*/

	AddGameObject<Trail>();


	AddGameObject<HPgage>(SPRITE_LAYER);
	AddGameObject<Staminagage>(SPRITE_LAYER);

	AddGameObject<Potion>(SPRITE_LAYER);
	AddGameObject<PotionCount>(SPRITE_LAYER);

	//AddGameObject<GuardEffect>(EFFECT_LAYER);

	//AddGameObject<Grass>();
	

	/*collider2 = AddGameObject<Collider>(COLLIDER_LAYER);
	collider2->SetScale(D3DXVECTOR3(30.0f, 30.0f, 30.0f));
	collider2->m_collisionSize = 0.1f;
	collider2->gameObject = enemy;
	collider2->boneMatrix = Collider::MatrixConvert(enemy->m_Model->GetBone("mixamorig:LeftHand")->WorldMatrix);
	collider2->boneEnable = true;*/

	Box* box = AddGameObject<Box>();
	box->SetScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	box->SetPosition(D3DXVECTOR3(8.0f, 0.0f, 2.0f));

	
	


	//Collider* collider = AddGameObject<Collider>();
	

	//sword->SetScale(D3DXVECTOR3(0.3f, 0.3f, 0.3f));
	//sword->SetPosition(D3DXVECTOR3(8.0f, 2.0f, -10.0f));
	
	/*Enemy2* enemy2;
	enemy2 = AddGameObject<Enemy2>();
	enemy2->SetPosition(D3DXVECTOR3(-5.0f, 0.0f, 5.0f));*/



	/*auto* collider = AddGameObject<Collider>(1);
	collider->SetScale(D3DXVECTOR3(0.5f, 0.5f, 0.5f));
	collider->SetPosition(D3DXVECTOR3(0.0f, 2.0f, 0.0f));*/


	/*AddGameObject<Enemy>(1)->SetPosition(D3DXVECTOR3(-4.0f,1.0f, 5.0f));
	AddGameObject<Enemy>(1)->SetPosition(D3DXVECTOR3(4.0f, 1.0f, 5.0f));*/

	/*torus = AddGameObject<Torus>();
	torus->SetPosition(D3DXVECTOR3(0.0f, 1.0f, 2.0f));
	torus->SetScale(D3DXVECTOR3(5.0f, 5.0f, 5.0f));*/


	Cylinder* cylinder=AddGameObject<Cylinder>();
	cylinder->SetPosition(D3DXVECTOR3(-10.0f, 0.0f, 10.0f));
	cylinder->SetScale(D3DXVECTOR3(3.0f, 2.0f, 3.0f));

	/*Box* box = AddGameObject<Box>(1);
	box->SetPosition(D3DXVECTOR3(4.0f, 2.0f, 4.0f));
	box->SetScale(D3DXVECTOR3(2.0f, 1.0f, 2.0f));*/

	//AddGameObject<Score>(2);

	
	//AddGameObject<PlayerHPGage>(SPRITE_LAYER);

	m_Fade = AddGameObject<Fade>(SPRITE_LAYER);
	//AddGameObject<Polygon2D>(2);
	
	//AddGameObject<Tree>(2);

	//auto rock = AddGameObject<Rock>();


	//��
	for (int i = 0; i < 20; i++)
	{
		auto tree = AddGameObject<TreeTexture>();

		D3DXVECTOR3 pos;
		pos.x = (float)rand() / RAND_MAX * 100.0f - 50.0f;
		pos.z = (float)rand() / RAND_MAX * 100.0f - 50.0f;
		//pos.y = meshfield->GetHeight(pos);
		pos.y = 0.0f;
		tree->SetPosition(pos);
	}

	////��
	for (int i = 0; i < 20; i++)
	{
		auto rock = AddGameObject<Rock>();

		D3DXVECTOR3 pos;
		pos.x = (float)rand() / RAND_MAX * 100.0f - 50.0f;
		pos.z = (float)rand() / RAND_MAX * 100.0f - 50.0f;
		//pos.y = meshField->GetHeight(pos);
		rock->SetPosition(pos);

		D3DXVECTOR3 scl;
		scl.x = scl.y = scl.z = (float)rand() / RAND_MAX * 1.0f + 1.0f;
		rock->SetScale(scl);
	}
	
	
}


void Game::Update()
{
	Scene::Update();
	Scene* scene = Manager::GetScene();
	Player* player = scene->GetGameObject<Player>();
	

	if (player->GetOverFlag())
	{
		m_Fade->FadeOut();
	}
	if (m_Fade->GetFadeFinish())
	{
		Manager::SetScene<Result>();
	}

	
	
	/*collider->boneMatrix = Collider::MatrixConvert(player->m_Model->GetBone("mixamorig:Spine")->WorldMatrix);
	collider2->boneMatrix = Collider::MatrixConvert(enemy->m_Model->GetBone("mixamorig:LeftHand")->WorldMatrix);*/

}

void Game::Uninit()
{
	Scene::Uninit();
	
	
}

void Game::Draw()
{
	Scene* scene = Manager::GetScene();
	D3DXVECTOR3 playerpos =	player->GetPosition();

	//���C�g�J�����\���̂̏�����
	LIGHT light;
	light.Enable = true;
	light.Direction = D3DXVECTOR4(1.0f, -1.0f, 1.0f, 0.0f);	//����
	D3DXVec4Normalize(&light.Direction, &light.Direction);
	light.Ambient = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);	//�����̐F
	light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//�g�U���̐F


	//���C�g�J�����̃r���[�s����쐬
	D3DXVECTOR3 lightPos = D3DXVECTOR3(-50.0f + playerpos.x, 20.0f , -50.0f  + playerpos.z);
	D3DXVECTOR3 lightTarget = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 lightUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&light.ViewMatrix, &lightPos, &lightTarget, &lightUp);
	//���C�g�J�����̃v���W�F�N�V�����s����쐬(�}�g���b�N�X,����p,�A�X�y�N�g��,�j�A�N���b�v,�t�@�[�N���b�v(�`�拗��))
	D3DXMatrixPerspectiveFovLH(&light.ProjectionMatrix, 1.0f,(float)1.0f, 10.0f, 300.0f);
	Renderer::SetLight(light);



	////�r���[�ϊ��s����쐬
	////�����_�I�t�Z�b�g�e�[�u��
	//D3DXVECTOR3 lookatOffset[6] = {
	//	{ 1.0f, 0.0f, 0.0f },//+X D3D11_TEXTURECUBE_FACE_POSITIVE_X
	//	{ -1.0f, 0.0f, 0.0f },//-X D3D11_TEXTURECUBE_FACE_NEGATIVE_X
	//	{ 0.0f, 1.0f, 0.0f },//+Y D3D11_TEXTURECUBE_FACE_POSITIVE_Y
	//	{ 0.0f, -1.0f, 0.0f },//-Y D3D11_TEXTURECUBE_FACE_NEGATIVE_Y
	//	{ 0.0f, 0.0f, 1.0f },//+Z D3D11_TEXTURECUBE_FACE_POSITIVE_Z
	//	{ 0.0f, 0.0f, -1.0f },//-Z D3D11_TEXTURECUBE_FACE_NEGATIVE_Z
	//};

	////up�x�N�g���e�[�u��
	//D3DXVECTOR3 upOffset[6]={
	//	{ 0.0f, 1.0f, 0.0f },
	//	{ 0.0f, 1.0f, 0.0f },
	//	{ 0.0f, 0.0f,-1.0f },
	//	{ 0.0f, 0.0f, 1.0f },
	//	{ 0.0f, 1.0f, 0.0f },
	//	{ 0.0f, 1.0f, 0.0f },
	//};

	//D3DXVECTOR3 eye;
	//D3DXVECTOR3 lookat;
	//D3DXVECTOR3 up;
	//D3DXMATRIX viewMatrixArray[6];
	//D3DXVECTOR3 cylinderPosition = torus->GetPosition();
	//for (int i = 0; i < 6; i++)
	//{
	//	eye = cylinderPosition;
	//	lookat = cylinderPosition + lookatOffset[i];
	//	up = -upOffset[i];
	//	D3DXMatrixLookAtLH(&viewMatrixArray[i], &eye, &lookat, &up);
	//}

	////�v���W�F�N�V�����}�g���b�N�X�ݒ�(���p)
	//D3DXMATRIX projectionMatrix;
	//D3DXMatrixPerspectiveFovLH(&projectionMatrix, D3DX_PI / 2, 1.0f, 0.01f, 10000.0f);
	//Renderer::SetProjectionMatrix(&projectionMatrix);

	////�r���[�|�[�g�ύX
	//Renderer::SetReflectViewport();
	//for (int i = 0; i < 6; i++)
	//{
	//	Renderer::BeginCube();
	//	//�r���[�ϊ��}�g���N�X
	//	Renderer::SetViewMatrix(&viewMatrixArray[i]);
	//	
	//	Scene::ReflectDraw();
	//	
	//	

	//	//�`�悵���e�N�X�`�����L���[�u�}�b�v�p�e�N�X�`���ɃR�s�[���Ă���
	//	Renderer::GetDeviceContext()->CopySubresourceRegion(
	//		Renderer::GetCubeReflectTexture(),
	//		D3D11CalcSubresource(0, i, 1),
	//		0, 0, 0, Renderer::GetReflectTexture(), 0, nullptr);
	//}


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
	

	/*CollisionHit::Update();*/
	//�Q�[����Draw�̂��ƃR���|�[�l���g��Draw
}
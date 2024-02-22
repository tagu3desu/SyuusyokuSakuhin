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
#include"bladeefect1.h"
#include"bladeefect2.h"
#include"box.h"
#include"result.h"
#include"input.h"
#include"score.h"
#include"audio.h"
#include"sky.h"
#include"fade.h"
#include"meshField.h"
#include"rock.h"
#include"treetexture.h"
#include"collider.h"
#include"animationModel.h"
#include"torus.h"
#include"hpgage.h"
#include"staminagage.h"
#include"healItem.h"
#include"itemcount.h"
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
#include"trail.h"
#include"gametexturemanager.h"
#include"collider.h"
#include"campField.h"
#include"rockeffect.h"
#include"basecamptent.h"
#include"treasurebox.h"
#include"dummy.h"
#include"debug.h"
#include"shieldefect.h"
#include"healefect.h"

Player* g_Player;

bool Game::m_LoadFinish = false;

void Game::Load()
{
	Bullet::Load();
	Enemy::Load();
	Rock::Load();
	TreeTexture::Load();
	HowlEffect::Load();
	BladeEffect1::Load();
	BladeEffect2::Load();
	SwordTopVertex::Load();
	MeshField::Load();
	Collider::Load();
	BaseCamp::Load();
	Box::Load();
	RockEffect::Load();
	BaceCampTent::Load();
	TreasureBox::Load();
	Dummy::Load();
	ShieldEffect::Load();
	HealEffect::Load();
	m_LoadFinish = true;
}

void Game::Unload()
{
	m_LoadFinish = false;

	Bullet::Unload();
	Enemy::Unload();
	Rock::Unload();
	TreeTexture::Unload();
	HowlEffect::Unload();
	BladeEffect1::Unload();
	BladeEffect2::Unload();
	SwordTopVertex::Unload();
	MeshField::Unload();
	Collider::Unload();
	BaseCamp::Unload();
	Box::Unload();
	RockEffect::Unload();
	BaceCampTent::Unload();
	TreasureBox::Unload();
	Dummy::Unload();
	ShieldEffect::Unload();
	HealEffect::Unload();
}

void Game::Init()
{
	
	
	//カメラ
	Camera* camera = AddGameObject<Camera>(CAMERA_LAYER);
	//スカイドーム
	Sky*  skydome = AddGameObject<Sky>();
	skydome->SetScale(D3DXVECTOR3(300.0f,300.0f,300.0f));

	//フィールド関連
	//Field* field = AddGameObject<Field>();
	MeshField*  meshfield = AddGameObject<MeshField>();
	meshfield->SetMapActive(true);

	

	AddGameObject<GameTexture>(SPRITE_LAYER);

	g_Player =  AddGameObject<Player>();
	g_Player->SetPosition(D3DXVECTOR3(-1,0,-20));
	
	
	Sword*sword =AddGameObject<Sword>();
	Shield* shield = AddGameObject<Shield>();
	

	Enemy* enemy = AddGameObject<Enemy>();
	enemy->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 25.0f));
	
	Box* box = AddGameObject<Box>();
	box->SetPosition(D3DXVECTOR3(7.0f,0.0f,0.0f));

	


	//AddGameObject<ItemCount>(SPRITE_LAYER);
	

	m_Fade = AddGameObject<Fade>(SPRITE_LAYER);

	AddGameObject<DebugSystem>();

	////////木
	{
		//for (int i = 0; i < 20; i++) 
	//{
	//	auto tree = AddGameObject<TreeTexture>();

	//	D3DXVECTOR3 pos;
	//	pos.x = (float)rand() / RAND_MAX * 100.0f - 50.0f;
	//	pos.z = (float)rand() / RAND_MAX * 100.0f - 50.0f;
	//	//pos.y = meshfield->GetHeight(pos);
	//	pos.y = 0.0f;
	//	tree->SetPosition(pos);
	//}
	}
	

	//////////岩
	//for (int i = 0; i < 20; i++)
	//{
	//	auto rock = AddGameObject<Rock>();

	//	D3DXVECTOR3 pos;
	//	pos.x = (float)rand() / RAND_MAX * 100.0f - 50.0f;
	//	pos.z = (float)rand() / RAND_MAX * 100.0f - 50.0f;
	//	MeshField* meshField = GetGameObject<MeshField>();
	//	pos.y = meshField->GetHeight(pos);
	//	rock->SetPosition(pos);

	//	D3DXVECTOR3 scl;
	//	scl.x = scl.y = scl.z = (float)rand() / RAND_MAX * 1.0f + 1.0f;
	//	rock->SetScale(scl);
	//}
	
	m_BattleBGM = AddGameObject<GameObject>()->AddComponent<Audio>();
	m_BattleBGM->Load("asset\\audio\\BGM\\battlebgm.wav");

	m_WinSE = AddGameObject<GameObject>()->AddComponent<Audio>();
	m_WinSE->Load("asset\\audio\\SE\\栄光のファンファーレ.wav");
}


void Game::Update()
{
	Scene::Update();
	m_Scene = Manager::GetScene();
	Player* player = m_Scene->GetGameObject<Player>();
	Enemy* enemy = m_Scene->GetGameObject<Enemy>();
	GameTexture* gametexture = m_Scene->GetGameObject<GameTexture>();

	if (enemy != nullptr)
	{
		if (enemy->GetEnemyHowlFinish() && !m_PlayBGMFlag)
		{
			m_BattleBGM->Volume(Scene::m_BGMVolume * 0.3);
			m_BattleBGM->PlayBGM();
			m_PlayBGMFlag = true;
		}


		if (enemy->GetDead() && !m_WinSEFlag)
		{
			m_BattleBGM->Stop();
			m_WinSE->Volume(Scene::m_SEVolume*0.15f);
			m_WinSE->PlaySE();
			m_WinSEFlag = true;
		}
	}
	
	
	
	
	if (gametexture->GetChangeSceneFlag() || Input::GetKeyTrigger('H'))
	{
		m_Fade->FadeOut();
	}
	if (m_Fade->GetFadeFinish())
	{
		Manager::SetScene<Result>();
	}
	


	/*if (player->GetOverFlag())
	{
		m_Fade->FadeOut();
	}
	if (m_Fade->GetFadeFinish())
	{
		Manager::SetScene<Result>();
	}*/

	
}

void Game::Uninit()
{
	Scene::Uninit();
	
	
	
}

void Game::Draw()
{
	m_Scene = Manager::GetScene();
	D3DXVECTOR3 lighttarget;
	MeshField* meshfield= GetGameObject<MeshField>();
	
	
	lighttarget = meshfield->GetCenterPosition();

	
	
	////////reflect
 //   //ビュー変換行列を作成する
 //   //注視点オフセットテーブル
	//D3DXVECTOR3 lookatOffset[6] = {
	//	{ 1.0f, 0.0f, 0.0f },//+X D3D11_TEXTURECUBE_FACE_POSITIVE_X
	//	{ -1.0f, 0.0f, 0.0f },//-X D3D11_TEXTURECUBE_FACE_NEGATIVE_X
	//	{ 0.0f, 1.0f, 0.0f },//+Y D3D11_TEXTURECUBE_FACE_POSITIVE_Y
	//	{ 0.0f, -1.0f, 0.0f },//-Y D3D11_TEXTURECUBE_FACE_NEGATIVE_Y
	//	{ 0.0f, 0.0f, 1.0f },//+Z D3D11_TEXTURECUBE_FACE_POSITIVE_Z
	//	{ 0.0f, 0.0f, -1.0f },//-Z D3D11_TEXTURECUBE_FACE_NEGATIVE_Z
	//};

	////upベクトルテーブル
	//D3DXVECTOR3 upOffset[6] = {
	//	{ 0.0f, 1.0f, 0.0f },
	//	{ 0.0f, 1.0f, 0.0f },
	//	{ 0.0f, 0.0f, -1.0f },
	//	{ 0.0f, 0.0f, 1.0f },
	//	{ 0.0f, 1.0f, 0.0f },
	//	{ 0.0f, 1.0f, 0.0f },
	//};

	//D3DXVECTOR3 eye;
	//D3DXVECTOR3 lookat;
	//D3DXVECTOR3 up;
	//D3DXMATRIX viewMatrixArray[6];
	//D3DXVECTOR3 vPlayerPos = sword->GetPosition();
	//for (int i = 0; i < 6; i++)
	//{
	//	eye = vPlayerPos;
	//	lookat = vPlayerPos + lookatOffset[i];
	//	up = -upOffset[i];
	//	D3DXMatrixLookAtLH(&viewMatrixArray[i], &eye, &lookat, &up);
	//}

	////プロジェクションマトリクス設定
	//D3DXMATRIX projectionMatrix;
	//D3DXMatrixPerspectiveFovLH(&projectionMatrix, D3DX_PI / 2, 1.0f, 0.01f, 15000.0f);
	//Renderer::SetProjectionMatrix(&projectionMatrix);
	////ビューポート変更
	//Renderer::SetReflectViewport();
	////6面分描画する
	//for (int i = 0; i < 6; i++)
	//{
	//	Renderer::BeginCube();
	//	//ビュー変換マトリクス設定
	//	Renderer::SetViewMatrix(&viewMatrixArray[i]);
	//	Scene::ReflectDraw();

	//	//描画したテクスチャをキューブマップ用テクスチャにコピーしていく
	//	Renderer::GetDeviceContext()->CopySubresourceRegion(
	//		Renderer::GetCubeReflectTexture(),
	//		D3D11CalcSubresource(0, i, 1),
	//		0, 0, 0, Renderer::GetReflectTexture(), 0, nullptr);
	//}



	//ライトカメラ構造体の初期化
	//LIGHT light;
	m_Light.Enable = true;
	m_Light.Direction = D3DXVECTOR4(m_X, m_Y, m_Z, m_A);	//方向
	D3DXVec4Normalize(&m_Light.Direction, &m_Light.Direction);
	m_Light.Ambient = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);	//環境光の色
	m_Light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//拡散光の色


	//ライトカメラのビュー行列を作成
	D3DXVECTOR3 lightPos = D3DXVECTOR3(-50.0f + lighttarget.x, 100.0f , -50.0f  + lighttarget.z);
	//D3DXVECTOR3 lightPos = D3DXVECTOR3(lighttarget.x, 30.0f,lighttarget.z);
	D3DXVECTOR3 lightTarget = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 lightUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&m_Light.ViewMatrix, &lightPos, &lightTarget, &lightUp);
	//ライトカメラのプロジェクション行列を作成(マトリックス,視野角,アスペクト比,ニアクリップ,ファークリップ(描画距離))
	D3DXMatrixPerspectiveFovLH(&m_Light.ProjectionMatrix, 1.0f,(float)1.0f, 35.0f, 400.0f);
	Renderer::SetLight(m_Light);

	//** 1パス目 シャドウバッファの作成 **//
	Renderer::BeginDepth();
	Renderer::SetDepthViewport();

	//ライトカメラの行列をセット
	Renderer::SetViewMatrix(&m_Light.ViewMatrix);
	Renderer::SetProjectionMatrix(&m_Light.ProjectionMatrix);

	//影を落としたいオブジェクトの描画
	Scene::DepthDraw();
	
	//2パス目　通常の作成
	Renderer::Begin();

	Renderer::SetDefaultViewport();

	//本来のカメラ&プロジェクション行列をセット
	

	m_Light.Enable = false;
	Renderer::SetLight(m_Light);

	
	

	Scene::Draw();
	

	/*CollisionHit::Update();*/
	//ゲームのDrawのあとコンポーネントのDraw
}
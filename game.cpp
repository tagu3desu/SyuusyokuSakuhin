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
#include"trail.h"
#include"gametexturemanager.h"
#include"collider.h"
#include"campField.h"
#include"rockeffect.h"
#include"basecamptent.h"
#include"treasurebox.h"
#include"areachangecollider.h"

Torus* torus;
Player* player;

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
	AreaChange::Load();
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
	AreaChange::Unload();
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
	//meshfield->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 400.0f));
	meshfield->SetMapActive(true);

	BaseCamp* basecamp = AddGameObject<BaseCamp>();
	basecamp->SetMapActive(false);

	player =  AddGameObject<Player>();
	player->SetPosition(D3DXVECTOR3(-1,0,-4));
	//player->SetPosition(D3DXVECTOR3(-1, 0, 400));

	//Gun* gun = AddGameObject<Gun>();
	Sword*sword =AddGameObject<Sword>();
	Shield* shield = AddGameObject<Shield>();
	SwordTopVertex* swordtopvertex = AddGameObject<SwordTopVertex>();


	Enemy* enemy = AddGameObject<Enemy>();
	enemy->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 25.0f));
	
	Box* box = AddGameObject<Box>();
	box->SetPosition(D3DXVECTOR3(7.0f,0.0f,0.0f));

	

	if (basecamp->GetMapActive())
	{
		AddGameObject<AreaChange>()->SetPosition(D3DXVECTOR3(-1.0f, 6.0f, 43.0f));
		AddGameObject<BaceCampTent>();
		AddGameObject<TreasureBox>();
	}
	

	AddGameObject<Trail>();

	AddGameObject<GameTexture>(SPRITE_LAYER);
	
	AddGameObject<HPgage>(SPRITE_LAYER);

	AddGameObject<Staminagage>(SPRITE_LAYER);

	AddGameObject<Potion>(SPRITE_LAYER);
	AddGameObject<PotionCount>(SPRITE_LAYER);


	m_Fade = AddGameObject<Fade>(SPRITE_LAYER);

	////////木
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



	//////////岩
	/*for (int i = 0; i < 20; i++)
	{
		auto rock = AddGameObject<Rock>();

		D3DXVECTOR3 pos;
		pos.x = (float)rand() / RAND_MAX * 100.0f - 50.0f;
		pos.z = (float)rand() / RAND_MAX * 100.0f - 50.0f;
		MeshField* meshField = GetGameObject<MeshField>();
		pos.y = meshField->GetHeight(pos);
		rock->SetPosition(pos);

		D3DXVECTOR3 scl;
		scl.x = scl.y = scl.z = (float)rand() / RAND_MAX * 1.0f + 1.0f;
		rock->SetScale(scl);
	}*/
	
	
}


void Game::Update()
{
	Scene::Update();
	Scene* scene = Manager::GetScene();
	Player* player = scene->GetGameObject<Player>();
	
	Sword* sword = GetGameObject<Sword>();
	
	
	
	if (Input::GetKeyTrigger('@'))
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
	scene = Manager::GetScene();
	D3DXVECTOR3 lighttarget;
	MeshField* meshfield= GetGameObject<MeshField>();
	BaseCamp* campfield = GetGameObject<BaseCamp>();
	Sword* sword = GetGameObject<Sword>();

	if (meshfield != nullptr)
	{
		if (meshfield->GetMapActive())
		{
			lighttarget = meshfield->GetCenterPosition();
		}
	}
	
	if (campfield != nullptr)
	{
		if (campfield->GetMapActive())
		{
			lighttarget = campfield->GetCenterPosition();
		}
	}
	
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
	light.Enable = true;
	light.Direction = D3DXVECTOR4(x, y, z, a);	//方向
	D3DXVec4Normalize(&light.Direction, &light.Direction);
	light.Ambient = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);	//環境光の色
	light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//拡散光の色


	//ライトカメラのビュー行列を作成
	D3DXVECTOR3 lightPos = D3DXVECTOR3(-50.0f + lighttarget.x, 100.0f , -50.0f  + lighttarget.z);
	//D3DXVECTOR3 lightPos = D3DXVECTOR3(lighttarget.x, 30.0f,lighttarget.z);
	D3DXVECTOR3 lightTarget = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 lightUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&light.ViewMatrix, &lightPos, &lightTarget, &lightUp);
	//ライトカメラのプロジェクション行列を作成(マトリックス,視野角,アスペクト比,ニアクリップ,ファークリップ(描画距離))
	D3DXMatrixPerspectiveFovLH(&light.ProjectionMatrix, 1.0f,(float)1.0f, 35.0f, 400.0f);
	Renderer::SetLight(light);

	//** 1パス目 シャドウバッファの作成 **//
	Renderer::BeginDepth();
	Renderer::SetDepthViewport();

	//ライトカメラの行列をセット
	Renderer::SetViewMatrix(&light.ViewMatrix);
	Renderer::SetProjectionMatrix(&light.ProjectionMatrix);

	//影を落としたいオブジェクトの描画
	Scene::DepthDraw();
	
	//2パス目　通常の作成
	Renderer::Begin();

	Renderer::SetDefaultViewport();

	//本来のカメラ&プロジェクション行列をセット
	

	light.Enable = false;
	Renderer::SetLight(light);

	
	

	Scene::Draw();
	

	/*CollisionHit::Update();*/
	//ゲームのDrawのあとコンポーネントのDraw
}
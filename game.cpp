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

#include"gametexturemanager.h"

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
	
	
	//カメラ
	Camera* camera = AddGameObject<Camera>(CAMERA_LAYER);
	//スカイドーム
	Sky*  skydome = AddGameObject<Sky>();
	skydome->SetScale(D3DXVECTOR3(300.0f,300.0f,300.0f));

	//フィールド関連
	//Field* field = AddGameObject<Field>();
	MeshField*  meshfield = AddGameObject<MeshField>();

	

	player =  AddGameObject<Player>();
	player->SetPosition(D3DXVECTOR3(-1.0f,0.0f, -4.0f));

	//Gun* gun = AddGameObject<Gun>();
	Sword*sword =AddGameObject<Sword>();
	Shield* shield = AddGameObject<Shield>();



	

	Enemy* enemy = AddGameObject<Enemy>();
	enemy->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 15.0f));
	
	TrailTexture* trailtexture = AddGameObject<TrailTexture>();


	
	
	AddGameObject<Trail>();

	AddGameObject<GameTexture>(SPRITE_LAYER);
	
	AddGameObject<HPgage>(SPRITE_LAYER);

	AddGameObject<Staminagage>(SPRITE_LAYER);

	AddGameObject<Potion>(SPRITE_LAYER);
	AddGameObject<PotionCount>(SPRITE_LAYER);


	m_Fade = AddGameObject<Fade>(SPRITE_LAYER);

	////木
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

	//////岩
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
}

void Game::Uninit()
{
	Scene::Uninit();
	
	
}

void Game::Draw()
{
	Scene* scene = Manager::GetScene();
	D3DXVECTOR3 playerpos =	player->GetPosition();

	//ライトカメラ構造体の初期化
	LIGHT light;
	light.Enable = true;
	light.Direction = D3DXVECTOR4(1.0f, -1.0f, 1.0f, 0.0f);	//方向
	D3DXVec4Normalize(&light.Direction, &light.Direction);
	light.Ambient = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);	//環境光の色
	light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//拡散光の色


	//ライトカメラのビュー行列を作成
	D3DXVECTOR3 lightPos = D3DXVECTOR3(-50.0f + playerpos.x, 20.0f , -50.0f  + playerpos.z);
	D3DXVECTOR3 lightTarget = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 lightUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&light.ViewMatrix, &lightPos, &lightTarget, &lightUp);
	//ライトカメラのプロジェクション行列を作成(マトリックス,視野角,アスペクト比,ニアクリップ,ファークリップ(描画距離))
	D3DXMatrixPerspectiveFovLH(&light.ProjectionMatrix, 1.0f,(float)1.0f, 10.0f, 300.0f);
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
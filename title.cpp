#include"main.h"
#include"renderer.h"
#include"manager.h"
#include"title.h"
#include"camera.h"
#include"meshField.h"
#include"polygon2D.h"
#include"input.h"
#include"scene.h"
#include"game.h"
#include"fade.h"
#include"Loading.h"
#include"sky.h"
#include"player.h"
#include"field.h"
#include"wepon_sword.h"
#include"wepon_shield.h"
#include"wood.h"
#include"treeobj.h"
#include"titletexturemanager.h"
#include"audio.h"
#include"inputx.h"
#include"tutorial.h"

bool Title::m_TitleCheck = false;
bool Title::m_Menucontrol = false;
bool Title::m_QuestSelect = false;

TitleTexture* titletexture;

void Title::Init()
{
	Scene* scene = Manager::GetScene();

	Scene::Init();


	/*Game::SetLoadFinish(false);
	Tutorial::SetLoadFinish(false);*/

	Loading::SetTutorial(false);
	Loading::SetGameLoad(false);


	m_FloarPosition = 0;
	m_TitleCheck = true;

	//カメラ
	Camera* camera = AddGameObject<Camera>(CAMERA_LAYER);
	Sky* skydome = AddGameObject<Sky>();
	skydome->SetScale(D3DXVECTOR3(300.0f, 300.0f, 300.0f));
	Field* field = AddGameObject<Field>();
	Player* player = AddGameObject<Player>();
	player->SetRotation(D3DXVECTOR3(0.0f, -2.4f, 0.0f));
	

	Wood* wood = AddGameObject<Wood>();
	wood->SetPosition(D3DXVECTOR3(-0.3f, 0.3f, 0.0f));
	wood->SetRotation(D3DXVECTOR3(0.0f, -0.9f, 0.0f));


	titletexture = AddGameObject<TitleTexture>(SPRITE_LAYER);
	m_Fade = AddGameObject<Fade>(SPRITE_LAYER);

	int num = 0;

	m_TitleBGM = AddGameObject<GameObject>()->AddComponent<Audio>();
	m_TitleBGM->Load("asset\\audio\\BGM\\メインタイトル.wav");
	m_TitleBGM->PlayBGM(true);

	m_DecisiveSE = AddGameObject<GameObject>()->AddComponent<Audio>();
	m_DecisiveSE->Load("asset\\audio\\SE\\決定音.wav");
}

void Title::Update()
{
	Scene::Update();
	
	m_TitleBGM->Volume(titletexture->GetBGMVolume());


	//キー入力でゲーム画面に遷移
	if ((Input::GetKeyTrigger(VK_SPACE) || InputX::IsButtonTriggered(0, XINPUT_GAMEPAD_B) || Input::GetKeyTrigger(VK_LBUTTON)) && m_Menucontrol   && titletexture->GetGameButtonOverLap()) //Enterキー
	{
		m_Menucontrol = false;
		m_QuestSelect = true;
	} 

	if (titletexture->GetTutorialFlag())
	{
		Loading::SetTutorial(true);
		m_Fade->FadeOut();
	}
	else if (titletexture->GetQuestFlag())
	{
		Loading::SetGameLoad(true);
		m_Fade->FadeOut();
	}

	if (m_Fade->GetFadeFinish())
	{
		m_TitleCheck = false;
		Manager::SetScene<Loading>();
	}

	//最初の画面から選択画面へ
	if ((Input::GetKeyTrigger(VK_SPACE) || Input::GetKeyTrigger(VK_LBUTTON)  || InputX::IsButtonTriggered(0,XINPUT_GAMEPAD_B) ) && !m_Menucontrol)
	{
		m_DecisiveSE->PlaySE();
		m_DecisiveSE->Volume(titletexture->GetSEVolume());
		m_Menucontrol = true;
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
	Field* field= GetGameObject<Field>();
	objpos = field->GetPosition();

	//ライトカメラ構造体の初期化
	LIGHT light;
	light.Enable = true;
	light.Direction = D3DXVECTOR4(1.0f, -1.0f, 1.0f, 0.0f);	//方向
	D3DXVec4Normalize(&light.Direction, &light.Direction);
	light.Ambient = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);	//環境光の色
	light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//拡散光の色

	//ライトカメラのビュー行列を作成
	D3DXVECTOR3 lightPos = D3DXVECTOR3(-50.0f + objpos.x, 100.0f, -50.0f + objpos.z);
	D3DXVECTOR3 lightTarget = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 lightUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&light.ViewMatrix, &lightPos, &lightTarget, &lightUp);
	//ライトカメラのプロジェクション行列を作成(マトリックス,視野角,アスペクト比,ニアクリップ,ファークリップ(描画距離))
	D3DXMatrixPerspectiveFovLH(&light.ProjectionMatrix, 1.0f, (float)1.0f, 35.0f, 400.0f);
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
}



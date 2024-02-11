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

	//カメラ
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

	
	//キー入力でゲーム画面に遷移
	if (Input::GetKeyTrigger(VK_SPACE)  && menucontrol ||  Input::GetKeyTrigger(VK_LBUTTON) && buttonOverLapping && menucontrol) //Enterキー
	{
		m_Fade->FadeOut();
	} 
	if (m_Fade->GetFadeFinish())
	{
		m_TitleCheck = false;
	
		Manager::SetScene<Loading>();
	}

	//最初の画面から選択画面へ
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



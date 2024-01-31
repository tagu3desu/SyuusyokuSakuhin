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
//#include"titleplayer.h"
//#include"wepon_sword.h"



bool Title::m_TitleCheck = false;
//TitlePlayer* titleplayer;

void Title::Init()
{
	

	Scene::Init();

	

	m_framecount = 0;
	m_FloarPosition = 0;
	m_TitleCheck = true;

	//カメラ
	Camera* camera = AddGameObject<Camera>(CAMERA_LAYER);
	//スカイドーム
	/*Floar* box = AddGameObject<Floar>();
	box->SetPosition(D3DXVECTOR3(0.0f, 0.0f, m_FloarPosition));
	Floar* box2 = AddGameObject<Floar>();
	box2->SetPosition(D3DXVECTOR3(0.0f, 0.0f, m_FloarPosition + 2));
	Floar* box3 = AddGameObject<Floar>();
	box3->SetPosition(D3DXVECTOR3(0.0f, 0.0f, m_FloarPosition - 2));
	Floar* box4 = AddGameObject<Floar>();
	box4->SetPosition(D3DXVECTOR3(0.0f, 0.0f, m_FloarPosition - 4));
	Floar* box5 = AddGameObject<Floar>();
	box5->SetPosition(D3DXVECTOR3(0.0f, 0.0f, m_FloarPosition - 6));
	Floar* box6 = AddGameObject<Floar>();
	box6->SetPosition(D3DXVECTOR3(0.0f, 0.0f, m_FloarPosition - 8));*/

	Cylinder* cylinder = AddGameObject<Cylinder>();
	cylinder->SetPosition(D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	cylinder->SetScale(D3DXVECTOR3(5.0f, 1.0f, 5.0f));

	Door* door = AddGameObject<Door>();
	door->SetPosition(D3DXVECTOR3(0.0f, 2.0f, 10.0f));
	D3DXVECTOR3 doorposition = door->GetPosition();
	//DoorFrame* doorframe = AddGameObject<DoorFrame>();
	//doorframe->SetPosition(doorposition);
	
	//メッシュフィールド
	WaterSurFace* watersurface = AddGameObject<WaterSurFace>();
	watersurface->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));


	Sky* skydome = AddGameObject<Sky>();
	skydome->SetScale(D3DXVECTOR3(300.0f, 300.0f, 300.0f));

	/*titleplayer = AddGameObject<TitlePlayer>();
	titleplayer->SetPosition(D3DXVECTOR3(0.0f, 2.0f, 0.0f));
	Sword* sword = AddGameObject<Sword>();*/


	//AddGameObject<TitleLogo>(SPRITE_LAYER);
	TitleButton*  m_StartButton = AddGameObject<TitleButton>(SPRITE_LAYER);

	m_Fade = AddGameObject<Fade>(SPRITE_LAYER);
	buttonOverLapping = false;
	int num = 0;
}


void Title::Update()
{
	Scene::Update();
	
	Scene* scene = Manager::GetScene();

	m_MouseposX = GetMouseCursorPosXinWnd();
	m_MouseposY = GetMouseCursorPosYinWnd();

	//GUIにパラメータ表示
	/*ImGui::SetNextWindowSize(ImVec2(300, 150));
	ImGui::Begin("Mouse");
	ImGui::InputFloat("PositionX", &m_MouseposX);
	ImGui::InputFloat("PositionY", &m_MouseposY);
	ImGui::Checkbox("Push", &buttonOverLapping);
	ImGui::End();*/

	//シーン上の全ての床を参照
	//Camera* camera = GetGameObject<Camera>();
	//m_SponePosition = camera->GetPosition();
	//m_framecount++;
	//if (m_framecount >= 200)
	//{
	//	AddGameObject<Floar>()->SetPosition(D3DXVECTOR3(m_SponePosition.x, m_SponePosition.y - 3.0f, m_SponePosition.z + 10.0f));
	//	m_framecount = 0;
	//}



	//D3DXVECTOR3 position;
	//float differential;
	//std::vector<Floar*> floars = scene->GetGameObjects<Floar>();
	//for (Floar* floar : floars)
	//{
	//	position = floar->GetPosition();
	//	differential = m_SponePosition.z - position.z;

	//	if (m_SponePosition.y != position.y)
	//	{
	//		
	//	}

	//	if (m_SponePosition.z >= position.z)//differential > 2)
	//	{
	//		floar->SetDestroy();
	//	}
	//}
	
	
	

	if (430 <= m_MouseposX && m_MouseposX<= 930 && 425 <= m_MouseposY&& m_MouseposY <= 515)
	{
		buttonOverLapping = true;
	}
	else
	{
		buttonOverLapping = false;
	}

	//キー入力でゲーム画面に遷移
	if (Input::GetKeyTrigger(VK_SPACE) ||  Input::GetKeyTrigger(VK_LBUTTON) && buttonOverLapping) //Enterキー
	{
		m_Fade->FadeOut();
	} 
	if (m_Fade->GetFadeFinish())
	{
		m_TitleCheck = false;
		Manager::SetScene<Loading>();
	}
}

void Title::Uninit()
{
	
	Scene::Uninit();

	
}

void Title::Draw()
{
	
	Scene* scene = Manager::GetScene();
	Cylinder* cylinder = GetGameObject<Cylinder>();
	D3DXVECTOR3 objpos = cylinder->GetPosition();

	//ライトカメラ構造体の初期化
	LIGHT light;
	light.Enable = true;
	light.Direction = D3DXVECTOR4(1.0f, -1.0f, 1.0f, 0.0f);	//方向
	D3DXVec4Normalize(&light.Direction, &light.Direction);
	light.Ambient = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);	//環境光の色
	light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//拡散光の色

	//ライトカメラのビュー行列を作成
	D3DXVECTOR3 lightPos = D3DXVECTOR3(-50.0f + objpos.x, 20.0f, -50.0f + objpos.z);
	D3DXVECTOR3 lightTarget = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 lightUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&light.ViewMatrix, &lightPos, &lightTarget, &lightUp);
	//ライトカメラのプロジェクション行列を作成(マトリックス,視野角,アスペクト比,ニアクリップ,ファークリップ(描画距離))
	D3DXMatrixPerspectiveFovLH(&light.ProjectionMatrix, 1.0f, (float)1.0f, 10.0f, 300.0f);
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



#include"main.h"
#include"manager.h"
#include"renderer.h"
#include"areachangecollider.h"
#include"collider.h"
#include"player.h"
#include"meshField.h"
#include"campField.h"
#include"gametexturemanager.h"
#include"fade.h"

Model* AreaChange::m_Model;
void AreaChange::Init()
{
	m_DepthEnable = true;

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\vertexLightingPS.cso");

	scene = Manager::GetScene();
	m_AreaChangeCollider = scene->AddGameObject<Collider>();
	m_AreaChangeCollider->SetScale(D3DXVECTOR3(1.0f/m_Scale.x, 1.0f/m_Scale.y * 3.0f, 1.0f/m_Scale.z * 3.0f)*2.0f);
	m_AreaChangeCollider->SetPosition(D3DXVECTOR3(0.0f, 2.0f, 0.0f));

	
}

void AreaChange::Load()
{
	m_Model = new Model();
	m_Model->Load("asset\\model\\box.obj");
}

void AreaChange::Unload()
{
	m_Model->Unload();
	delete m_Model;
}

void AreaChange::Uninit()
{
	

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void AreaChange::Update()
{
	scene = Manager::GetScene();
	Player* player = scene->GetGameObject<Player>();
	MeshField* meshfield = scene->GetGameObject<MeshField>();
	BaseCamp* basecamp = scene->GetGameObject<BaseCamp>();
	GameTexture* gameflag = scene->GetGameObject<GameTexture>();

	m_AreaChangeCollider->SetMatrix(m_Matrix);
	SetColliderInfo(m_AreaChangeCollider->GetMatrix(),false);

	if (m_AreaChangeCollider->CollisionChecker(this, player, 0.9f) && gameflag->GetGameStart())
	{
		m_AreaChangeCollider->SetColliderColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		meshfield->SetMapActive(true);
		basecamp->SetMapActive(false);
		m_AreaChangeFlag = true;
		
	}
	else
	{
		m_AreaChangeCollider->SetColliderColor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
	}

	if (m_Fade->GetFadeFinish())
	{
	
	}

	ImGui::SetNextWindowSize(ImVec2(300, 250));
	ImGui::Begin("Area");
	ImGui::InputFloat3("CPosition", m_ColliderPosition);
	ImGui::InputFloat3("CScale", m_ColliderScale);
	ImGui::InputFloat3("Position", m_Position);
	ImGui::InputFloat3("Scale", m_Scale);
	ImGui::InputFloat3("Rotation", m_Rotation);
	ImGui::End();
}

void AreaChange::Draw()
{
	
	//入力レイアウト
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//シェーダ設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	//マトリクス設定
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	m_Matrix = scale * rot * trans;
	Renderer::SetWorldMatrix(&m_Matrix);

	//m_Model->Draw();
}
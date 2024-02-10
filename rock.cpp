#include"main.h"
#include"manager.h"
#include"renderer.h"
#include"scene.h"
#include"rock.h"
#include"collider.h"
#include"title.h"
Model* Rock::m_Model{};

void Rock::Init()
{
	
	m_DepthEnable = true;

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\vertexLightingPS.cso");

	scene = Manager::GetScene();


	m_RockCollider = scene->AddGameObject<Collider>();
	m_RockCollider->SetScale(D3DXVECTOR3(1 / m_Scale.x, 1 / m_Scale.y, 1 / m_Scale.z) * 1.5f);
	m_RockCollider->SetPosition(D3DXVECTOR3(0.0f, 0.3f, 0.0f));
	
}

void Rock::Load()
{
	m_Model = new Model();
	m_Model->Load("asset\\model\\Rock1.obj");
}

void Rock::Uninit()
{
	

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void Rock::Unload()
{
	m_Model->Unload();
	delete m_Model;
}

void Rock::Update()
{
	
	m_RockCollider->SetMatrix(m_Matrix);
	SetColliderInfo(m_RockCollider->GetMatrix(), false);

	
	
	
}

void Rock::Draw()
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

	m_Model->Draw();
}
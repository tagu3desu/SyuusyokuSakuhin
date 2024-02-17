#include"main.h"
#include"manager.h"
#include"renderer.h"
#include"box.h"
#include"collider.h"


Model* Box::m_Model;
void Box::Init()
{
	m_DepthEnable = true;

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\vertexLightingPS.cso");

	scene = Manager::GetScene();
	m_BoxCollider = scene->AddGameObject<Collider>();
	m_BoxCollider->SetScale(D3DXVECTOR3(1.0f/m_Scale.x, 1.0f/m_Scale.y, 1.0f/m_Scale.z)*2.0f);
	m_BoxCollider->SetPosition(D3DXVECTOR3(0.0f, 1.0f, 0.0f));
}

void Box::Load()
{
	m_Model = new Model();
	m_Model->Load("asset\\model\\box.obj");
}

void Box::Unload()
{
	m_Model->Unload();
	delete m_Model;
}

void Box::Uninit()
{
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void Box::Update()
{
	scene = Manager::GetScene();
	
	m_BoxCollider->SetMatrix(m_Matrix);
	SetColliderInfo(m_BoxCollider->GetMatrix(),false);
}

void Box::Draw()
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
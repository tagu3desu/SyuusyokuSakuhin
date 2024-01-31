#include"main.h"
#include"renderer.h"
#include"child.h"
#include"player.h"
Model* Child::m_Model{};

void Child::Init()
{
	
	

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\vertexLightingPS.cso");
}

void Child::Load()
{
	m_Model = new Model();
	m_Model->Load("asset\\model\\torus.obj");
}

void Child::Uninit()
{
	

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void Child::Unload()
{
	m_Model->Unload();
	delete m_Model;
}

void Child::Update()
{
	m_Rotation.y += 0.1f;
}

void Child::Draw()
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
	world = scale * rot * trans * m_Parent->GetMatrix();
	Renderer::SetWorldMatrix(&world);

	m_Model->Draw();
}
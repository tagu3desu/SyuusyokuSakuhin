#include"main.h"
#include"renderer.h"
#include"house.h"
#include"shadow.h"

void House::Init()
{

	m_Model = new Model();
	m_Model->Load("asset\\model\\house.obj");
	m_Scale = D3DXVECTOR3(0.15f, 0.15f, 0.15f);

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\vertexLightingPS.cso");

	//m_Shadow = AddComponent<Shadow>();
}

void House::Uninit()
{
	GameObject::Uninit();


	m_Model->Unload();
	delete m_Model;

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void House::Update()
{
	/*D3DXVECTOR3 shadowPosition = m_Position;
	shadowPosition.y = 0.0f;
	m_Shadow->SetPosition(shadowPosition);
	m_Shadow->SetScale(D3DXVECTOR3(3.0f, 3.0f, 3.0f));*/
}

void House::Draw()
{
	GameObject::Draw();
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
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(&world);

	m_Model->Draw();
}
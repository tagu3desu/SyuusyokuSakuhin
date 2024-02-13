#include"main.h"
#include"manager.h"
#include"renderer.h"
#include"treasurebox.h"
#include"collider.h"


Model* TreasureBox::m_Model;
void TreasureBox::Init()
{
	m_DepthEnable = true;
	m_Scale = D3DXVECTOR3(0.6f, 0.6f, 0.6f);
	m_Position = D3DXVECTOR3(8.0f, 4.0f, 19.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.6f, 0.0f);
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\vertexLightingPS.cso");

	scene = Manager::GetScene();
	
}

void TreasureBox::Load()
{
	m_Model = new Model();
	m_Model->Load("asset\\model\\Object\\treasurebox.obj");
}

void TreasureBox::Unload()
{
	m_Model->Unload();
	delete m_Model;
}

void TreasureBox::Uninit()
{
	

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void TreasureBox::Update()
{
	scene = Manager::GetScene();
	


	

	/*ImGui::SetNextWindowSize(ImVec2(300, 250));
	ImGui::Begin("TreasureBox");
	ImGui::InputFloat3("Position", m_Position);
	ImGui::InputFloat3("Scale", m_Scale);
	ImGui::InputFloat3("Rotation", m_Rotation);
	ImGui::End();*/
}

void TreasureBox::Draw()
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
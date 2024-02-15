#include"main.h"
#include"manager.h"
#include"renderer.h"
#include"dummy.h"
#include"collider.h"


Model* Dummy::m_Model;
void Dummy::Init()
{
	m_DepthEnable = true;

	m_Scale = D3DXVECTOR3(1.0, 2.0f, 1.0);

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\DepthShadowMappingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\DepthShadowMappingPS.cso");

	scene = Manager::GetScene();
	m_DummyCollider = scene->AddGameObject<Collider>();
	m_DummyCollider->SetScale(D3DXVECTOR3(1.0f/m_Scale.x, 1.0f/m_Scale.y * 2.0, 1.0f/m_Scale.z)*2.0f);
	m_DummyCollider->SetPosition(D3DXVECTOR3(0.0f, 1.0f, 0.0f));
}

void Dummy::Load()
{
	m_Model = new Model();
	m_Model->Load("asset\\model\\box.obj");
}

void Dummy::Unload()
{
	m_Model->Unload();
	delete m_Model;
}

void Dummy::Uninit()
{
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void Dummy::Update()
{
	scene = Manager::GetScene();
	
	m_DummyCollider->SetMatrix(m_Matrix);
	SetColliderInfo(m_DummyCollider->GetMatrix(),false);

	

	ImGui::SetNextWindowSize(ImVec2(300, 250));
	ImGui::Begin("Box");
	ImGui::InputFloat3("Position", m_ColliderPosition);
	ImGui::InputFloat3("Scale", m_ColliderScale);
	ImGui::InputFloat3("Forward", m_ColiiderForward);
	ImGui::InputFloat3("Right", m_ColiiderRight);
	ImGui::InputFloat3("Up", m_ColiiderUp);
	ImGui::End();
}

void Dummy::Draw()
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
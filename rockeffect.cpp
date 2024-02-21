#include"main.h"
#include"manager.h"
#include"renderer.h"
#include"rockeffect.h"
#include"collider.h"
#include"player.h"
#include"camera.h"
Model* RockEffect::m_Model;
void RockEffect::Init()
{
	m_DepthEnable = true;

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\vertexLightingPS.cso");

	m_Scale = D3DXVECTOR3(1.3f, 1.3, 1.3f);
	m_Position = D3DXVECTOR3(0.0f, -0.7f, 0.0f);


	scene = Manager::GetScene();
	m_RockCollider = scene->AddGameObject<Collider>();
	m_RockCollider->SetScale(D3DXVECTOR3(1.0f/m_Scale.x * 2.0, 1.0f/m_Scale.y * 2.0f, 1.0f/m_Scale.z * 6.5f)*2.0f);
	m_RockCollider->SetPosition(D3DXVECTOR3(0.2f, 1.6f, -0.0f));
}

void RockEffect::Load()
{
	m_Model = new Model();
	m_Model->Load("asset\\model\\rockeffect.obj");
}

void RockEffect::Unload()
{
	m_Model->Unload();
	delete m_Model;
}

void RockEffect::Uninit()
{
	

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void RockEffect::Update()
{
	Player* player = scene->GetGameObject<Player>();

	m_RockCollider->SetMatrix(m_Matrix);
	SetColliderInfo(m_RockCollider->GetMatrix());

	if (m_RockCollider->CollisionChecker(this, player, 0.7f))
	{
		m_RockCollider->SetColliderColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	}
	else
	{
		m_RockCollider->SetColliderColor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));	
	}

	m_FrameWait++;
	if (m_FrameWait < 10)
	{
		Camera* camera = scene->GetGameObject<Camera>();
		camera->Shake(0.1f);
		m_Position.y += 0.1f;
	}

	if (90 < m_FrameWait)
	{
		m_RockCollider->SetDestroy();
		SetDestroy();
	}

}

void RockEffect::Draw()
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
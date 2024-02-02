#include"main.h"
#include"manager.h"
#include"renderer.h"
#include"scene.h"
#include"bullet.h"
#include"player.h"
#include"explosion.h"
#include"enemy.h"
#include"score.h"

Model* Bullet::m_Model{};

void Bullet::Init()
{
	m_Scale = D3DXVECTOR3(1.2f, 1.2f, 1.2f);
	

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\pixelLightingRimVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\pixelLightingRimPS.cso");

	m_MaxAccleration = 15.0f;
	m_Idlecount = 0;
	m_Period = 2.0;
	
}

void Bullet::Load()
{
	m_Model = new Model();
	m_Model->Load("asset\\model\\Rock1.obj");
}

void Bullet::Uninit()
{
	

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void Bullet::Unload()
{
	m_Model->Unload();
	delete m_Model;
}

void Bullet::Update()
{
	Scene* scene = Manager::GetScene();
	Player* player=scene->GetGameObject<Player>();



	switch (m_BulletState)
	{
	case BULLET_STATE_IDLE:
		UpdateIdle();
		break;
	case BULLET_STATE_ATTACK:
		UpdateAttack();
		break;
	default:
		break;
	}
	
	if (m_Position.y >= 6.0)
	{
		m_BulletState = BULLET_STATE_ATTACK;
	}

	////GUIにパラメータ表示
	//ImGui::SetNextWindowSize(ImVec2(400, 250));
	//ImGui::Begin("Bullet");
	//ImGui::InputFloat3("Direction", m_direction);
	//ImGui::InputFloat3("Position", m_Position);	
	//ImGui::InputFloat3("Ratation", m_Rotation);
	//ImGui::InputFloat3("Scale", m_Scale);
	//ImGui::InputFloat("Length", &m_BulletLife);
	//ImGui::InputFloat("m_FrameWait", &m_FrameWait);
	//ImGui::Checkbox("hit", &hit);
	//ImGui::End();
	
}

void Bullet::Draw()
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
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(&world);

	m_Model->Draw();
}

void Bullet::UpdateIdle()
{
	m_Position.y += 0.075f;
	
}

void Bullet::UpdateAttack()
{
	Scene* scene = Manager::GetScene();
	Player* player = scene->GetGameObject<Player>();

	D3DXVECTOR3 m_Accleleration{ 0.0f,0.0f,0.0f };

	m_FrameWait += 0.0005f;


	m_direction = player->GetPosition() - m_Position;

	m_Accleleration += (m_direction - m_Velocity * m_Period) * 2 / (m_Period * m_Period);

	m_Period -= m_FrameWait;

	m_BulletLife++;
	if (m_BulletLife > 300.0f)
	{
		SetDestroy();
		return;
	}



	length = D3DXVec3Length(&m_Accleleration);


	if (length > m_MaxAccleration)
	{
		D3DXVec3Normalize(&m_Accleleration, &m_Accleleration);
		m_Accleleration = m_Accleleration * m_MaxAccleration;
	}

	m_Velocity += m_Accleleration * m_FrameWait;
	m_Position += m_Velocity * m_FrameWait;

	D3DXVECTOR3 hitposition;
	if (player->GetPosition() == m_Position)
	{
		hit = true;
		SetDestroy();
		return;
	}
}
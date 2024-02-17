#include"main.h"
#include"manager.h"
#include"renderer.h"
#include"scene.h"
#include"bullet.h"
#include"player.h"
#include"bladeefect1.h"
#include"enemy.h"
#include"score.h"
#include"collider.h"

Model* Bullet::m_Model{};

void Bullet::Init()
{
	m_Scale = D3DXVECTOR3(3.0f, 3.0f, 3.0f);
	

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\pixelLightingRimVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\pixelLightingRimPS.cso");

	m_MaxAccleration = 15.0f;
	m_Idlecount = 0;
	m_Period = 2.0;

	scene = Manager::GetScene();
	m_BulletCollider = scene->AddGameObject<Collider>();
	m_BulletCollider->SetScale(D3DXVECTOR3(1.0f / m_Scale.x, 1.0f / m_Scale.y , 1.0f / m_Scale.z) * 4.0f);
	m_BulletCollider->SetPosition(D3DXVECTOR3(0.0f, 0.3f, 0.0f));
	
}

void Bullet::Load()
{
	m_Model = new Model();
	m_Model->Load("asset\\model\\Rock.obj");
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

	m_BulletCollider->SetMatrix(m_Matrix);
	SetColliderInfo(m_BulletCollider->GetMatrix(), false);

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
	
	if (m_BulletCollider->CollisionChecker(this, player, 0.7f))
	{
		m_BulletCollider->SetColliderColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		m_Hit = true;
	}
	else
	{
		m_BulletCollider->SetColliderColor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
		m_Hit = false;
	}

}

void Bullet::Draw()
{
	//入力レイアウト
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//シェーダ設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	PARAMETER parameter;
	parameter.weponcolor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	Renderer::SetParameter(parameter);

	//マトリクス設定
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	m_Matrix = scale * rot * trans;
	Renderer::SetWorldMatrix(&m_Matrix);

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

	m_Rotation.x += 0.1f;

	m_FrameWait += 0.00008f;


	m_direction = player->GetPosition() - m_Position;

	m_Accleleration += (m_direction - m_Velocity * m_Period) * 2 / (m_Period * m_Period);

	m_Period -= m_FrameWait;

	m_BulletLife++;
	if (m_BulletLife > 300.0f)
	{
		m_BulletCollider->SetDestroy();
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

	

}
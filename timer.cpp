#include "main.h"
#include "renderer.h"
#include"manager.h"
#include"scene.h"
#include"enemy.h"
#include "polygon2D.h"
#include"sprite.h"
#include"timer.h"
#include"clearrank.h"
float ClockTimeHand::m_TimeMin=0.0f; //��
float ClockTimeHand::m_TimeSecond=0.0f;	//�b
float ClockTimeHand::m_TimeMilliSeconds =0.0f;	//�~��

void ClockTimeHand::Init()
{


	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\unlitTexturePS.cso");

	AddComponent<Sprite>()->Init(0, 0, 200, 200, "asset/texture/UI/ClockHand.png");
	m_Position = (D3DXVECTOR3(85, 90, 0.0f));

	m_Scene = Manager::GetScene();

}

void ClockTimeHand::Uninit()
{

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

	GameObject::Uninit();
}

void ClockTimeHand::Update()
{
	//GameObject::Update();
	//m_Position = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
	m_TimeCount++;
	
	Enemy* enemy = m_Scene->GetGameObject<Enemy>();
	ClearRank* clearrank = m_Scene->GetGameObject<ClearRank>();

	if (!enemy->GetDead())
	{
		m_TimeMilliSeconds++;
		//1���Ŏ��v�̐j�𓮂���
		if (m_TimeCount % 60 == 0)
		{
			m_TimeMilliSeconds = 0.0f;
			m_TimeSecond += 1.0f;
		}

		if (m_TimeCount >= 3600)
		{
			m_TimeCount = 0;
			m_TimeSecond = 0.0f;
			m_TimeMin += 1.0f;
			m_Rotation.z += 0.106f;
		}
	}
	
	if (enemy->GetDead())
	{
		if (clearrank != nullptr)
		{
			if (m_TimeMin <= 1) //S
			{
				clearrank->SetRank(0);
			}
			else if (m_TimeMin >= 1 && m_TimeSecond > 30) //A
			{
				clearrank->SetRank(1);
			}
			else if (m_TimeMin >= 2 && m_TimeSecond > 30) //B
			{
				clearrank->SetRank(2);
			}
			else if (m_TimeMin >= 3 && m_TimeSecond > 30) //C
			{
				clearrank->SetRank(3);
			}
			else if (m_TimeMin >= 4 && m_TimeSecond > 30) //D
			{
				clearrank->SetRank(4);
			}
			else if (m_TimeMin >= 5 && m_TimeSecond > 30) //E
			{
				clearrank->SetRank(5);
			}
		}
		
	}
	
	/*ImGui::Begin("Time");
	ImGui::InputFloat("Min", &m_TimeMin);
	ImGui::InputFloat("Second", &m_TimeSecond);
	ImGui::InputFloat("MilliSecond", &m_TimeMilliSeconds);
	ImGui::End();*/

}

void ClockTimeHand::Draw()
{
	//���̓��C�A�E�g
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//�V�F�[�_�ݒ�
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	//�}�g���N�X�ݒ�
	Renderer::SetWorldViewProjection2D();

	D3DXMATRIX world, scale, rot, trans,offset;
	D3DXMatrixTranslation(&offset, -100.0f, -100.0f, 0);
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z); 
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = offset * scale * rot * trans;
	Renderer::SetWorldMatrix(&world);

	//���N���X�̃��\�b�h�Ăяo��
	GameObject::Draw();

}



void ClockTimeLimit::Init()
{


	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\unlitTexturePS.cso");

	AddComponent<Sprite>()->Init(0, 0, 185, 185, "asset/texture/UI/ClockHandLimit2.png");
	m_Position = (D3DXVECTOR3(75.0f, 100.0f, 0.0f));

	//��������
	SetLimitTime(10.0f);


}

void ClockTimeLimit::Uninit()
{

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

	GameObject::Uninit();
}

void ClockTimeLimit::Update()
{
	
}

void ClockTimeLimit::Draw()
{
	//���̓��C�A�E�g
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//�V�F�[�_�ݒ�
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	//�}�g���N�X�ݒ�
	Renderer::SetWorldViewProjection2D();

	D3DXMATRIX world, scale, rot, trans, offset;
	D3DXMatrixTranslation(&offset, -100.0f, -100.0f, 0);
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = offset * scale * rot * trans;
	Renderer::SetWorldMatrix(&world);

	//���N���X�̃��\�b�h�Ăяo��
	GameObject::Draw();

}

void ClockTimeLimit::SetLimitTime(float limit)
{
	m_LimitTime = limit;
	m_LimitTime *= 0.106;
	m_Rotation.z = m_LimitTime;
}
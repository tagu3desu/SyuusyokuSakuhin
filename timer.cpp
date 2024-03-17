#include "main.h"
#include "renderer.h"
#include"manager.h"
#include"scene.h"
#include"enemy.h"
#include "polygon2D.h"
#include"sprite.h"
#include"timer.h"
#include"clearrank.h"
float ClockTimeHand::m_TimeMin=0.0f; //分
float ClockTimeHand::m_TimeSecond=0.0f;	//秒
float ClockTimeHand::m_TimeMilliSeconds =0.0f;	//ミリ
int ClockTimeHand::m_Rank = 0;
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
		//1分で時計の針を動かす
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
		
			if (m_TimeMin < 1) //S
			{
				m_Rank = 0;
			}
			else if (1 <= m_TimeMin  && m_TimeMin < 3) //A
			{
				m_Rank = 1;
			}
			else if (3 <= m_TimeMin && m_TimeMin < 4) //B
			{
				m_Rank = 2;
			}
			else if (4 <= m_TimeMin && m_TimeMin < 5) //C
			{
				m_Rank = 3;
			}
			else if (5 <= m_TimeMin && m_TimeMin < 6) //D
			{
				m_Rank = 4;
			}
			else//E
			{
				m_Rank = 5;
			}
	}
}

void ClockTimeHand::Draw()
{
	//入力レイアウト
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//シェーダ設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	//マトリクス設定
	Renderer::SetWorldViewProjection2D();

	D3DXMATRIX world, scale, rot, trans,offset;
	D3DXMatrixTranslation(&offset, -100.0f, -100.0f, 0);
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z); 
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = offset * scale * rot * trans;
	Renderer::SetWorldMatrix(&world);

	//基底クラスのメソッド呼び出し
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

	//制限時間
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
	//入力レイアウト
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//シェーダ設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	//マトリクス設定
	Renderer::SetWorldViewProjection2D();

	D3DXMATRIX world, scale, rot, trans, offset;
	D3DXMatrixTranslation(&offset, -100.0f, -100.0f, 0);
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = offset * scale * rot * trans;
	Renderer::SetWorldMatrix(&world);

	//基底クラスのメソッド呼び出し
	GameObject::Draw();

}

void ClockTimeLimit::SetLimitTime(float limit)
{
	m_LimitTime = limit;
	m_LimitTime *= 0.106;
	m_Rotation.z = m_LimitTime;
}
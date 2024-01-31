#include "main.h"
#include "renderer.h"
#include "polygon2D.h"
#include"sprite.h"
#include"titlebutton.h"
#include"input.h"
void TitleButton::Init()
{


	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\unlitTexturePS.cso");


	m_Sprite = AddComponent<Sprite>();
	m_Sprite->Init(360, SCREEN_HEIGHT/2, SCREEN_WIDTH/2, SCREEN_HEIGHT/3, "asset/texture/PushtoSpace.png");
	
}

void  TitleButton::Uninit()
{
	

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

	GameObject::Uninit();
}

void TitleButton::Update()
{
	

	GameObject::Update();
	

	m_Count++;
	if (m_Count < 90)
	{
		m_AlfaColor-=0.01f;
	}
	else if (m_Count > 90 && m_Count<180)
	{
		m_AlfaColor += 0.01f;
	}
	else if (m_Count > 180)
	{
		m_Count = 0;
	}
	
	

	m_Sprite->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f,m_AlfaColor));

}

void TitleButton::Draw()
{
	//入力レイアウト
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//シェーダ設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	//マトリクス設定
	Renderer::SetWorldViewProjection2D();

	//基底クラスのメソッド呼び出し
	GameObject::Draw();

}
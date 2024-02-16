#include "main.h"
#include "renderer.h"
#include "hpgage.h"
#include"manager.h"
#include"enemy.h"
#include"sprite.h"
#include"input.h"
#include"player.h"
void HPgage::Init()
{
	VERTEX_3D vertex[4];

	vertex[0].Position = D3DXVECTOR3(m_X, m_Y, 0.0f);
	vertex[0].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	vertex[1].Position = D3DXVECTOR3(m_X+m_Width, m_Y, 0.0f);
	vertex[1].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

	vertex[2].Position = D3DXVECTOR3(m_X, m_Y+m_Height, 0.0f);
	vertex[2].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);

	vertex[3].Position = D3DXVECTOR3(m_X+ m_Width, m_Y+ m_Height, 0.0f);
	vertex[3].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);


	// 頂点バッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);
	

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\gaugeVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\gaugePS.cso");

	m_Hp = m_HpMax = m_BeforHp = 100;


	
	//AddComponent<Sprite>()->Init(200.0f, 100.0f, 300.0f, 200.0f, "asset/texture/grass.jpg");



}

void HPgage::Uninit()
{
	

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

	GameObject::Uninit();
}

void HPgage::Update()
{
	
	GameObject::Update();
	Scene* scene = Manager::GetScene();
	Enemy* enemy = scene->GetGameObject<Enemy>();
	Player* player = scene->GetGameObject<Player>();

	if (m_Hp > m_HpMax)
	{
		m_Hp = m_HpMax;
	}

	if (m_Hp != m_BeforHp)
	{
		m_BeforHp -= 1.0f;
	}
}

void HPgage::Draw()
{
	//入力レイアウト
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//シェーダ設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	//マトリクス設定
	Renderer::SetWorldViewProjection2D();

	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	// マテリアル設定
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	Renderer::SetMaterial(material);

	// テクスチャ設定
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);

	//HPパラメータ設定
	PARAMETER param;
	param.hitpoint.x = m_Hp;
	param.hitpoint.y = m_HpMax;
	param.hitpoint.z = m_BeforHp;
	param.basecolor = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f); //緑
	param.lostColor = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f); //灰
	param.dissColor = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f); //赤
	Renderer::SetParameter(param);

	// プリミティブトポロジ設定
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// ポリゴン描画
	Renderer::GetDeviceContext()->Draw(4, 0);

	//基底クラスのメソッド呼び出し
	GameObject::Draw();

}
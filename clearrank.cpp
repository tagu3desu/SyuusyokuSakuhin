#include "main.h"
#include "renderer.h"
#include"sprite.h"
#include"clearrank.h"
#include"input.h"
#include"timenumber.h"
#include"gametexturemanager.h"
#include"manager.h"

void ClearRank::Init()
{
	VERTEX_3D vertex[4];

	//頂点バッファ設定
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	//テクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/UI/rank.png",
		NULL,
		NULL,
		&m_Texture,
		NULL);
	assert(m_Texture);

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\unlitTexturePS.cso");

}

void ClearRank::Uninit()
{
	m_VertexBuffer->Release();
	m_Texture->Release();

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

	GameObject::Uninit();
}

void ClearRank::Update()
{

	GameObject::Update();

}

void ClearRank::Draw()
{
	Scene* scene = Manager::GetScene();
	GameTexture* gametexture = scene->GetGameObject<GameTexture>();

	int count = m_Rank;



	//入力レイアウト
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//シェーダ設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	//マトリクス設定
	Renderer::SetWorldViewProjection2D();

	//基底クラスのメソッド呼び出し
	//GameObject::Draw();
	// 
	//頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	//マテリアル設定
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	if (m_Rank == 0) //S
	{
		m_RankColor = D3DXCOLOR(1.0f, 0.9f, 0.0f, 1.0f);
	}
	if (m_Rank == 1) //A
	{
		m_RankColor = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	}
	if (m_Rank == 2) //B
	{
		m_RankColor = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);

	}
	if (m_Rank == 3) //C
	{
		m_RankColor = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
	}
	if (m_Rank == 4) //D
	{
		m_RankColor = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
	}
	if (m_Rank == 5) //E
	{
		m_RankColor = D3DXCOLOR(0.0f, 0.7f, 0.0f, 1.0f);
	}
	material.Diffuse = m_RankColor; 
	material.TextureEnable = true;
	Renderer::SetMaterial(material);


	//テクスチャ設定
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);

	//プリミティブトポロジ設定
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);




	
	for (int i = 0; i < 1; i++) {


		//m_X = m_PosX  * 25.0f; //1719
		/*float height = 65.0f;
		float width = 45.0f;*/
		float height = 165.0f;
		float width = 185.0f;
		//テクスチャ座標算出
		int number = count % 6;
		count /= 6;
		float x = number % 2/*横分割*/ * (1.0f / 2);//横分割
		float y = number / 3/*横分割*/ * (1.0f / 3);//縦分割

		//頂点データ書き換え
		D3D11_MAPPED_SUBRESOURCE msr;
		Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

		VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

		vertex[0].Position = D3DXVECTOR3(m_X, m_Y, 0.0f);	//左奥
		vertex[0].Normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[0].TexCoord = D3DXVECTOR2(x, y);

		vertex[1].Position = D3DXVECTOR3(m_X + width, m_Y, 0.0f);	//右奥
		vertex[1].Normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[1].TexCoord = D3DXVECTOR2(x + 0.5f, y);

		vertex[2].Position = D3DXVECTOR3(m_X, m_Y + height, 0.0f);
		vertex[2].Normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[2].TexCoord = D3DXVECTOR2(x, y + (1.0f/3.0f));

		vertex[3].Position = D3DXVECTOR3(m_X + width, m_Y + height, 0.0f);
		vertex[3].Normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[3].TexCoord = D3DXVECTOR2(x + 0.5f, y + (1.0f / 3.0f));

		Renderer::GetDeviceContext()->Unmap(m_VertexBuffer, 0);



		//ポリゴン描画
		Renderer::GetDeviceContext()->Draw(4, 0);



	}

}
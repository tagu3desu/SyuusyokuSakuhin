#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "trail.h"
#include "scene.h"
#include"player.h"
#include"input.h"



void Trail::Init()
{
	Scene* scene = Manager::GetScene();
	//SwordTopVertex* toppostion = scene->GetGameObject<SwordTopVertex>();
	//Sword* bottomposition = scene->GetGameObject<Sword>();
	// 頂点バッファ生成
	{
		for (int i = 0; i < VERTEX_NUMBER / 2; i++)
		{

			m_Vertex[i * 2].Position = D3DXVECTOR3((i - 10) * 1.0f, 2.0f, 0);
			m_Vertex[i * 2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);//法線ベクトル
			m_Vertex[i * 2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
			m_Vertex[i * 2].TexCoord = D3DXVECTOR2(i * 1.0f, 0.0f);

			m_Vertex[i * 2 + 1].Position = D3DXVECTOR3((i - 10) * 1.0f, 2.0f, 5.0f);
			m_Vertex[i * 2 + 1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);//法線ベクトル
			m_Vertex[i * 2 + 1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
			m_Vertex[i * 2 + 1].TexCoord = D3DXVECTOR2(i * 1.0f, 1.0f);

		}

		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.ByteWidth = sizeof(VERTEX_3D) * VERTEX_NUMBER;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = m_Vertex;

		Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);
	}


	// テクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/Effect/Trail.png",
		NULL,
		NULL,
		&m_Texture,
		NULL);
	assert(m_Texture);

	

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\unlitTextureVS.cso");
	Renderer::CreatePixelShader(&m_PixelShader, "shader\\unlitTexturePS.cso");

	GameObject::Init();
}




void Trail::Uninit()
{

	m_VertexBuffer->Release();
	m_Texture->Release();
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

	GameObject::Uninit();
}


void Trail::Update()
{

}


void Trail::Draw()
{
	
	
	Renderer::SetRssetEnable(true);
	GameObject::Draw();

	


	if (m_TrailDrawFlag)
	{
		
		if (m_TopVertexArray.size() >= VERTEX_NUMBER / 2)
		{
			m_TopVertexArray.pop();
			m_BottomVertexArray.pop();
		}
		m_TopVertexArray.push(m_TopVertex);
		m_BottomVertexArray.push(m_BottomVertex);

		m_TopVertexArrayCopy = m_TopVertexArray;
		m_BottomVertexArrayCopy = m_BottomVertexArray;

		//// 頂点データ書き換え// ここにメンバ変数で保存した頂点データを変える
		D3D11_MAPPED_SUBRESOURCE msr;
		Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
		VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

		////キュー
		for (int i = 0; i < VERTEX_NUMBER / 2; i++)
		{
			if (!m_TopVertexArrayCopy.empty())
			{
				vertex[i * 2].Position = m_TopVertexArrayCopy.front();
				vertex[i * 2].TexCoord = D3DXVECTOR2(i * 1.0f, 0.0f);
				vertex[i * 2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
				vertex[i * 2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);//法線ベクトル
				m_TopVertexArrayCopy.pop();
			}

			if (!m_BottomVertexArrayCopy.empty())
			{
				vertex[i * 2 + 1].Position = m_BottomVertexArrayCopy.front();
				vertex[i * 2 + 1].TexCoord = D3DXVECTOR2(i * 1.0f, 1.0f);
				vertex[i * 2 + 1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
				vertex[i * 2 + 1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);//法線ベクトル
				m_BottomVertexArrayCopy.pop();
			}

		}

		Renderer::GetDeviceContext()->Unmap(m_VertexBuffer, 0);




		// 入力レイアウト設定
		Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

		// シェーダ設定
		Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
		Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);




		// マトリクス設定
		D3DXMATRIX world, scale, rot, trans;
		D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
		D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
		D3DXMatrixTranslation(&trans, m_Position.x , m_Position.y , m_Position.z);
		world = scale * rot * trans;
		Renderer::SetWorldMatrix(&world);



		// 頂点バッファ設定
		UINT stride = sizeof(VERTEX_3D);
		UINT offset = 0;
		Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);



		// マテリアル設定
		MATERIAL material;
		ZeroMemory(&material, sizeof(material));
		//material.Diffuse = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		material.TextureEnable = true;
		Renderer::SetMaterial(material);

		// テクスチャ設定
		Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);


		// プリミティブトポロジ設定
		Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);


		Renderer::SetATCEnable(true);
		// ポリゴン描画
		if (m_TrailEnable)
		{
			Renderer::GetDeviceContext()->Draw(m_BottomVertexArray.size() * 2, 0);

		}
		
		Renderer::SetATCEnable(false);
		Renderer::SetRssetEnable(false);
	}
	else
	{
		while (!m_TopVertexArray.empty()) {
			m_TopVertexArray.pop();
		}
		while (!m_BottomVertexArray.empty()){
			m_BottomVertexArray.pop();
		}
		while(!m_BottomVertexArrayCopy.empty()){
			m_BottomVertexArrayCopy.pop();
		}
		while (!m_TopVertexArrayCopy.empty()) {
			m_TopVertexArrayCopy.pop();
		}
	}
	
}


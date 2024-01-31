#include "main.h"
#include "renderer.h"
#include"grass.h"
#include"scene.h"
#include"manager.h"
#include"camera.h"


void Grass::Init()
{
	VERTEX_3D vertex[4];

	vertex[0].Position = D3DXVECTOR3(-1.0f, 2.0f, 0.0f);	//左奥
	vertex[0].Normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	vertex[1].Position = D3DXVECTOR3(1.0f, 2.0f, 0.0f);	//右奥
	vertex[1].Normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

	vertex[2].Position = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
	vertex[2].Normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);

	vertex[3].Position = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	vertex[3].Normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファ設定
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags =0;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	//テクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/grass.png",
		NULL,
		NULL,
		&m_Texture,
		NULL);
	assert(m_Texture);

	//ストラクチャードバッファー
	{
		D3DXVECTOR3* pos = new D3DXVECTOR3[1000000];

		int i = 0;
		for (int x = 0; x < 1000; x++)
		{
			for (int z = 0; z < 1000; z++)
			{
				pos[i] = D3DXVECTOR3(x, 0.0f, z);
				i++;
			}
		}


		//ストラクチャードバッファ生成
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(D3DXVECTOR3) * 1000000;
		bd.StructureByteStride = sizeof(D3DXVECTOR3);
		bd.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		bd.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = pos;

		Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_PositionBuffer);

		delete[] pos;

		//シェーダーリソースビュー
		D3D11_SHADER_RESOURCE_VIEW_DESC srvd;
		ZeroMemory(&srvd, sizeof(srvd));
		srvd.Format = DXGI_FORMAT_UNKNOWN;
		srvd.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
		srvd.Buffer.FirstElement = 0;
		srvd.Buffer.NumElements = 1000000;
		Renderer::GetDevice()->CreateShaderResourceView(m_PositionBuffer, &srvd, &m_PositionSRV);

		
	}
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\unlitTextureVS2.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\unlitTexturePS2.cso");

	m_Scale = D3DXVECTOR3(5.0f, 5.0f, 0.0f);
}
void Grass::Load()
{

}

void Grass::Unload()
{

}

void Grass::Uninit()
{
	m_VertexBuffer->Release();
	m_Texture->Release();

	m_PositionBuffer->Release();
	m_PositionSRV->Release();

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void Grass::Update()
{

}

void Grass::Draw()
{
	

	


	//入力レイアウト
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//シェーダ設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	//ビルボードの処理
	//カメラのビューマトリクス取得
	//Scene* scene = Manager::GetScene();
	//Camera* camera = scene->GetGameObject<Camera>();
	//D3DXMATRIX view = camera->GetViewMatrix();

	////ビューの逆行列
	//D3DXMATRIX invView;
	//D3DXMatrixInverse(&invView, NULL, &view);//逆行列
	//invView._41 = 0.0f;
	//invView._42 = 0.0f;
	//invView._43 = 0.0f;

	//マトリクス設定
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(&world);



	//頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	//マテリアル設定
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	material.TextureEnable = true;
	Renderer::SetMaterial(material);

	//テクスチャ設定
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);

	//ストラクチャードバッファ設定
	Renderer::GetDeviceContext()->VSSetShaderResources(2, 1, &m_PositionSRV);
	//プリミティブトポロジ設定
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	Renderer::SetATCEnable(true);

	//ポリゴン描画
	//Renderer::GetDeviceContext()->Draw(4, 0); //ドローコール
	Renderer::GetDeviceContext()->DrawInstanced(4, 10000, 0, 0);

	Renderer::SetATCEnable(false);
}
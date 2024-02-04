
#include "main.h"
#include "renderer.h"
#include "campField.h"

ID3D11Buffer* BaseCamp::m_VertexBuffer{};
ID3D11Buffer* BaseCamp::m_IndexBuffer{};
ID3D11ShaderResourceView* BaseCamp::m_Texture{};
VERTEX_3D					BaseCamp::m_Vertex[MESH_COUNT_X][MESH_COUNT_Z]{};

float g_BaseCampHeight[MESH_COUNT_X][MESH_COUNT_Z]
{
	{15.0f,15.0f,15.0f,15.0f,15.0f,15.0f,15.0f,15.0f,15.0f,15.0f},
	{15.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,15.0f},
	{0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,15.0f},
	{0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,15.0f},
	{0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,15.0f},
	{0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,15.0f},
	{0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,15.0f},
	{0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,15.0f},
	{15.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,15.0f},
	{15.0f,15.0f,15.0f,15.0f,15.0f,15.0f,15.0f,15.0f,15.0f,15.0f},
	
};

void BaseCamp::Init()
{
	m_DepthEnable = true;
	m_ReflectEnable = true;

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\DepthShadowMappingVS.cso");
	Renderer::CreatePixelShader(&m_PixelShader, "shader\\DepthShadowMappingPS.cso");
}

void BaseCamp::Load()
{
	// 頂点バッファ生成
	{
		for (int x = 0; x <= (MESH_COUNT_X-1); x++)
		{
			for (int z = 0; z <= (MESH_COUNT_Z-1); z++)
			{
				m_Vertex[x][z].Position = D3DXVECTOR3((x - 10) * 5.0f, g_BaseCampHeight[x][z], (z - 10) * -5.0f);
				m_Vertex[x][z].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);//法線ベクトル
				m_Vertex[x][z].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
				m_Vertex[x][z].TexCoord = D3DXVECTOR2(x * 0.5f, z * 0.5f);
			}
		}
		//法線ベクトル産出
		for (int x = 1; x <= (MESH_COUNT_X-2); x++)
		{
			for (int z = 1; z <= (MESH_COUNT_Z/2 - 1); z++)
			{
				D3DXVECTOR3 vx, vz, vn;
				vx = m_Vertex[x + 1][z].Position - m_Vertex[x - 1][z].Position;
				vz = m_Vertex[x][z - 1].Position - m_Vertex[x][z + 1].Position;

				D3DXVec3Cross(&vn, &vz, &vx);//外積
				D3DXVec3Normalize(&vn, &vn);//正規化(長さ1にする)
				m_Vertex[x][z].Normal = vn;
			}
		}

		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(VERTEX_3D) * MESH_COUNT_X * MESH_COUNT_Z;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = m_Vertex;

		Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);
	}




	// インデックスバッファ生成
	{
		unsigned int index[((MESH_COUNT_X+1) * 2) * (MESH_COUNT_X -1) - 2];

		int i = 0;
		for (int x = 0; x < (MESH_COUNT_X-1); x++)
		{
			for (int z = 0; z < MESH_COUNT_X; z++)
			{
				index[i] = x * MESH_COUNT_X + z;
				i++;

				index[i] = (x + 1) * MESH_COUNT_X + z;
				i++;
			}

			if (x == (MESH_COUNT_X-2))
				break;

			index[i] = (x + 1) * MESH_COUNT_X + (MESH_COUNT_X-1);
			i++;

			index[i] = (x + 1) * MESH_COUNT_X;
			i++;
		}

		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(unsigned int) * (((MESH_COUNT_X+1) * 2) * (MESH_COUNT_X-1) - 2);
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = index;

		Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_IndexBuffer);
	}

	

	// テクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/grass.jpg",
		NULL,
		NULL,
		&m_Texture,
		NULL);
	assert(m_Texture);
}

void BaseCamp::Unload()
{
	m_VertexBuffer->Release();
	m_IndexBuffer->Release();
	m_Texture->Release();
}

void BaseCamp::Uninit()
{
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void BaseCamp::Update()
{

}


void BaseCamp::Draw()
{
	GameObject::Draw();

	// 入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	// シェーダ設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);



	// マトリクス設定
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(&world);


	// 頂点バッファ設定
	UINT stride = sizeof( VERTEX_3D );
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers( 0, 1, &m_VertexBuffer, &stride, &offset );

	// インデックスバッファ設定
	Renderer::GetDeviceContext()->IASetIndexBuffer( m_IndexBuffer, DXGI_FORMAT_R32_UINT, 0 );

	// マテリアル設定
	MATERIAL material;
	ZeroMemory( &material, sizeof(material) );
	material.Diffuse = D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f );
	material.TextureEnable = true;
	Renderer::SetMaterial( material );

	// テクスチャ設定
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);

	// プリミティブトポロジ設定
	Renderer::GetDeviceContext()->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP );

	// ポリゴン描画
	Renderer::GetDeviceContext()->DrawIndexed(((MESH_COUNT_X+1) * 2) * (MESH_COUNT_X-1) - 2, 0, 0);

}

float BaseCamp::GetHeight(D3DXVECTOR3 Position)
{

	int x,z;

	//ブロック番号算術
	x = Position.x / 5.0f + 10.0f;
	z = Position.z / -5.0f + 10.0f;

	D3DXVECTOR3 pos0, pos1,pos2, pos3;

	pos0 = m_Vertex[x][z].Position;
	pos1 = m_Vertex[x + 1][z].Position;
	pos2 = m_Vertex[x][z + 1].Position;
	pos3 = m_Vertex[x + 1][z + 1].Position;

	D3DXVECTOR3 v12, v1p, c;
	v12 = pos2 - pos1;
	v1p = Position - pos1;

	D3DXVec3Cross(&c, &v12, &v1p);

	float py;
	D3DXVECTOR3 n;
	if (c.y > 0.0f)
	{
		//左上ポリゴン
		D3DXVECTOR3 v10;
		v10 = pos0 - pos1;
		D3DXVec3Cross(&n, &v10, &v12);
	}
	else
	{
		//右下ポリゴン
		D3DXVECTOR3 v13;
		v13 = pos3 - pos1;
		D3DXVec3Cross(&n, &v12, &v13);
	}

	//高さ取得
	py = -((Position.x - pos1.x) * n.x + (Position.z - pos1.z) * n.z) / n.y + pos1.y;

	return py;
}

D3DXVECTOR3 BaseCamp::GetCenterPosition()
{
	// マップの幅と高さ
	float mapWidth = MESH_COUNT_X * 5.0f;  // メッシュの数 * メッシュの幅
	float mapHeight = MESH_COUNT_Z * 5.0f; // メッシュの数 * メッシュの高さ

	// マップの中心座標を計算
	float centerX = -mapWidth / 2.0f;
	float centerZ = mapHeight / 2.0f;

	// マップの中心座標を返す
	return D3DXVECTOR3(centerX, 0.0f, centerZ); 
}

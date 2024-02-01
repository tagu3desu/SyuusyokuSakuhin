#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "trail.h"
#include "scene.h"
#include"player.h"

#include"input.h"
#include"trailtexture.h"
#include"wepon_sword.h"

void Trail::Init()
{
	Scene* scene = Manager::GetScene();
	Player* player = scene->GetGameObject<Player>();

	// 頂点バッファ生成
	{
		for (int i = 0; i <= VERTEX_NUMBER; i++)
		{
		
				m_Vertex[i* 2].Position = D3DXVECTOR3((i - 10) * 5.0f, 2.0f,  0);
				m_Vertex[i* 2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);//法線ベクトル
				m_Vertex[i* 2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
				m_Vertex[i* 2].TexCoord = D3DXVECTOR2(i * 1.0f,  0.0f);

				m_Vertex[i * 2 + 1].Position = D3DXVECTOR3((i - 10) * 5.0f, 2.0f, 5.0f);
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


	// インデックスバッファ生成
	//{
	//	unsigned int index[((VERTEX_NUMBER + 2) * 2) * VERTEX_NUMBER - 2];

	//	int i = 0;
	//	for (int x = 0; x < VERTEX_NUMBER; x++)
	//	{
	//		for (int z = 0; z < VERTEX_NUMBER + 1; z++)
	//		{
	//			index[i] = x * (VERTEX_NUMBER + 1) + z;
	//			i++;

	//			index[i] = (x + 1) * (VERTEX_NUMBER + 1) + z;
	//			i++;
	//		}

	//		if (x == VERTEX_NUMBER - 1)
	//			break;

	//		//縮退ポリゴン
	//		index[i] = (x + 1) * (VERTEX_NUMBER + 1) + VERTEX_NUMBER;
	//		i++;

	//		index[i] = (x + 1) * (VERTEX_NUMBER + 1);
	//		i++;
	//	}

	//	D3D11_BUFFER_DESC bd;
	//	ZeroMemory(&bd, sizeof(bd));
	//	bd.Usage = D3D11_USAGE_DYNAMIC;
	//	bd.ByteWidth = sizeof(unsigned int) * (((VERTEX_NUMBER + 2) * 2) * VERTEX_NUMBER - 2);
	//	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	//	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	//	D3D11_SUBRESOURCE_DATA sd;
	//	ZeroMemory(&sd, sizeof(sd));
	//	sd.pSysMem = index;

	//	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_IndexBuffer);
	//}


	// テクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/vertex.png",
		NULL,
		NULL,
		&m_Texture,
		NULL);
	assert(m_Texture);

	

	//// テクスチャ読み込み
	//D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
	//	"asset/texture/waternormal.png",
	//	NULL,
	//	NULL,
	//	&m_TextureNormal,
	//	NULL);
	//assert(m_TextureNormal);

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\vertexLightingVS.cso");
	Renderer::CreatePixelShader(&m_PixelShader, "shader\\vertexLightingPS.cso");

	GameObject::Init();
}


void Trail::Uninit()
{

	m_VertexBuffer->Release();
	//m_IndexBuffer->Release();
	m_Texture->Release();
	//m_TextureNormal->Release();

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

	GameObject::Uninit();
}


void Trail::Update()
{
	Scene* scene = Manager::GetScene();
	TrailTexture* toppostion = scene->GetGameObject<TrailTexture>();
	Sword* bottomposition = scene->GetGameObject<Sword>();


	
	ImGui::SetNextWindowSize(ImVec2(400, 250));
	ImGui::Begin("Top");
	while (!m_TopVertexArray.empty()) {
		D3DXVECTOR3 element = m_TopVertexArray.front();
		ImGui::Text("Element : (%f, %f, %f)", element.x, element.y, element.z);
		m_TopVertexArray.pop();
	}
	ImGui::End();

	ImGui::SetNextWindowSize(ImVec2(400, 250));
	ImGui::Begin("Bottom");
	while (!m_BottomVertexArray.empty()) {
		D3DXVECTOR3 element = m_BottomVertexArray.front();
		ImGui::Text("Element : (%f, %f, %f)", element.x, element.y, element.z);
		m_BottomVertexArray.pop();
	}
	ImGui::End();

	

	
	
	

	//size_t count = m_TopVertexArray.size();

	//if (count > 10)
	//{
	//	m_TopVertexArray.clear();
	//	m_BottomVertexArray.clear();
	//}
	//
	//


	//ImGui::SetNextWindowSize(ImVec2(400, 250));
	//ImGui::Begin("Count");
	//for (int i = 0; i < m_TopVertexArray.size(); ++i)
	//{
	//	ImGui::Text("Size: %zu", count);
	//}

	//ImGui::End();

	//ImGui::SetNextWindowSize(ImVec2(400, 250));
	//ImGui::Begin("TopVertexArray");
	//for (int i = 0; i < m_TopVertexArray.size(); ++i)
	//{
	//	ImGui::Text("TopVertex %d: (%f, %f, %f)", i, m_TopVertexArray[i].x, m_TopVertexArray[i].y, m_TopVertexArray[i].z);
	//}

	//ImGui::End();

	//ImGui::SetNextWindowSize(ImVec2(400, 250));
	//ImGui::Begin("BottomVertexArray");
	//for (int i = 0; i < m_TopVertexArray.size(); ++i)
	//{
	//	ImGui::Text("BottomVertex %d: (%f, %f, %f)", i, m_BottomVertexArray[i].x, m_BottomVertexArray[i].y, m_BottomVertexArray[i].z);
	//}

	//ImGui::End();

}


void Trail::Draw()
{
	Scene* scene = Manager::GetScene();
	TrailTexture* toppostion = scene->GetGameObject<TrailTexture>();
	Sword* bottomposition = scene->GetGameObject<Sword>();
	Player* player = scene->GetGameObject<Player>();
	

	GameObject::Draw();

	//// 頂点データ書き換え// ここにメンバ変数で保存した頂点データを変える
	D3D11_MAPPED_SUBRESOURCE msr;
	Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

	
	
	if (m_TopVertexArray.size() > 10)
	{
		m_TopVertexArray.pop();
		m_BottomVertexArrayCopy.pop();
	}


	////キュー
	for (int i = 0; i < KEEP_VERTEX; i++)
	{	
		m_TopVertexArray.push(toppostion->GetTopVertexPostion());
		m_BottomVertexArray.push(bottomposition->GetBottomVertexPostion());


		vertex[i * 2].Position = m_TopVertexArray.front();
		vertex[i * 2].TexCoord = D3DXVECTOR2(i * 1.0f, 0.0f);
		vertex[i * 2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[i * 2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);//法線ベクトル

	
		vertex[i * 2 + 1].Position = m_BottomVertexArray.front();
		vertex[i * 2 + 1].TexCoord = D3DXVECTOR2(i * 1.0f, 1.0f);
		vertex[i * 2 + 1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[i * 2 + 1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);//法線ベクトル
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
	/*D3DXMatrixTranslation(&trans, m_Position.x , m_Position.y , m_Position.z);*/
	D3DXMatrixTranslation(&trans, befortopvertex.x, befortopvertex.y, befortopvertex.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(&world);



	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	// インデックスバッファ設定
	//Renderer::GetDeviceContext()->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// マテリアル設定
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	material.TextureEnable = true;
	Renderer::SetMaterial(material);

	// テクスチャ設定
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);
	//Renderer::GetDeviceContext()->PSSetShaderResources(2, 1, &m_TextureNormal);

	// プリミティブトポロジ設定
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// ポリゴン描画
	//Renderer::GetDeviceContext()->DrawIndexed(((VERTEX_NUMBER + 2) * 2) * VERTEX_NUMBER - 2, 0, 0);
	Renderer::GetDeviceContext()->Draw(VERTEX_NUMBER*4 , 0);
}


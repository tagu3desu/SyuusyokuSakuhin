#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "trail.h"
#include "scene.h"
#include"player.h"
#include"input.h"
#include"wepon_sword.h"


void Trail::Init()
{
	Scene* scene = Manager::GetScene();
	//SwordTopVertex* toppostion = scene->GetGameObject<SwordTopVertex>();
	//Sword* bottomposition = scene->GetGameObject<Sword>();
	// ���_�o�b�t�@����
	{
		for (int i = 0; i < KEEP_VERTEX / 2; i++)
		{

			m_Vertex[i * 2].Position = D3DXVECTOR3((i - 10) * 5.0f, 2.0f, 0);
			m_Vertex[i * 2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);//�@���x�N�g��
			m_Vertex[i * 2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
			m_Vertex[i * 2].TexCoord = D3DXVECTOR2(i * 1.0f, 0.0f);

			m_Vertex[i * 2 + 1].Position = D3DXVECTOR3((i - 10) * 5.0f, 2.0f, 5.0f);
			m_Vertex[i * 2 + 1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);//�@���x�N�g��
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




	// �e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/trail.png",
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
	
	Scene* scene = Manager::GetScene();
	SwordTopVertex* swordtopvertex = scene->GetGameObject<SwordTopVertex>();
	Sword* bottomposition = scene->GetGameObject<Sword>();
	Player* player = scene->GetGameObject<Player>();
	
	
	Renderer::SetRssetEnable(true);
	GameObject::Draw();

	if (m_TopVertexArray.size() >= VERTEX_NUMBER / 2)
	{
		m_TopVertexArray.pop();
		m_BottomVertexArray.pop();
	}


	m_TopVertexArray.push(swordtopvertex->GetTopVertexPostion());
	m_BottomVertexArray.push(bottomposition->GetBottomVertexPostion());




	m_TopVertexArrayCopy = m_TopVertexArray;
	m_BottomVertexArrayCopy = m_BottomVertexArray;

	if (player->GetPlayerAttack())
	{

		//// ���_�f�[�^��������// �����Ƀ����o�ϐ��ŕۑ��������_�f�[�^��ς���
		D3D11_MAPPED_SUBRESOURCE msr;
		Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
		VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

		////�L���[
		for (int i = 0; i < VERTEX_NUMBER / 2; i++)
		{
			if (!m_TopVertexArrayCopy.empty())
			{
				vertex[i * 2].Position = m_TopVertexArrayCopy.front();
				vertex[i * 2].TexCoord = D3DXVECTOR2(/*i * 1.0f*/0.2f, 0.0f);
				vertex[i * 2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
				vertex[i * 2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);//�@���x�N�g��
				m_TopVertexArrayCopy.pop();
			}

			if (!m_BottomVertexArrayCopy.empty())
			{
				vertex[i * 2 + 1].Position = m_BottomVertexArrayCopy.front();
				vertex[i * 2 + 1].TexCoord = D3DXVECTOR2(/*i * 1.0f*/0.2f, 1.0f);
				vertex[i * 2 + 1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
				vertex[i * 2 + 1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);//�@���x�N�g��
				m_BottomVertexArrayCopy.pop();
			}

		}

		Renderer::GetDeviceContext()->Unmap(m_VertexBuffer, 0);




		// ���̓��C�A�E�g�ݒ�
		Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

		// �V�F�[�_�ݒ�
		Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
		Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);




		// �}�g���N�X�ݒ�
		D3DXMATRIX world, scale, rot, trans;
		D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
		D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
		D3DXMatrixTranslation(&trans, m_Position.x , m_Position.y , m_Position.z);
		world = scale * rot * trans;
		Renderer::SetWorldMatrix(&world);



		// ���_�o�b�t�@�ݒ�
		UINT stride = sizeof(VERTEX_3D);
		UINT offset = 0;
		Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);



		// �}�e���A���ݒ�
		MATERIAL material;
		ZeroMemory(&material, sizeof(material));
		material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		material.TextureEnable = true;
		Renderer::SetMaterial(material);

		// �e�N�X�`���ݒ�
		Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);


		// �v���~�e�B�u�g�|���W�ݒ�
		Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);



		// �|���S���`��
		Renderer::GetDeviceContext()->Draw(VERTEX_NUMBER, 0);
		Renderer::SetRssetEnable(false);
	}

	
}


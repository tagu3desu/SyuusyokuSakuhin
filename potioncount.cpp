#include "main.h"
#include "renderer.h"
#include"potioncount.h"
#include"sprite.h"
#include"potioncount.h"
#include"input.h"
void PotionCount::Init()
{
	VERTEX_3D vertex[4];

	

	//���_�o�b�t�@�ݒ�
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

	//�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/score.png",
		NULL,
		NULL,
		&m_Texture,
		NULL);
	assert(m_Texture);

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\unlitTexturePS.cso");

	
	m_Potioncount = 5;
	

}

void PotionCount::Uninit()
{
	m_VertexBuffer->Release();
	m_Texture->Release();

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

	GameObject::Uninit();
}

void PotionCount::Update()
{
	
	GameObject::Update();
	
}

void PotionCount::Draw()
{


	//���̓��C�A�E�g
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//�V�F�[�_�ݒ�
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	//�}�g���N�X�ݒ�
	Renderer::SetWorldViewProjection2D();

	//���N���X�̃��\�b�h�Ăяo��
	//GameObject::Draw();
	// 
	//���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	//�}�e���A���ݒ�
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	material.TextureEnable = true;
	Renderer::SetMaterial(material);


	//�e�N�X�`���ݒ�
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);

	//�v���~�e�B�u�g�|���W�ݒ�
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);


	int count = m_Potioncount;

	for (int i = 0; i < 1; i++) {
		//���_���W�Y�o
		/*float vx = 1153.0f -i * 30.0f;
		float vy = 645.0f;*/

		

		float height = 50.0f;
		float width = 35.0f;
		//�e�N�X�`�����W�Z�o
		int number = count % 10;
		count /= 10;
		float x = number % 5/*������*/ * (1.0f / 5);//������
		float y = number / 5/*������*/ * (1.0f / 5);//�c����

		//���_�f�[�^��������
		D3D11_MAPPED_SUBRESOURCE msr;
		Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

		VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

		vertex[0].Position = D3DXVECTOR3(m_X, m_Y, 0.0f);	//����
		vertex[0].Normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[0].TexCoord = D3DXVECTOR2(x, y);

		vertex[1].Position = D3DXVECTOR3(m_X +width, m_Y, 0.0f);	//�E��
		vertex[1].Normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[1].TexCoord = D3DXVECTOR2(x + 0.2f, y);

		vertex[2].Position = D3DXVECTOR3(m_X, m_Y +height, 0.0f);
		vertex[2].Normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[2].TexCoord = D3DXVECTOR2(x, y + 0.2f);

		vertex[3].Position = D3DXVECTOR3(m_X +width, m_Y +height, 0.0f);
		vertex[3].Normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[3].TexCoord = D3DXVECTOR2(x + 0.2f, y + 0.2f);

		Renderer::GetDeviceContext()->Unmap(m_VertexBuffer, 0);

		

		//�|���S���`��
		Renderer::GetDeviceContext()->Draw(4, 0);

	}
	
	

}
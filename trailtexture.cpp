#include "main.h"
#include "renderer.h"
#include"manager.h"
#include"trailtexture.h"
#include"scene.h"
#include"camera.h"
#include"wepon_sword.h"
#include "player.h"
ID3D11Buffer* TrailTexture::m_VertexBuffer;
ID3D11ShaderResourceView* TrailTexture::m_Texture;

void TrailTexture::Init()
{
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\unlitTexturePS.cso");

	m_Scale = D3DXVECTOR3(0.1f, 0.1f, 0.1f);
	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.7f);
}
void TrailTexture::Load()
{
	VERTEX_3D vertex[4];

	vertex[0].Position = D3DXVECTOR3(-1.0f, 0.0f, 1.0f);	//����
	vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	vertex[1].Position = D3DXVECTOR3(1.0f, 0.0f, 1.0f);	//�E��
	vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

	vertex[2].Position = D3DXVECTOR3(-1.0f, 0.0f, -1.0f);
	vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);

	vertex[3].Position = D3DXVECTOR3(1.0f, 0.0f, -1.0f);
	vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@�ݒ�
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

	//�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/sea.jpg",
		NULL,
		NULL,
		&m_Texture,
		NULL);
	assert(m_Texture);

}

void TrailTexture::Unload()
{
	m_VertexBuffer->Release();
	m_Texture->Release();
}

void TrailTexture::Uninit()
{
	

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void TrailTexture::Update()
{
	Scene* scene =  Manager::GetScene();
	Sword* sword = scene->GetGameObject<Sword>();
	//Player* player = scene->GetGameObject<Player>();
	m_Parent = sword->GetMatrix();
	

	m_TopVertex = ExtractTranslationFromMatrix(m_Matrix);
	


	////GUI�Ƀp�����[�^�\��
	//ImGui::SetNextWindowSize(ImVec2(400, 250));
	//ImGui::Begin("Top");
	//ImGui::InputFloat3("Position", m_Position);
	//ImGui::InputFloat3("Ratation", m_Rotation);
	//ImGui::InputFloat3("Scale", m_Scale);
	//ImGui::End();

}

void TrailTexture::Draw()
{

	//���̓��C�A�E�g
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//�V�F�[�_�ݒ�
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);


	//�}�g���N�X�ݒ�
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans * m_Parent;
	Renderer::SetWorldMatrix(&world);

	m_Matrix = world;

	//���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	////�}�e���A���ݒ�
	//MATERIAL material;
	//ZeroMemory(&material, sizeof(material));
	//material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//material.TextureEnable = true;
	//Renderer::SetMaterial(material);

	////�e�N�X�`���ݒ�
	//Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);

	////�v���~�e�B�u�g�|���W�ݒ�
	//Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	////�|���S���`��
	//Renderer::GetDeviceContext()->Draw(4, 0);
}
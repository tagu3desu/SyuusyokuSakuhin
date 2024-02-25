#include "main.h"
#include "renderer.h"
#include "staminagage.h"
#include"manager.h"
#include"enemy.h"
#include"sprite.h"
#include"input.h"
#include"player.h"
#include"gametexturemanager.h"
#include"inputx.h"
void Staminagage::Init()
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

	vertex[3].Position = D3DXVECTOR3(m_X+m_Width, m_Y+m_Height, 0.0f);
	vertex[3].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);


	// ���_�o�b�t�@����
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
		"shader\\staminagaugeVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\staminagaugePS.cso");

	m_Scene = Manager::GetScene();
	m_Player = m_Scene->GetGameObject<Player>();

	m_Stamina = m_StaminaMax = m_Player->GetPlayerStamina();
}

void Staminagage::Uninit()
{
	

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

	GameObject::Uninit();
}

void Staminagage::Update()
{
	

	GameObject::Update();
	m_Player = m_Scene->GetGameObject<Player>();
	GameTexture* gamatexture = m_Scene->GetGameObject<GameTexture>();
	
	if (m_Player != nullptr)
	{
		if ((Input::GetKeyPress(VK_LSHIFT) || InputX::IsButtonPressed(0, XINPUT_GAMEPAD_RIGHT_SHOULDER)) && m_Stamina > 0 && m_Player->GetPlayerRun())
		{

			m_Stamina -= 2.0f;
		}
		if (m_Player->GeiPlayerIdle() && m_Stamina <= m_StaminaMax && !m_ZeroStamina)
		{

			m_Stamina += 3.0f;
		}

		if (m_Stamina <= 0)
		{
			m_ZeroStamina = true;
		}

		if (m_ZeroStamina)
		{
			m_FrameWait++;
			if (m_FrameWait > 60)
			{
				m_ZeroStamina = false;
			}
		}

		if (m_Player->GetSuccessGuard())
		{

			SetStaminaPoint(-6.0f);
		}
	}

	

	if (gamatexture->GetGameClear())
	{
		SetDestroy();
	}

}

void Staminagage::Draw()
{
	//���̓��C�A�E�g
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//�V�F�[�_�ݒ�
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	//�}�g���N�X�ݒ�
	Renderer::SetWorldViewProjection2D();

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	// �}�e���A���ݒ�
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	Renderer::SetMaterial(material);

	// �e�N�X�`���ݒ�
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);

	//HP�p�����[�^�ݒ�
	PARAMETER param;
	param.stamina.x = m_Stamina;
	param.stamina.y = m_StaminaMax;
	param.staminabasecolor = D3DXCOLOR(1.0f,0.6f, 0.0f, 1.0f); //�I�����W�H
	param.lostColor = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f); //�D
	Renderer::SetParameter(param);

	// �v���~�e�B�u�g�|���W�ݒ�
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �|���S���`��
	Renderer::GetDeviceContext()->Draw(4, 0);

	//���N���X�̃��\�b�h�Ăяo��
	GameObject::Draw();

}
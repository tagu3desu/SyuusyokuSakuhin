#include"main.h"
#include"renderer.h"
#include"wood.h"

void Wood::Init()
{

	m_Model = new Model();
	m_Model->Load("asset\\model\\object\\wood2.obj");

	m_DepthEnable = true;

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\DepthShadowMappingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\DepthShadowMappingPS.cso");
	m_Scale = D3DXVECTOR3(0.7f, 0.7f, 1.3f);
}

void Wood::Uninit()
{
	m_Model->Unload();
	delete m_Model;

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void Wood::Update()
{
	
}

void Wood::Draw()
{
	GameObject::Draw();
	//���̓��C�A�E�g
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//�V�F�[�_�ݒ�
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	//// �e�N�X�`���ݒ�
	/*ID3D11ShaderResourceView* depthShadowTexture = Renderer::GetDepthShadowTexture();
	Renderer::GetDeviceContext()->PSSetShaderResources(1, 1, &depthShadowTexture);*/

	//�}�g���N�X�ݒ�
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(&world);

	m_Model->Draw();
}
#include"main.h"
#include"manager.h"
#include"renderer.h"
#include"scene.h"
#include"model.h"
#include"boxcomponent.h"



void BoxCollider::Init()
{

	m_Model = new Model();
	m_Model->Load("asset\\model\\boxcollider.obj");

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\unlitTexturePS.cso");

	m_collisionSize = 1.0f;
	m_Scale *= m_collisionSize;


	//Scene* scene = Manager::GetScene();
	//auto* player = scene->GetGameObject<Player>();
	//m_Velocity = D3DXVECTOR3(player->GetForward().x, 0.0f, player->GetForward().z * 1.3f);
	//m_Scale = D3DXVECTOR3(0.7f, 0.7f, 0.7f);
}
void BoxCollider::Uninit()
{
	m_Model->Unload();
	delete m_Model;
}
void BoxCollider::Update()
{
	
}

void BoxCollider::Draw()
{
	//���̓��C�A�E�g
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//�V�F�[�_�ݒ�
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	// �e�N�X�`���ݒ�
	ID3D11ShaderResourceView* depthShadowTexture = Renderer::GetDepthShadowTexture();
	Renderer::GetDeviceContext()->PSSetShaderResources(1, 1, &depthShadowTexture);

	//�}�g���N�X�ݒ�
	D3DXMATRIX  scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	m_Matrix = scale * rot * trans;
	if (ParentMatrix)
	{
		if (boneEnable)
		{
			m_Matrix *= boneMatrix * ParentMatrix->GetMatrix(); //boneMatrix�Ɛe�q�֌W�̏������킹�Ă�
		}
		else
		{
			m_Matrix *= ParentMatrix->GetMatrix();	//�e�q�֌W����Ă�
		}
		D3DXVec3TransformCoord(&GlobalPosition, &m_Position, &m_Matrix);
	}
	else
	{
		GlobalPosition=m_Position;
	}

	Renderer::SetWorldMatrix(&m_Matrix);

	m_Model->Draw();
}



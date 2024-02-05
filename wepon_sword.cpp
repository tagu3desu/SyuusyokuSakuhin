#include"main.h"
#include"renderer.h"
#include"manager.h"
#include"scene.h"
#include"wepon_sword.h"
#include"player.h"
#include"animationModel.h"
#include"swordtrail.h"
#include"input.h"
#include"enemy.h"
#include"collider.h"

ID3D11Buffer* SwordTopVertex::m_VertexBuffer;



void Sword::Init()
{

	m_Model = new Model();
	m_Model->Load("asset\\model\\MetalSword.obj");

	
	m_DepthEnable = true;

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\unlitTexturePS.cso");

	//�[����
	m_Scale = D3DXVECTOR3(110.0f, 110.0f, 1.0f / 0.01f);
	m_Position = D3DXVECTOR3(20.0f, 6.0f, -14.0f);
	m_Rotation = D3DXVECTOR3(0.5f, 0.0f, 2.0f);


	scene = Manager::GetScene();

	
	//swordcollider = new Collider;
	//swordcollider = scene->AddGameObject<Collider>();
	
}

void Sword::Uninit()
{
	m_Model->Unload();
	delete m_Model;

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void Sword::Update()
{
	Player* player = scene->GetGameObject<Player>();
	Enemy* enemy = scene->GetGameObject<Enemy>();
	

	//swordcollider->SetMatrix(m_Matrix);
	
	
	AnimationModel* animationmodel;
	animationmodel = player->GetAnimationModel();
	BONE* bone;

	if (player->GetSwordDrawn())
	{
		bone = animationmodel->GetBone("mixamorig:RightHandPinky4");
		m_Scale = D3DXVECTOR3(110.0f, 110.0f, 1.0f / 0.01f);
		m_Position = D3DXVECTOR3(11.0f, -1.0f, -1.0f);
		m_Rotation = D3DXVECTOR3(-3.6f, -1.8f, 2.0f);
	}
	else
	{
		bone = animationmodel->GetBone("mixamorig:Hips");
		m_Scale = D3DXVECTOR3(110.0f, 110.0f, 1.0f / 0.01f);
		m_Position = D3DXVECTOR3(20.0f, 6.0f, -14.0f);
		m_Rotation = D3DXVECTOR3(0.5f, 0.0f, 2.0f);
	}
	bone->WorldMatrix;
	m_Parent = animationmodel->ConvertMatrix(bone->WorldMatrix);

	////���̃��[���h���W
	D3DXVECTOR3 worldposition = ExtractTranslationFromMatrix(m_Matrix);


	m_BottomVertex = worldposition;
}

void Sword::Draw()
{
	Scene* scene = Manager::GetScene();
	Player* player = scene->GetGameObject<Player>();
	

	GameObject::Draw();
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
	world = scale * rot * trans * m_Parent * player->GetMatrix();

	m_Matrix = world;

	Renderer::SetWorldMatrix(&world);

	m_Model->Draw();
}

//
void SwordTopVertex::Init()
{
	scene = Manager::GetScene();
	m_Scale = D3DXVECTOR3(0.1f, 0.1f, 0.1f);
	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.7f);
}
void SwordTopVertex::Load()
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
}

void SwordTopVertex::Unload()
{
	m_VertexBuffer->Release();
}

void SwordTopVertex::Uninit()
{
}

void SwordTopVertex::Update()
{
	
	Sword* sword = scene->GetGameObject<Sword>();
	

	m_Parent = sword->GetMatrix();
	m_TopVertex = ExtractTranslationFromMatrix(m_Matrix);
}

void SwordTopVertex::Draw()
{
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
}
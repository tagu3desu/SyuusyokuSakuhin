#include"main.h"
#include"renderer.h"
#include"scene.h"
#include"manager.h"
#include"npcteacher.h"
#include"boxcollider.h"
#include"meshField.h"
#include"camera.h"
#include"player.h"
AnimationModel* NpcTeacher::m_Model{};

void NpcTeacher::Init()
{
	GameObject::Init();

	m_AnimationName = "Idle";
	m_NextAnimationName = "Idle";

	m_Scale = D3DXVECTOR3(0.015f, 0.015f, 0.015f);
	m_Rotation = D3DXVECTOR3(0.0f, 3.0f, 0.0f);

	Renderer::CreateSkiningVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\skiningVertexLightingVS.cso");


	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\VertexLightingPS.cso");

	m_DepthEnable = true;

	m_Time = 0.0f;
	m_BlendTime = 0.0f;
	m_GroundHeight = 0.0f;

	m_Scene = Manager::GetScene();

	m_NpcCollider = m_Scene->AddGameObject<BoxCollider>();
	m_NpcCollider->SetScale(D3DXVECTOR3(160.0f, 180.0f, 160.0f));
	m_NpcCollider->SetPosition(D3DXVECTOR3(0.0f, -10.0f, 0.0f));

}

void NpcTeacher::Load()
{
	m_Model = new AnimationModel();
	m_Model->Load("asset\\model\\npc\\akai_e_espiritu.fbx");
	m_Model->LoadAnimation("asset\\model\\npc\\Unarmed Idle 01.fbx","Idle");
}

void NpcTeacher::Unload()
{
	m_Model->Unload();
	delete m_Model;
}


void NpcTeacher::Uninit()
{
	GameObject::Uninit();
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void NpcTeacher::Update()
{
	GameObject::Update();
	m_Scene = Manager::GetScene();
	m_Player = m_Scene->GetGameObject<Player>();
	//コライダー
	AnimationModel* animationmodel;
	animationmodel = GetAnimationModel();
	m_NpcCollider->SetMatrix(m_Matrix);
	BONE* bodybone;
	bodybone = animationmodel->GetBone("mixamorig:Hips");
	m_NpcCollider->SetBoneEnable(true);
	m_NpcCollider->SetBoneMatrix(animationmodel->ConvertMatrix(bodybone->WorldMatrix));
	SetColliderInfo(m_NpcCollider->GetMatrix());

	if (m_NpcCollider->CollisionChecker(this, m_Player, 0.7f))
	{
		m_Hit = true;
	}
	else
	{
		m_Hit = false;
	}

	if (m_NextAnimationName != "Idle")
	{
		m_AnimationName = m_NextAnimationName;
		m_NextAnimationName = "Idle";
		m_BlendTime = 0.0f;
	}

	//メッシュフィールドとの衝突判定
	float m_GroundHeight = 0.0f;

	MeshField* meshField = m_Scene->GetGameObject<MeshField>();


	if (meshField != nullptr) {

		meshField = m_Scene->GetGameObject<MeshField>();
		m_GroundHeight = meshField->GetHeight(m_Position);

	}

	//重力
	m_Velocity.y -= 0.015f;

	//接地
	if (m_Position.y < m_GroundHeight && m_Velocity.y < 0.0f)
	{

		m_Position.y = m_GroundHeight;
		m_Velocity.y = 0.0f;
	}

}

void NpcTeacher::Draw()
{
	GameObject::Draw();
	MeshField* meshfield = m_Scene->GetGameObject<MeshField>();

	//視錘台カリング
	{

		Camera* camera = m_Scene->GetGameObject<Camera>();

		if (!camera->CheckView(m_Position))
			return;
	}



	//入力レイアウト
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//シェーダ設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	//マトリクス設定
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;

	m_Matrix = world;
	Renderer::SetWorldMatrix(&world);



	m_Model->Update(m_AnimationName.c_str(), m_Time, m_NextAnimationName.c_str(), m_Time, m_BlendTime);
	m_Time += 0.5;

	if (m_BlendTime < 1.0f)
	{
		m_BlendTime += 0.1f;
	}

	m_Model->Draw();
}
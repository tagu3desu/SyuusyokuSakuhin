#include"main.h"
#include"renderer.h"
#include"enemy2.h"
#include"manager.h"
#include"scene.h"
#include"camera.h"
#include"animationModel.h"
#include"meshField.h"
AnimationModel* Enemy2::m_Model{};
//Model* Enemy::m_Model{};

void Enemy2::Init()
{
	GameObject::Init();

	m_AnimationName = "Idle";
	m_NextAnimationName = "Idle";

	m_Scale = D3DXVECTOR3(0.03f, 0.03f, 0.03f);
	

	m_DepthEnable = true;
	

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\pixelLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\dissolvePS.cso");

	m_Threshold = 0.0f;
	m_Time = 0.0f;
	m_BlendTime = 0.0f;
	m_Rotation = D3DXVECTOR3(0.0f, 3.0f, 0.0f);
}

void Enemy2::Load()
{
	m_Model = new AnimationModel();
	m_Model->Load("asset\\model\\Mutant.fbx");
	m_Model->LoadAnimation("asset\\model\\Mutant Breathing Idle.fbx","Idle");
	
}

void Enemy2::Uninit()
{
	GameObject::Uninit();
	m_DisolveTexture->Release();



	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void Enemy2::Unload()
{
	m_Model->Unload();
	delete m_Model;
}

void Enemy2::Update()
{
	m_move = false;
	GameObject::Update();

	Scene* scene = Manager::GetScene();

	switch (m_EnemyState)
	{
	case ENEMY2_STATE_GROUND:
		UpdateGround();
		break;
	case ENEMY2_STATE_ATTACK:
		UpdateAttack();
		break;
	default:
		break;
	}



	//メッシュフィールドとの衝突判定
	float groundHeight = 0.0f;
	auto meshField = scene->GetGameObject<MeshField>();
	//groundHeight = meshField->GetHeight(m_Position);



	//重力
	m_Velocity.y -= 0.15f;

	//接地
	if (m_Position.y < groundHeight && m_Velocity.y < 0.0f)
	{
		
		m_Position.y = groundHeight;
		m_Velocity.y = 0.0f;
	}
	else
	{
		
	}

	//GUIにパラメータ表示
	/*ImGui::SetNextWindowSize(ImVec2(300, 150));
	ImGui::Begin("Enemy");
	ImGui::InputFloat3("Position", m_Position);
	ImGui::InputFloat3("Rotation", m_Rotation);
	ImGui::InputFloat3("Scale", m_Scale);
	ImGui::End();*/

	//ディゾルブ処理テスト
	m_Threshold += 0.005;
	if (m_Threshold > 1.1f)
	{
		m_Threshold = 0.0f;
	}
}

void Enemy2::Draw()
{
	GameObject::Draw();

	//視錘台カリング
	{
		Scene* scene = Manager::GetScene();
		Camera* camera  = scene->GetGameObject<Camera>();

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

	PARAMETER param;
	ZeroMemory(&param, sizeof(param));
	param.dissolveThreshold = m_Threshold;
	param.disolveRange = 0.1f;
	Renderer::SetParameter(param);

	m_Model->Update(m_AnimationName.c_str(), m_Time, m_NextAnimationName.c_str(), m_Time, m_BlendTime);
	m_Time+=0.5;

	if (m_BlendTime < 1.0f)
	{
		m_BlendTime += 0.1f;
	}

	

	Renderer::SetWorldMatrix(&world);
	m_Model->Draw();
}

void Enemy2::UpdateGround()
{
	if (!m_move && !m_attack && !m_die && m_guard)
	{
		if (m_NextAnimationName != "Idle")
		{
			m_AnimationName = m_NextAnimationName;
			m_NextAnimationName = "Idle";
			m_BlendTime = 0.0f;
		}
	}
}

void Enemy2::UpdateAttack()
{

}
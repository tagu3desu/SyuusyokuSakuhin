#include"main.h"
#include"renderer.h"
#include"enemy.h"
#include"manager.h"
#include"scene.h"
#include"camera.h"
#include"animationModel.h"
#include"meshField.h"
#include"player.h"
#include<cmath>
#include"spherecomponent.h"
#include"input.h"
#include"boxcomponent.h"
#include"bladeefect1.h"
#include"bladeefect2.h"
#include"audio.h"
#include"howleffect.h"
#include<cstdlib>
#include"bullet.h"
#include"field.h"
#include"campField.h"
#include"title.h"
#include"collider.h"
#include"wepon_sword.h"
#include"rockeffect.h"
#include"areachangecollider.h"
AnimationModel* Enemy::m_Model{};

void Enemy::Init()
{
	GameObject::Init();

	m_AnimationName = "Idle";
	m_NextAnimationName = "Idle";

	m_Scale = D3DXVECTOR3(0.05f, 0.05f, 0.05f);
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\pixelLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\dissolvePS.cso");

	m_Time = 0.0f;
	m_BlendTime = 0.0f;
	m_Rotation = D3DXVECTOR3(0.0f, 3.0f, 0.0f);
	m_GroundHeight = 0.0f;
	m_Speed = 0.0f;
	m_HP = 160;

	m_Threshold = 0;
	m_DissolveEnable = true;

	m_DepthEnable = true;

	

	m_Howl=false;



	m_Scene = Manager::GetScene();

	m_HowlSE = AddComponent<Audio>();
	m_HowlSE->Load("asset\\audio\\SE\\怪獣・鳴声01.wav");

	m_RockAttackSE = AddComponent<Audio>();
	m_RockAttackSE->Load("asset\\audio\\SE\\打撃4.wav");

	if (!Title::GetCheckTitle())
	{
		m_EnemyCollider = m_Scene->AddGameObject<Collider>();
		m_EnemyCollider->SetScale(D3DXVECTOR3(100.0f, 160.0f, 100.0f));
		m_EnemyCollider->SetPosition(D3DXVECTOR3(0.0f,80.0f,0.0f));
		m_EnemyCollider->SetRotation(D3DXVECTOR3(0.1f, 0.4f, 0.0f));
		m_EnemyCollider->SetTag(ENEMY_TAG);
	}

}

void Enemy::Load()
{
	m_Model = new AnimationModel();
	//読み込むモデルをローポリとハイポリで2つ読みこむ
	m_Model->Load("asset\\model\\Mutant.fbx");
	m_Model->LoadAnimation("asset\\model\\Mutant Breathing Idle.fbx", "Idle");
	m_Model->LoadAnimation("asset\\model\\Mutant Walking.fbx", "Walk");
	m_Model->LoadAnimation("asset\\model\\SlapAttack.fbx", "Attack");
	m_Model->LoadAnimation("asset\\model\\Jump Attack.fbx", "JumpAttack");
	m_Model->LoadAnimation("asset\\model\\Standing 2H Magiccharge shot.fbx", "RockAttack");
	m_Model->LoadAnimation("asset\\model\\Mutant Roaring.fbx", "Howl");
	//m_Model->LoadAnimation("asset\\model\\Mutant Dying.fbx", "Dead");
	m_Model->LoadAnimation("asset\\model\\Standing React Death Forward.fbx", "Dead");
}

void Enemy::Uninit()
{
	GameObject::Uninit();
	
	m_EnemyCollider->SetDestroy();
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void Enemy::Unload()
{


	m_Model->Unload();
	delete m_Model;
}

void Enemy::Update()
{
	
	GameObject::Update();

	
	auto player = m_Scene->GetGameObject<Player>();
	auto sword = m_Scene->GetGameObject<Sword>();
	AreaChange* areachange = m_Scene->GetGameObject<AreaChange>();

	

	
	//敵本体のコライダー
	m_EnemyCollider->SetMatrix(m_Matrix);
	SetColliderInfo(m_EnemyCollider->GetMatrix() ,false);



	if (m_IsAttack)
	{
		m_Attackdelay++;
	}
	if (m_Attackdelay > 300)
	{
		m_Attackdelay = 0;
		m_IsAttack = false;
	}

	//追跡用
	
	


	switch (m_EnemyState)
	{
	case ENEMY_STATE_IDLE:
		UpdateIdle();
		break;
	case ENEMY_STATE_MOVE:
		UpdateMove();
		break;
	case ENEMY_STATE_ATTACK:
		UpdateAttack();
		break;
	case ENEMY_STATE_HOWL:
		UpdateHowl();
		break;
	case ENAMY_STATE_DEAD:
		UpdateDead();
		break;
	default:
		break;
	}




	if (m_EnemyAI)
	{
		if (m_Length < 15 && !m_IsAttack && m_HowlFinish)
		{
			m_EnemyState = ENEMY_STATE_ATTACK;
		}
		else if (m_HowlFinish && m_Length < 25 && 16 < m_Length && !m_Dead && !m_IsAttack)
		{
			m_EnemyState = ENEMY_STATE_MOVE;
		}
		if (IsInFieldOfView(m_Position, m_Direction, 70, 25.0f))
		{
			if (!m_Howl)
			{
				m_EnemyState = ENEMY_STATE_HOWL;
			}
			m_Find = true;
		}
		else
		{
			m_Find = false;
		}

		m_Direction = player->GetPosition() - m_Position;
		m_Length = D3DXVec3Length(&m_Direction);
		D3DXVec3Normalize(&m_Direction, &m_Direction);
		if (!m_Dead && !m_Attacking && !m_Find)
		{
			m_Rotation.y = atan2f(m_Direction.x, m_Direction.z);
		}
	}
	


	m_Position += m_Direction * m_Speed;
	m_Position += m_Velocity;



	
	

	//当たり判定の処理
	{
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

		if (sword->GetSwordHit())
		{
			m_InviciblilityStartFlag = true;
		}

		if (m_InviciblilityStartFlag)
		{
			m_InvincibilityTime++;
			if (m_InvincibilityTime <= 60)
			{
				m_InvincibilityFlag = true;
			}
			else
			{
				m_InvincibilityFlag = false;
				m_InviciblilityStartFlag = false;
				m_InvincibilityTime = 0;
			}
		}
	}
	
	//死亡系の処理
	{
		if (m_HP <= 0)
		{
			m_Dead = true;
			m_EnemyState = ENAMY_STATE_DEAD;
		}
	}

	//GUIにパラメータ表示
	/*ImGui::SetNextWindowSize(ImVec2(300, 250));
	ImGui::Begin("Enemy");
	ImGui::InputInt("AnimationCount", &m_Attackdelay);
	ImGui::InputInt("HP", &m_HP);
	ImGui::Checkbox("EnemyAI", &m_EnemyAI);
	ImGui::Checkbox("Attaking", &m_Attacking);
	ImGui::Checkbox("Attack", &m_IsAttack);
	ImGui::End();*/
}

void Enemy::Draw()
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



	//Initで用意したモデルの読み込み切り替え

	
	m_Model->Draw();

}

void Enemy::UpdateIdle()
{
	

	if (m_NextAnimationName != "Idle")
	{
		m_Speed = 0.0f;
		m_AnimationName = m_NextAnimationName;
		m_NextAnimationName = "Idle";
		m_BlendTime = 0.0f;
	}


}

void Enemy::UpdateHowl()
{
	
	if (m_NextAnimationName != "Howl")
	{
		m_AnimationName = m_NextAnimationName;
		m_NextAnimationName = "Howl";
		m_BlendTime = 0.0f;
		m_Time = 0.0f;
		m_Speed = 0.0f;
		m_Howl = true;
	}

	
			
	if (m_Howl == true)
	{
		m_AnimationDelay++;
		if (m_AnimationDelay >= 90 && m_AnimationDelay<=300)
		{
			if (m_AnimationDelay % 10 == 0)
			{
				//HowlEffect* howleffect = m_Scene->AddGameObject<HowlEffect>();
				//howleffect->SetScale(D3DXVECTOR3(50.0f, 50.0f, 0.0f));
			}		
			if (!m_HowlSEFlag)
			{
				m_HowlSE->Volume(Scene::m_SEVolume * 0.5f);
				m_HowlSE->PlaySE();
				m_HowlSEFlag = true;
			}
		}

	

		if (m_AnimationDelay >= 330)
		{
			m_HowlFinish = true;
			m_AnimationDelay = 0;
			m_EnemyState = ENEMY_STATE_IDLE;
		}
	}
}

void Enemy::UpdateAttack() {

	

	if (!m_Attacking)
	{
		if (m_Length < 10)
		{
			m_EnemyAttackPatarn = ENEMY_ATTACK_SLAP;
		}
		/*else if (m_Length >= 11 && m_Length < 25 && !m_RockAttackFlag)
		{
			m_EnemyAttackPatarn = ENEMY_ATTCK_ROCK;
			m_RockAttackFlag = true;
		}*/
	}
	
	if (m_RockAttackFlag)
	{
		m_RockattackLimit++;
		if (m_RockattackLimit > 1200)
		{
			m_RockattackLimit = 0;
			m_RockAttackFlag = false;
		}
	}

	switch (m_EnemyAttackPatarn)
	{
	case ENEMY_ATTACK_SLAP:
		UpdatePunchiAttack();
		break;
	case ENEMY_ATTCK_ROCK:
		UpdateRockAttack();
		break;
	default:
		break;
	}


	
}

void Enemy::UpdateMove() {
	if (m_NextAnimationName != "Walk")
	{
		m_Speed = 0.05f;
		m_AnimationName = m_NextAnimationName;
		m_NextAnimationName = "Walk";
		m_BlendTime = 0.0f;
	}
	if (!m_Find)
	{
		m_EnemyState = ENEMY_STATE_IDLE;
	}
}

void Enemy::UpdateDead() {
	
	if (!m_DeadFinish)
	{
		if (m_NextAnimationName != "Dead")
		{
			m_AnimationName = m_NextAnimationName;
			m_NextAnimationName = "Dead";
			m_BlendTime = 0.0f;
			m_Time = 0.0f;

		}
	}

	m_DeadAnimationdelay++;

	if (m_DeadAnimationdelay >= 350)
	{
		m_Time = 350;
		m_DeadFinish = true;
		
	}

	if (m_DeadAnimationdelay >= 650)
	{
		//ディゾルブ処理テスト
		m_Threshold += 0.005;

		if (m_Threshold > 1.1f)
		{
			SetDestroy();
			//m_Threshold = 0.0f;
		}
	}
	
}

void Enemy::UpdatePunchiAttack(){
	if (m_NextAnimationName != "Attack")
	{
		m_AnimationName = m_NextAnimationName;
		m_NextAnimationName = "Attack";
		m_BlendTime = 0.0f;
		m_Time = 0.0f;
		m_IsAttack = true;
	}
	
	m_AnimationDelay++;

	if (m_AnimationDelay >= 100 && !m_Attacking)
	{
		RockEffect* rockeffect = m_Scene->AddGameObject<RockEffect>();
		rockeffect->SetPosition(m_Position + (D3DXVECTOR3(0.0f, -1.5f, 0.0f)) + GetForward() * 5.0f);
		rockeffect->SetRotation(m_Rotation);
		m_RockAttackSE->Volume(Scene::m_SEVolume);
		m_RockAttackSE->PlaySE();
		m_Attacking = true;
	}

	if (m_AnimationDelay >= 200)
	{
		m_AnimationDelay = 0;
		m_Attacking = false;
		m_EnemyState = ENEMY_STATE_IDLE;
	}
	

}

void Enemy::UpdateRockAttack() {


	if (m_NextAnimationName != "RockAttack")
	{
		m_AnimationName = m_NextAnimationName;
		m_NextAnimationName = "RockAttack";
		m_BlendTime = 0.0f;
		m_Time = 0.0f;
		m_Speed = 0.0f;
		m_IsAttack = true;
		m_ShotFlag = true;
		m_Attacking = true;
	}
	if (m_ShotFlag && m_ShotCount==0)
	{
		m_ShotCount = 1;
		Bullet* bullet = m_Scene->AddGameObject<Bullet>();
		bullet->SetPosition(m_Position + D3DXVECTOR3(0.0f, -2.0f, 0.0f));
	}
	m_AnimationDelay++;
	if (m_AnimationDelay >= 220)
	{
		m_AnimationDelay = 0;
		m_ShotCount = 0;
		m_IsAttack = false;
		m_Attacking = false;
		m_EnemyState = ENEMY_STATE_IDLE;
	}
}

bool Enemy::IsInFieldOfView(const D3DXVECTOR3& origin, D3DXVECTOR3& direction, float fieldOfViewRadians, float viewDistancee)
{
	
	Player* player = m_Scene->GetGameObject<Player>();

	// 視野範囲内かどうかの判定
	D3DXVECTOR3 normalizedDirection;
	D3DXVec3Normalize(&normalizedDirection, &direction);
	D3DXVECTOR3 houkou = GetForward();
	float dotProduct = D3DXVec3Dot(&houkou, &normalizedDirection);
	float angle = acos(dotProduct);
	fieldOfViewRadians = D3DXToRadian(fieldOfViewRadians);
	bool isInFieldOfView = angle <= fieldOfViewRadians / 2.0f;

	// 視野距離内かどうかの判定
	D3DXVECTOR3 dice = origin - player->GetPosition();
	float distance = D3DXVec3Length(&dice);
	bool isInViewDistance = distance <= viewDistancee;

	return isInFieldOfView && isInViewDistance;
}


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
	groundHeight = 0.0f;
	m_speed = 0.0f;
	m_HP = 1000;

	m_Threshold = 0;
	m_dissolveEnable = true;

	m_DepthEnable = true;

	hitcout = 0;

	m_howl=false;

	m_lastattackcout = 0;

	scene = Manager::GetScene();

	m_HowlSE = AddComponent<Audio>();
	m_HowlSE->Load("asset\\audio\\bull_monster.wav");

	if (!Title::GetCheckTitle())
	{
		m_EnemyCollider = scene->AddGameObject<Collider>();
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
	m_Model->LoadAnimation("asset\\model\\Mutant Dying.fbx", "Dead");
}

void Enemy::Uninit()
{
	GameObject::Uninit();
	
	
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

	
	auto player = scene->GetGameObject<Player>();
	auto sword = scene->GetGameObject<Sword>();
	AreaChange* areachange = scene->GetGameObject<AreaChange>();

	direction = player->GetPosition() - m_Position;
	//プレイヤーとの距離
	length = D3DXVec3Length(&direction);

	
	//敵本体のコライダー
	m_EnemyCollider->SetMatrix(m_Matrix);
	SetColliderInfo(m_EnemyCollider->GetMatrix() ,false);



	if (isAttack)
	{
		m_attackdelay++;
	}
	if (m_attackdelay > 300)
	{
		m_attackdelay = 0;
		isAttack = false;
	}

	//追跡用
	D3DXVec3Normalize(&direction, &direction);


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
		if (length < 15 && !isAttack && m_howlfinish)
		{
			m_EnemyState = ENEMY_STATE_ATTACK;
		}
		else if (m_howlfinish && length < 20 && 16 < length && !m_dead && !isAttack)
		{
			m_EnemyState = ENEMY_STATE_MOVE;
		}
		if (IsInFieldOfView(m_Position, direction, 70, 25.0f))
		{
			if (!m_howl)
			{
				m_EnemyState = ENEMY_STATE_HOWL;
			}
			m_find = true;
		}
		else
		{
			m_find = false;
		}

		if (!m_dead)
		{
			m_Rotation.y = atan2f(direction.x, direction.z);
		}
	}
	


	m_Position += direction * m_speed;
	m_Position += m_Velocity;



	
	

	//当たり判定の処理
	{
		//メッシュフィールドとの衝突判定
		float groundHeight = 0.0f;
		//auto meshField = scene->GetGameObject<MeshField>();

		//MeshField* meshField;
		//BaseCamp* baseCamp;

		MeshField* meshField = scene->GetGameObject<MeshField>();
		BaseCamp* campField = scene->GetGameObject<BaseCamp>();

		if (meshField != nullptr) {
			if (meshField->GetMapActive())
			{
				meshField = scene->GetGameObject<MeshField>();
				groundHeight = meshField->GetHeight(m_Position);
			}
		}
		
		if (campField != nullptr)
		{
			if (campField->GetMapActive())
			{
				campField = scene->GetGameObject<BaseCamp>();
				groundHeight = meshField->GetHeight(m_Position);
			}
		}
		//position+ forward * 数値
		if (Input::GetKeyTrigger('B'))
		{
			
		}


		//重力
		m_Velocity.y -= 0.015f;

		//接地
		if (m_Position.y < groundHeight && m_Velocity.y < 0.0f)
		{

			m_Position.y = groundHeight;
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
			m_dead = true;
			m_EnemyState = ENAMY_STATE_DEAD;
		}
	}
	

	

	//GUIにパラメータ表示
	ImGui::SetNextWindowSize(ImVec2(300, 250));
	ImGui::Begin("Enemy");
	//ImGui::InputFloat3("ArmPos", m_EnemyLightArmCollider->GetColliderPosition());
	//ImGui::InputFloat("Thredhold", &m_Threshold);
	//ImGui::InputFloat3("Position", m_Position);
	//ImGui::InputFloat3("BPosition", m_BonePos);
	//ImGui::InputFloat("Length", &length);
	ImGui::InputInt("AnimationCount", &m_animationdelay);
	ImGui::InputInt("HP", &m_HP);
	//ImGui::Checkbox("hit", &m_lastattackhit);
	//ImGui::InputInt("HitCount", &hitcout);
	//ImGui::InputFloat3("Scale", m_Scale);
	//ImGui::Checkbox("Find", &m_find);
	//ImGui::Checkbox("Attack", &m_attack);
	//ImGui::Checkbox("Collision", &m_EnemyAttackHit);
	ImGui::Checkbox("EnemyAI", &m_EnemyAI);
	//ImGui::InputInt("Count", &m_InvincibilityTime);
	ImGui::End();
}

void Enemy::Draw()
{
	GameObject::Draw();
	MeshField* meshfield = scene->GetGameObject<MeshField>();

	//視錘台カリング
	{
		
		Camera* camera = scene->GetGameObject<Camera>();

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
		m_speed = 0.0f;
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
		m_speed = 0.0f;
		m_howl = true;
	}

			
	if (m_howl == true)
	{
		m_animationdelay++;
		if (m_animationdelay >= 90 && m_animationdelay<=300)
		{
			if (m_animationdelay % 10 == 0)
			{
				HowlEffect* howleffect = scene->AddGameObject<HowlEffect>();
				howleffect->SetScale(D3DXVECTOR3(50.0f, 50.0f, 0.0f));
			}		
		}

		if (m_animationdelay >= 330)
		{
			m_howlfinish = true;
			m_animationdelay = 0;
			m_EnemyState = ENEMY_STATE_IDLE;
		}
	}
}

void Enemy::UpdateAttack() {

	

	if (!m_Attacking)
	{
		if (length < 10)
		{
			m_EnemyAttackPatarn = ENEMY_ATTACK_SLAP;
		}
		else if (length >= 11 && length < 25 && !m_RockAttackFlag)
		{
			m_EnemyAttackPatarn = ENEMY_ATTCK_ROCK;
			m_RockAttackFlag = true;
		}
	}
	
	if (m_RockAttackFlag)
	{
		m_Rockattacklimit++;
		if (m_Rockattacklimit > 1200)
		{
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
		m_speed = 0.05f;
		m_AnimationName = m_NextAnimationName;
		m_NextAnimationName = "Walk";
		m_BlendTime = 0.0f;
	}
	if (!m_find)
	{
		m_EnemyState = ENEMY_STATE_IDLE;
	}
}

void Enemy::UpdateDead() {
	
	if (!m_deadfinish)
	{
		if (m_NextAnimationName != "Dead")
		{
			m_AnimationName = m_NextAnimationName;
			m_NextAnimationName = "Dead";
			m_BlendTime = 0.0f;
			m_Time = 0.0f;

		}
	}

	m_deadanimationdelay++;

	if (m_deadanimationdelay >= 250)
	{
		m_Time = 250;
		m_deadfinish = true;
		
		// 
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
		m_speed = 0.0f;
		isAttack = true;
	}
	m_animationdelay++;

	if (m_animationdelay >= 100 && !m_Attacking)
	{
		RockEffect* rockeffect = scene->AddGameObject<RockEffect>();
		rockeffect->SetPosition(m_Position + (D3DXVECTOR3(0.0f, -1.5f, 0.0f)) + GetForward() * 5.0f);
		rockeffect->SetRotation(m_Rotation);
		m_Attacking = true;
	}

	if (m_animationdelay >= 200)
	{
		m_animationdelay = 0;
		m_attack = false;
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
		m_speed = 0.0f;
		isAttack = true;
		m_shotflag = true;
		m_Attacking = true;
	}
	if (m_shotflag && m_shotcount==0)
	{
		m_shotcount = 1;
		Bullet* bullet = scene->AddGameObject<Bullet>();
		bullet->SetPosition(m_Position + D3DXVECTOR3(0.0f, -2.0f, 0.0f));
	}
	m_animationdelay++;
	if (m_animationdelay >= 220)
	{
		m_animationdelay = 0;
		m_shotcount = 0;
		m_attack = false;
		m_Attacking = false;
		m_EnemyState = ENEMY_STATE_IDLE;
	}
}

bool Enemy::IsInFieldOfView(const D3DXVECTOR3& origin, D3DXVECTOR3& direction, float fieldOfViewRadians, float viewDistancee)
{
	
	Player* player = scene->GetGameObject<Player>();

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


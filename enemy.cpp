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
#include"input.h"
#include"bladeefect1.h"
#include"bladeefect2.h"
#include"audio.h"
#include"howleffect.h"
#include<cstdlib>
#include"bullet.h"
#include"field.h"
#include"title.h"
#include"boxcollider.h"
#include"sword.h"
#include"rockeffect.h"
#include"areachangecollider.h"
#include"inputx.h"
#include"debug.h"
AnimationModel* Enemy::m_Model{};

void Enemy::Init()
{
	GameObject::Init();

	m_AnimationName = "Idle";
	m_NextAnimationName = "Idle";

	m_Scale = D3DXVECTOR3(0.05f, 0.05f, 0.05f);

	Renderer::CreateSkiningVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\skiningVertexLightingVS.cso");


	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\VertexLightingPS.cso");

	

	//影の有効化
	m_DepthEnable = true;
	

	m_Scene = Manager::GetScene();

	m_HowlSE = AddComponent<Audio>();
	m_HowlSE->Load("asset\\audio\\SE\\怪獣・鳴声01.wav");

	m_RockAttackSE = AddComponent<Audio>();
	m_RockAttackSE->Load("asset\\audio\\SE\\打撃4.wav");

	m_DeadSE = AddComponent<Audio>();  //足音と死んだときの音に使用
	m_DeadSE->Load("asset\\audio\\SE\\怪獣の足音.wav");

	m_ReactionSE = AddComponent<Audio>();
	m_ReactionSE->Load("asset\\audio\\SE\\怪物・怯み.wav");

	//パラメータの設定
	m_HP = 120;
	m_Hesitation = 100;

	if (!Title::GetCheckTitle())
	{
		m_EnemyCollider = m_Scene->AddGameObject<BoxCollider>();
		m_EnemyCollider->SetScale(D3DXVECTOR3(100.0f, 160.0f, 100.0f));
		m_EnemyCollider->SetPosition(D3DXVECTOR3(0.0f,0.0f,0.0f));
		m_EnemyCollider->SetRotation(D3DXVECTOR3(0.1f, 0.4f, 0.0f));
		
		m_EnemyLeftArm = m_Scene->AddGameObject<EnemyLeftArm>();

		m_EnemyAnimationCorrection = m_Scene->AddGameObject<EnemyAnimationCorrection>();
	}

}

void Enemy::Load()
{
	m_Model = new AnimationModel();
	//読み込むモデルをローポリとハイポリで2つ読みこむ
	m_Model->Load("asset\\model\\enemy\\Mutant.fbx");
	m_Model->LoadAnimation("asset\\model\\enemy\\MutantIdle.fbx", "Idle");
	m_Model->LoadAnimation("asset\\model\\enemy\\MutantWalk.fbx", "Walk");
	m_Model->LoadAnimation("asset\\model\\enemy\\MutantRun.fbx", "Run");
	m_Model->LoadAnimation("asset\\model\\enemy\\MutantSwiping.fbx", "PunchiAttack");
	m_Model->LoadAnimation("asset\\model\\enemy\\MutantSlapAttack.fbx", "SlapAttack");
	m_Model->LoadAnimation("asset\\model\\enemy\\MutantJumpAttack.fbx", "JumpAttack");
	m_Model->LoadAnimation("asset\\model\\enemy\\MutantHowl.fbx", "Howl");
	m_Model->LoadAnimation("asset\\model\\enemy\\MutantReaction.fbx", "DamageReaction");
	m_Model->LoadAnimation("asset\\model\\enemy\\MutantDead.fbx", "Dead");
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
	DebugSystem* debugsystem = m_Scene->GetGameObject<DebugSystem>();
	
	D3DXQUATERNION quat;
	D3DXVECTOR3 axis = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	float angle = atan2f(GetForward().x, GetForward().z);
	D3DXQuaternionRotationAxis(&quat, &axis, angle);
	D3DXQuaternionSlerp(&m_Quaternion, &m_Quaternion, &quat, 0.1f);
	
	if (debugsystem->GetDebugWindowEnable())
	{
		//GUIにパラメータ表示
		ImGui::SetNextWindowSize(ImVec2(300, 250));
		ImGui::Begin("EnemyStates");
		ImGui::InputFloat3("Position", m_Position);
		ImGui::InputInt("Frame", &m_AnimationDelay);
		ImGui::InputInt("HP", &m_HP);
		ImGui::InputInt("Hesitation", &m_Hesitation);
		ImGui::End();
	}

	//敵本体のコライダー
	AnimationModel* animationmodel;
	animationmodel = GetAnimationModel();
	m_EnemyCollider->SetMatrix(m_Matrix);
	BONE* bodybone;
	bodybone = animationmodel->GetBone("mixamorig:Hips");
	m_EnemyCollider->SetBoneEnable(true);
	m_EnemyCollider->SetBoneMatrix(animationmodel->ConvertMatrix(bodybone->WorldMatrix));
	SetColliderInfo(m_EnemyCollider->GetMatrix());

	

	//ジャンプ攻撃
	if (m_JumpAttackFlag){
		if ((m_EnemyCollider->CollisionChecker(this,player,0.7f) || m_EnemyLeftArm->GetHit()) && !m_JumpInvincibilityFlag)
		{
			m_JumpAttackHit = true;
			m_JumpInvincibilityFlag = true;
		}
		else
		{
			m_JumpAttackHit = false;
		}
	}
	else
	{
		m_JumpInvincibilityFlag = false;
		m_JumpAttackHit = false;
	}
	
	


	//パンチ攻撃
	if (m_PunchAttackFlag){
		if (m_EnemyLeftArm->GetHit() && !m_PunchInvincibilityFlag)
		{
			m_PunchAttackHit = true;
			m_PunchInvincibilityFlag = true;
		}
		else
		{
			m_PunchAttackHit = false;
		}
	}
	else
	{
		m_PunchInvincibilityFlag = false;
		m_PunchAttackHit = false;
	}


	if (m_IsAttack)
	{
		m_Attackdelay++;
	}
	if (m_Attackdelay > 300)
	{
		m_Attackdelay = 0;
		m_IsAttack = false;
	}

	

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
	case ENEMY_STATE_LOITERING:
		UpdateLoitering();
		break;
	case ENEMY_STATE_REACTION:
		UpdateDamageReaction();
	default:
		break;
	}




	if (m_EnemyAI)
	{
		m_Direction = player->GetPosition() - m_Position;
		m_Length = D3DXVec3Length(&m_Direction);
		D3DXVec3Normalize(&m_Direction, &m_Direction);

		if (m_Hesitation <= 0)
		{
			m_Run = false;
			m_Walk = false;
			m_EnemyState = ENEMY_STATE_REACTION;
		}
		else if (m_Length < 16 && !m_IsAttack && m_HowlFinish && !player->GetPlayerDead())
		{
			m_Run = false;
			m_Walk = false;
			m_EnemyState = ENEMY_STATE_ATTACK;
		}
		else if (!m_HowlFinish && !m_Find && m_EnemyState != ENEMY_STATE_HOWL)
		{
			m_EnemyState = ENEMY_STATE_LOITERING;
		}
		else if (m_HowlFinish && m_Length < 70 && 16 <= m_Length && !m_Dead && !m_IsAttack)
		{
			m_Run = true;
			m_EnemyState = ENEMY_STATE_MOVE;
		}
		if (IsInFieldOfView(m_Position, m_Direction, 70, 15.0f,player) || m_Length < 15)
		{
			if (!m_Howl)
			{
				m_Walk = false;
				m_EnemyState = ENEMY_STATE_HOWL;
			}
			m_Find = true;
		}
		else
		{
			m_Find = false;
		}

		
		if (!m_Dead && !m_Animating && ( !m_Attacking && m_HowlFinish || m_Find) )
		{
			m_Rotation.y = atan2f(m_Direction.x, m_Direction.z);
		}
	}
	
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
		m_Position += m_Velocity;
		
	}
	
	

	//死亡系の処理
	{
		if (m_HP <= 0)
		{
			m_Dead = true;
			m_Speed = 0.0f;
			m_EnemyState = ENAMY_STATE_DEAD;
		}
	}

	

	D3DXVECTOR3 direction = m_DirectionX + m_DirectionZ;
	D3DXVec3Normalize(&direction, &direction);
	m_Position += direction * m_Speed;
	
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
	D3DXMatrixRotationQuaternion(&rot, &m_Quaternion);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	m_Matrix = scale * rot * trans;

	Renderer::SetWorldMatrix(&m_Matrix);

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

	m_DirectionX = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_DirectionZ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			
	if (m_Howl == true)
	{
		m_AnimationDelay++;
		if (m_AnimationDelay >= 90 && m_AnimationDelay<=290)
		{
			if (m_AnimationDelay % 30 == 0)
			{
				HowlEffect* howleffect = m_Scene->AddGameObject<HowlEffect>();
				howleffect->SetScale(D3DXVECTOR3(50.0f, 50.0f, 0.0f));
				howleffect->SetPosition(D3DXVECTOR3(m_Position.x, m_Position.y + 4.0f, m_Position.z));
			}		
			if (!m_HowlSEFlag)
			{
				m_HowlSE->Volume(Scene::m_SEVolume * 0.1f);
				m_HowlSE->PlaySE();
				m_HowlSEFlag = true;
			}
			InputX::SetVibration(0, 50);
		}
		else
		{
			InputX::StopVibration(0);
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


	if (!m_Animating)
	{
		if (m_Length < 10)
		{
			m_AttackRandomNum = rand() % 100;

			//60%の確率でパンチ
			if(m_AttackRandomNum < 60)
			{
				m_EnemyAttackPatarn = ENEMY_ATTACK_PUNCH;
			}
			else   //40%でたたきつけ
			{
				m_EnemyAttackPatarn = ENEMY_ATTACK_SLAP;
			}
		}
		else if (m_Length >= 10 && m_Length < 30)
		{
			m_EnemyAttackPatarn = ENEMY_ATTCK_JUMP;
			
		}
	}
	

	switch (m_EnemyAttackPatarn)
	{
	case ENEMY_ATTACK_SLAP:
		UpdateSlapAttack();
		break;
	case ENEMY_ATTACK_PUNCH:
		UpdatePunchAttack();
		break;
	case ENEMY_ATTCK_JUMP:
		UpdateJumpAttack();
		break;
	default:
		break;
	}


	
}

void Enemy::UpdateMove() {
	if (m_NextAnimationName != "Run")
	{
		m_Speed = 0.2f;
		m_AnimationName = m_NextAnimationName;
		m_NextAnimationName = "Run";
		m_BlendTime = 0.0f;
		m_DirectionZ = GetForward();
		m_Run = true;
	}
	if (!m_Find)
	{
		m_Run = false;
		m_EnemyState = ENEMY_STATE_IDLE;
	}

	if (!m_FootSoundFlag)
	{
		m_DeadSE->Volume(Scene::m_SEVolume * 0.03f);
		m_DeadSE->PlaySE();
		m_FootSoundFlag = true;
	}
	if (m_FootSoundFlag)
	{
		m_FootSoundInterval++;
		if (m_FootSoundInterval >= 23)
		{
			m_FootSoundInterval = 0;
			m_FootSoundFlag = false;
		}
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
	if (m_DeadAnimationdelay >= 250 && !m_DeadSEFlag)
	{
		m_DeadSE->Volume(Scene::m_SEVolume * 0.5f);
		m_DeadSE->PlaySE();
		m_DeadSEFlag = true;
	}

	if (m_DeadAnimationdelay >= 350)
	{
		m_Time = 350;
		m_DeadFinish = true;
		
	}	
}

void Enemy::UpdateLoitering()
{
	if (m_NextAnimationName != "Walk")
	{
		m_Speed = 0.05f;
		m_AnimationName = m_NextAnimationName;
		m_NextAnimationName = "Walk";
		m_BlendTime = 0.0f;
		m_Walk = true;
	}

	m_FrameWait++;
	if (m_FrameWait < 180 || 540 <=m_FrameWait && m_FrameWait <720 )
	{
		m_DirectionX = -GetRight();

		D3DXQUATERNION quat;
		D3DXVECTOR3 axis = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		float angle = atan2f(-GetRight().x, -GetRight().z);
		D3DXQuaternionRotationAxis(&quat, &axis, angle);
		D3DXQuaternionSlerp(&m_Quaternion, &m_Quaternion, &quat, 0.1f);	//球面線形補間
	}
	else if (180 <= m_FrameWait && m_FrameWait < 540)
	{
		m_DirectionX = GetRight();

		D3DXQUATERNION quat;
		D3DXVECTOR3 axis = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		float angle = atan2f(GetRight().x, GetRight().z);
		D3DXQuaternionRotationAxis(&quat, &axis, angle);
		D3DXQuaternionSlerp(&m_Quaternion, &m_Quaternion, &quat, 0.1f);	//球面線形補間
	}
	else if (720 <= m_FrameWait)
	{
		m_FrameWait = 0;
	}

	if (!m_FootSoundFlag)
	{
		m_DeadSE->Volume(Scene::m_SEVolume * 0.03f);
		m_DeadSE->PlaySE();
		m_FootSoundFlag = true;
	}
	if (m_FootSoundFlag)
	{
		m_FootSoundInterval++;
		if (m_FootSoundInterval >= 40)
		{
			m_FootSoundInterval = 0;
			m_FootSoundFlag = false;
		}
	}
}

void Enemy::UpdateDamageReaction()
{
	if (!m_ReactionSEFlag)
	{
		m_ReactionSEFlag = true;
		m_ReactionSE->Volume(Scene::m_SEVolume*0.3);
		m_ReactionSE->PlaySE();
	}


	if (m_NextAnimationName != "DamageReaction")
	{
		m_AnimationName = m_NextAnimationName;
		m_NextAnimationName = "DamageReaction";
		m_BlendTime = 0.0f;
		m_Time = 0.0f;
		m_Speed = 0.0f;
		m_Animating = true;
	}
	m_DamageReactionDelay++;
	if (m_DamageReactionDelay >= 125)
	{
		m_Position.x = m_EnemyAnimationCorrection->GetAnimationPosition().x;
		m_Position.z = m_EnemyAnimationCorrection->GetAnimationPosition().z;
		m_ReactionSEFlag = false;
		m_AnimationDelay = 0;
		m_DamageReactionDelay = 0;
		m_Hesitation = 100;
		m_EnemyState = ENEMY_STATE_IDLE;
	}

}

void Enemy::UpdateSlapAttack(){
	if (m_NextAnimationName != "SlapAttack")
	{
		m_AnimationName = m_NextAnimationName;
		m_NextAnimationName = "SlapAttack";
		m_BlendTime = 0.0f;
		m_Time = 0.0f;
		m_Speed = 0.0f;
		m_IsAttack = true;
		m_Animating = true;
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

	if (100 <= m_AnimationDelay && m_AnimationDelay < 110)
	{
		Camera* m_Camera = m_Scene->GetGameObject<Camera>();
		m_Camera->Shake(1.0f);
	}

	if (m_AnimationDelay >= 200)
	{
		m_AnimationDelay = 0;
		m_Attacking = false;
		m_Animating = false;
		m_EnemyState = ENEMY_STATE_IDLE;
	}
	

}

void Enemy::UpdatePunchAttack() {

	if (m_NextAnimationName != "PunchiAttack")
	{
		m_AnimationName = m_NextAnimationName;
		m_NextAnimationName = "PunchiAttack";
		m_BlendTime = 0.0f;
		m_Time = 0.0f;
		m_Speed = 0.0f;
		m_IsAttack = true;
		m_Animating = true;
	}

	m_AnimationDelay++;

	if (80 < m_AnimationDelay &&  m_AnimationDelay < 110)
	{
		m_PunchAttackFlag = true;
	}
	else
	{
		m_PunchAttackFlag = false;
	}

	if (m_AnimationDelay >= 150)
	{
		m_AnimationDelay = 0;
		m_Attacking = false;
		m_Animating = false;
		m_PunchAttackFlag = false;
		m_EnemyState = ENEMY_STATE_IDLE;
	}
	
}

void Enemy::UpdateJumpAttack()
{
	if (m_NextAnimationName != "JumpAttack")
	{
		m_AnimationName = m_NextAnimationName;
		m_NextAnimationName = "JumpAttack";
		m_BlendTime = 0.0f;
		m_Time = 0.0f;
		m_Speed = 0.0f;
		m_IsAttack = true;
		m_Animating = true;
	}

	m_AnimationDelay++;

	if (m_AnimationDelay >= 100 && !m_Attacking)
	{
		m_RockAttackSE->Volume(Scene::m_SEVolume);
		m_RockAttackSE->PlaySE();
		m_Attacking = true;
	}


	if (100 <= m_AnimationDelay && m_AnimationDelay < 110)
	{
		Camera* m_Camera = m_Scene->GetGameObject<Camera>();
		m_Camera->Shake(1.0f);
	}

	if (90 <= m_AnimationDelay && m_AnimationDelay <= 130)
	{
		m_JumpAttackFlag = true;
	}
	else
	{
		m_JumpAttackFlag = false;
	}

	if (m_AnimationDelay >= 230)
	{
		
		m_Position.x = m_EnemyAnimationCorrection->GetAnimationPosition().x;
		m_Position.z = m_EnemyAnimationCorrection->GetAnimationPosition().z;
		m_AnimationDelay = 0;
		m_Attacking = false;
		m_Animating = false;
		m_JumpAttackFlag = false;
		m_EnemyState = ENEMY_STATE_IDLE;
	}
}


//左腕
void EnemyLeftArm::Init()
{


	m_Scene = Manager::GetScene();
	m_LeftArmCollider = m_Scene->AddGameObject<BoxCollider>();
	m_LeftArmCollider->SetScale(D3DXVECTOR3(60.0f, 120.0f, 60.0f));
	m_LeftArmCollider->SetPosition(D3DXVECTOR3(0.0f, 40.0f, 0.0f));
}

void EnemyLeftArm::Uninit()
{
	m_LeftArmCollider->SetDestroy();
}

void EnemyLeftArm::Update()
{
	Enemy* enemy = m_Scene->GetGameObject<Enemy>();
	Player* player = m_Scene->GetGameObject<Player>();

	//アニメーションのずれを補正
	AnimationModel* animationmodel;
	animationmodel = enemy->GetAnimationModel();
	BONE* bone;
	bone = animationmodel->GetBone("mixamorig:LeftHand");
	bone->WorldMatrix;
	m_Parent = animationmodel->ConvertMatrix(bone->WorldMatrix);
	
	m_LeftArmCollider->SetMatrix(m_Matrix);
	SetColliderInfo(m_LeftArmCollider->GetMatrix());

	
	if (m_LeftArmCollider->CollisionChecker(this, player, 0.5f))
	{
		m_LeftArmCollider->SetColliderColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		m_Hit = true;
	}
	else
	{
		m_LeftArmCollider->SetColliderColor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
		m_Hit = false;
	}

}

void EnemyLeftArm::Draw()
{

	Enemy* enemy = m_Scene->GetGameObject<Enemy>();
	if (enemy != nullptr)
	{
		//マトリクス設定
		D3DXMATRIX scale, rot, trans;
		D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
		D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
		D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
		m_Matrix = scale * rot * trans * m_Parent * enemy->GetMatrix();
		Renderer::SetWorldMatrix(&m_Matrix);
	}

}



//アニメーション補正用のクラス
void EnemyAnimationCorrection::Init()
{
	m_Scene = Manager::GetScene();
}

void EnemyAnimationCorrection::Uninit()
{
	
}

void EnemyAnimationCorrection::Update()
{
	Enemy* enemy = m_Scene->GetGameObject<Enemy>();


	//アニメーションのずれを補正
	AnimationModel* animationmodel;
	animationmodel = enemy->GetAnimationModel();
	BONE* bone;
	bone = animationmodel->GetBone("mixamorig:Hips");
	bone->WorldMatrix;
	m_Parent = animationmodel->ConvertMatrix(bone->WorldMatrix);
	m_AnimationPosition = MatrixtoPosition(m_Matrix);


	m_DifferencePosition = m_AnimationPosition - m_Oldposition;
	m_Oldposition = m_AnimationPosition;
}

void EnemyAnimationCorrection::Draw()
{
	
	Enemy* enemy = m_Scene->GetGameObject<Enemy>();
	if (enemy != nullptr)
	{
		//マトリクス設定
		D3DXMATRIX scale, rot, trans;
		D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
		D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
		D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
		m_Matrix = scale * rot * trans * m_Parent * enemy->GetMatrix();
		Renderer::SetWorldMatrix(&m_Matrix);
	}
	
}



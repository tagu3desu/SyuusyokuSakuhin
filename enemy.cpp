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
#include"collisionHit.h"
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
AnimationModel* Enemy::m_Model{};

void Enemy::Init()
{
	GameObject::Init();

	m_AnimationName = "Idle";
	m_NextAnimationName = "Idle";

	m_Scale = D3DXVECTOR3(0.03f, 0.03f, 0.03f);
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\pixelLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\dissolvePS.cso");

	m_Time = 0.0f;
	m_BlendTime = 0.0f;
	m_Rotation = D3DXVECTOR3(0.0f, 3.0f, 0.0f);
	groundHeight = 0.0f;
	m_speed = 0.0f;
	m_HP = 1000 ;

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
	m_Model->LoadAnimation("asset\\model\\Mutant Swiping.fbx", "Attack");
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

	direction = player->GetPosition() - m_Position;
	//sabun = m_Position - player->GetPosition();
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
		if (IsInFieldOfView(m_Position, direction, 70, 15.0f))
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
		



		//重力
		m_Velocity.y -= 0.015f;

		//接地
		if (m_Position.y < groundHeight && m_Velocity.y < 0.0f)
		{

			m_Position.y = groundHeight;
			m_Velocity.y = 0.0f;
		}

		D3DXVECTOR3 ExplosionPosition = m_Position;
		if (sword->GetSwordHit() && player->GetPlayerAttack() && player->GetPlayerAttackNumber() == 3)
		{
			m_lastattackhit = true;
		}
		else if (sword->GetSwordHit() && player->GetPlayerAttack() && player->GetPlayerAttackNumber() != 3)
		{
			//BladeEffect1* bladeeffect1 = scene->AddGameObject<BladeEffect1>(EFFECT_LAYER);
			//bladeeffect1->SetScale(D3DXVECTOR3(6.5f, 6.5f, 6.5f));
			//bladeeffect1->SetPosition(ExplosionPosition += D3DXVECTOR3(0.0f, 1.0f, 0.0f));
			//m_HP -= 10;
			hitcout += 1;
		}

		if (m_lastattackhit)
		{
			m_lastattackcout++;
		}

		if (m_lastattackcout >= 20)
		{
			//BladeEffect2* bladeeffect2 = scene->AddGameObject<BladeEffect2>(EFFECT_LAYER);
			//bladeeffect2->SetScale(D3DXVECTOR3(8.0f, 8.0f, 8.0f));
			//bladeeffect2->SetPosition(ExplosionPosition += D3DXVECTOR3(0.0f, 1.0f, 0.0f));
			//m_HP -= 10;
			hitcout += 1;
			m_lastattackcout = 0;
			m_lastattackhit = false;
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
	/*ImGui::InputFloat("Thredhold", &m_Threshold);
	ImGui::InputFloat3("Position", m_Position);
	ImGui::InputFloat3("BPosition", m_BonePos);
	ImGui::InputFloat("Length", &length);
	ImGui::InputInt("AttackCount", &m_animationdelay);*/
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


	if (length < 5)
	{
		m_EnemyAttackPatarn = ENEMY_ATTACK_PUNCHI;
	}
	else if(length>=6 && length <14)
	{
		m_EnemyAttackPatarn = ENEMY_ATTCK_ROCK;
	}


	switch (m_EnemyAttackPatarn)
	{
	case ENEMY_ATTACK_PUNCHI:
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
	if (m_animationdelay >= 140)
	{
		m_animationdelay = 0;
		m_attack = false;
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
	}
	if (m_shotflag && m_shotcount==0)
	{
		m_shotcount = 1;
		Bullet* bullet = scene->AddGameObject<Bullet>();
		bullet->SetPosition(m_Position + D3DXVECTOR3(0.0f, -2.0f, 0.0f));
		//bullet->SetVelocity(/*-GetForward() * 6.0f + GetUp() *7.0f + */GetRight() * 4.2f);

		Bullet* bullet1 = scene->AddGameObject<Bullet>();
		bullet1->SetPosition(m_Position + D3DXVECTOR3(0.0f, -2.0f, 0.0f) + GetRight() * 4.2f);
		//bullet1->SetVelocity(-GetForward() * 6.0f + GetUp() * 7.0f + -GetRight() * 4.2f);

		Bullet* bullet2 = scene->AddGameObject<Bullet>();
		bullet2->SetPosition(m_Position + D3DXVECTOR3(0.0f, -2.0f, 0.0f) - GetRight() * 4.2f);
		//bullet2->SetVelocity(GetUp() * 5.0f +  -GetForward() * 6.0f);
	}
	m_animationdelay++;
	if (m_animationdelay >= 220)
	{
		m_animationdelay = 0;
		m_shotcount = 0;
		m_attack = false;
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

void Enemy::SetCollision(aiNode* node, aiMatrix4x4 matrix)
{
	
	Player* player = scene->GetGameObject<Player>();

	std::string BornName = node->mName.C_Str();

	//boneの位置特定
	if (BornName == "mixamorig:LeftArm")
	{
		
		if (m_BonePos.x - m_BoneScale.x - 0.5f < player->GetPosition().x &&
			player->GetPosition().x < m_BonePos.x + m_BoneScale.x + 0.5f &&
			m_BonePos.z - m_BoneScale.z - 0.5f < player->GetPosition().z &&
			player->GetPosition().z < m_BonePos.z + m_BoneScale.z + 0.5f && !m_InvincibilityFlag
			&& length < 5.5f)
		{
			m_EnemyAttackHit = true;
		}
		else 
		{
			m_EnemyAttackHit = false;
		}

	}



	//Matrix変換
	m_WorldMatrix._11 = matrix.a1; m_WorldMatrix._12 = matrix.b1; m_WorldMatrix._13 = matrix.c1; m_WorldMatrix._14 = matrix.d1;
	m_WorldMatrix._21 = matrix.a2; m_WorldMatrix._22 = matrix.b2; m_WorldMatrix._23 = matrix.c2; m_WorldMatrix._24 = matrix.d2;
	m_WorldMatrix._31 = matrix.a3; m_WorldMatrix._32 = matrix.b3; m_WorldMatrix._33 = matrix.c3; m_WorldMatrix._34 = matrix.d3;
	m_WorldMatrix._41 = matrix.a4; m_WorldMatrix._42 = matrix.b4; m_WorldMatrix._43 = matrix.c4; m_WorldMatrix._44 = matrix.d4;

	//posの変換
	m_BonePos.x = m_WorldMatrix._41; // 行列の右下の要素がX軸方向の移動成分
	m_BonePos.y = m_WorldMatrix._42; // 行列の右下の要素がY軸方向の移動成分
	m_BonePos.z = m_WorldMatrix._43; // 行列の右下の要素がZ軸方向の移動成分

	//scale変換
	D3DXVECTOR3 x = D3DXVECTOR3(m_WorldMatrix._11, m_WorldMatrix._12, m_WorldMatrix._13);
	D3DXVECTOR3 y = D3DXVECTOR3(m_WorldMatrix._21, m_WorldMatrix._22, m_WorldMatrix._23);
	D3DXVECTOR3 z = D3DXVECTOR3(m_WorldMatrix._31, m_WorldMatrix._32, m_WorldMatrix._33);

	m_BoneScale.x = D3DXVec3Length(&x) + 8.9f; //数値は微調整 //15
	m_BoneScale.y = D3DXVec3Length(&y) + 8.9f;
	m_BoneScale.z = D3DXVec3Length(&z) + 8.9f;

	//m_BoneScale.x = D3DXVec3Length(&x) + 8.9f; //数値は微調整 //15
	//m_BoneScale.y = D3DXVec3Length(&y) + 8.9f;
	//m_BoneScale.z = D3DXVec3Length(&z) + 8.9f;

	//m_BonePos.x += m_Position.x; //微調整
	//m_BonePos.z += m_Position.z;

	//m_BonePos.x += m_Position.x -36.0f; //微調整 //-36
	//m_BonePos.z += m_Position.z -21.0f;			//-21

	m_BonePos.x += m_Position.x-20; //微調整 //-36
	m_BonePos.z += m_Position.z - 24.0f;
}

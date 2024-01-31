#include"main.h"
#include"manager.h"
#include"renderer.h"
#include"input.h"
#include"scene.h"
#include"player.h"
#include"bullet.h"
#include"box.h"
#include"cylinder.h"
#include"audio.h"
#include"shadow.h"
#include"animationModel.h"
#include"meshField.h"
#include"camera.h"
#include"enemy.h"
#include"staminagage.h"
#include"hpgage.h"
#include"potioncount.h"

#include"howleffect.h"
#include"GuardInpacteffect.h"

void Player::Init()
{

	m_Model = new AnimationModel();
	m_Model->Load("asset\\model\\Paladin J Nordstrom.fbx");

	//納刀状態モーション
	m_Model->LoadAnimation("asset\\model\\Walking.fbx", "Walk");
	m_Model->LoadAnimation("asset\\model\\Standard Run.fbx", "Run");
	m_Model->LoadAnimation("asset\\model\\Unarmed Idle 01.fbx", "Idle");
	m_Model->LoadAnimation("asset\\model\\Great Sword Jump.fbx", "Jump");
	m_Model->LoadAnimation("asset\\model\\Sword And Shield Death.fbx", "IsDead");
	m_Model->LoadAnimation("asset\\model\\Sprinting Forward Roll.fbx", "IsRoll");

	//剣モーション
	m_Model->LoadAnimation("asset\\model\\Sword And Shield Walk.fbx", "SwordWalk");
	m_Model->LoadAnimation("asset\\model\\Sword And Shield Run.fbx", "SwordRun");
	m_Model->LoadAnimation("asset\\model\\Sword And Shield Idle.fbx", "SwordIdle");
	m_Model->LoadAnimation("asset\\model\\Sheath Sword 2.fbx", "onSword");
	m_Model->LoadAnimation("asset\\model\\Sheath Sword 1.fbx", "offSword");
	m_Model->LoadAnimation("asset\\model\\Sword And Shield Slash.fbx", "SlashAttack");
	m_Model->LoadAnimation("asset\\model\\Sword And Shield Slash2.fbx", "SlashAttack2");
	m_Model->LoadAnimation("asset\\model\\Sword And Shield Slash3.fbx", "SlashAttack3");
	m_Model->LoadAnimation("asset\\model\\Sword And Shield RotAttack.fbx", "RotationAttack");
	m_Model->LoadAnimation("asset\\model\\ComboAttack1.fbx", "ComboAttack1");
	m_Model->LoadAnimation("asset\\model\\ComboAttack2.fbx", "ComboAttack2");
	m_Model->LoadAnimation("asset\\model\\ComboAttack3.fbx", "ComboAttack3");
	m_Model->LoadAnimation("asset\\model\\GreatSwordBackWalk.fbx", "BackWalk");
	m_Model->LoadAnimation("asset\\model\\Sword And Shield BlockStart.fbx", "StartGuard");
	m_Model->LoadAnimation("asset\\model\\Sword And Shield Block Idle.fbx", "IsGuard");
	m_Model->LoadAnimation("asset\\model\\Sword And Shield BlockEnd.fbx", "EndGuard");
	m_Model->LoadAnimation("asset\\model\\Sword And Shield Impact.fbx", "GuardImpact");
	m_Model->LoadAnimation("asset\\model\\Sword And Shield HitSmallAttack.fbx", "HitSmallImpact");


	m_AnimationName = "Idle";
	m_NextAnimationName = "Idle";

	
	m_Scale = D3DXVECTOR3(0.015f, 0.015f, 0.015f);
	//m_MoveVector = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_speed = 0.1f;

	m_DepthEnable = true;
	m_ReflectEnable = true;

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\DepthShadowMappingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\DepthShadowMappingPS.cso");


	m_OnWeponSE = AddComponent<Audio>();
	m_OnWeponSE->Load("asset\\audio\\剣を抜く.wav");

	m_OffWeponSE = AddComponent<Audio>();
	m_OffWeponSE->Load("asset\\audio\\剣を鞘にしまう.wav");

	m_RunSoundBGM = AddComponent<Audio>();
	m_RunSoundBGM->Load("asset\\audio\\鎧の騎士が走る.wav");

	m_WalkSoundBGM = AddComponent<Audio>();
	m_WalkSoundBGM->Load("asset\\audio\\鎧の騎士が歩く.wav");

	m_AttackSE = AddComponent<Audio>();
	m_AttackSE->Load("asset\\audio\\木刀・振る.wav");

	m_Time = 0.0f;
	m_BlendTime = 0.0f;
	m_AnimationDelay = 0.0f;
	m_ConboNumber = 0;
	m_HP = 0;
	m_hitInpactDelay = 0;

	directionX = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	directionZ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_sworddrawn = false;
	m_comboCount=0;
	m_Stamina = 0;

	GameObject::Init();
}

void Player::Uninit()
{
	GameObject::Uninit();

	m_Model->Unload();
	delete m_Model;

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

	GameObject::Uninit();
}

void Player::Update()
{
	Scene* scene = Manager::GetScene();

	directionX = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	directionZ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_move = false;
	
	GameObject::Update();
	D3DXVECTOR3 oldPosition = m_Position;

	Staminagage* staminagage = scene->GetGameObject<Staminagage>();
	Enemy* enemy = scene->GetGameObject<Enemy>();

	m_Stamina = staminagage->GetStamina();

	Camera* camera = scene->GetGameObject<Camera>();
	cameraFoward = camera->GetForward();
	cameraRight = camera->GetRight();
	cameraFoward.y = 0.0f;
	cameraRight.y = 0.0f;
	D3DXVec3Normalize(&cameraRight, &cameraRight);
	D3DXVec3Normalize(&cameraFoward, &cameraFoward);

	//HP関連
	HPgage* hpgage = scene->GetGameObject<HPgage>();
	m_HP = hpgage->GetHp();


	//GUIにパラメータ表示
	ImGui::SetNextWindowSize(ImVec2(300, 250));
	ImGui::Begin("Player");
	ImGui::InputFloat3("Position", m_Position);
	ImGui::InputFloat3("BPosition", m_BonePos);
	ImGui::InputFloat3("Scale", m_Scale);
	ImGui::InputInt("HP", &m_HP);
	ImGui::InputFloat("AnimationDelay", &m_AnimationDelay);
	ImGui::InputInt("count", &hitcount);
	ImGui::Checkbox("Collision", &m_Rockhit);
	ImGui::Checkbox("Move", &m_move);
	ImGui::Checkbox("Run", &m_run); 
	ImGui::Checkbox("Attack", &m_attack);
	ImGui::Checkbox("Idle", &m_idle);
	ImGui::Checkbox("Guard", &m_isGuard); 
	ImGui::Checkbox("EndGuard", &m_EndGuard);
	ImGui::Checkbox("InpactGuard", &m_InpactGuard);
	ImGui::End();

	

	switch (m_PlayerState)
	{
	case PLAYER_STATE_GROUND:
		UpdateGround();
		break;
	case PLAYER_STATE_JUMP:
		UpdateJump();
		break;
	case PLAYER_STATE_ATTACK:
		UpdateAttack();
		break;
	case PLAYER_STATE_ATTACK2:
		UpdateAttack2();
		break;
	case PLAYER_STATE_ATTACK3:
		UpdateAttack3();
		break;
	case PLAYER_STATE_ROLL:
		UpdateRoll();
		break;
	case PLAYER_STATE_DEAD:
		UpdateDead();
		break;
	case PLAYER_STATE_GUARD:
		UpdateGuard();
		break;
	default:
		break;
	}

	PotionCount* potioncount = scene->GetGameObject<PotionCount>();
	m_potioncount = potioncount->GetCount();
	if (m_potioncount > 0)
	{
		if (Input::GetKeyTrigger('F'))
		{
			potioncount->SubstractCount(1);
			hpgage->SetHealPoint(200);
		}
	}
	
	if (m_PlayerHitEnemy)
	{
		m_InviciblilityStartFlag = true;
	}
	if (enemy != nullptr)
	{
		direction = enemy->GetPosition() - m_Position;
		length = D3DXVec3Length(&direction);
	}
	



	if (m_InviciblilityStartFlag)
	{
		m_InvincibilityTime++;
		if (m_InvincibilityTime <= 100)
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

	/*if (Input::GetKeyTrigger('B'))
	{
		Bullet* bullet = scene->AddGameObject<Bullet>();
		bullet->SetPosition(m_Position + D3DXVECTOR3(0.0f,2.0f,0.0f));
		bullet->SetVelocity(GetRight() * 2.2f);
	}*/
	//メッシュフィールドとの衝突判定
	float groundHeight = 0.0f;
	auto meshField = scene->GetGameObject<MeshField>();
	groundHeight = meshField->GetHeight(m_Position);


	//円柱
	std::vector<Cylinder*> Cylinders = scene->GetGameObjects<Cylinder>();
	for (Cylinder* cylinder : Cylinders)//範囲for
	{
		D3DXVECTOR3 postion = cylinder->GetPosition();
		D3DXVECTOR3 scale = cylinder->GetScale();

		D3DXVECTOR3 direction2 = m_Position - postion;
		direction2.y = 0.0f;
		float length = D3DXVec3Length(&direction2);

		if (length < scale.x)
		{
			if (m_Position.y < postion.y + scale.y - 0.5f)
			{
				m_Position.x = oldPosition.x;
				m_Position.z = oldPosition.z;
			}
			else
			{

				groundHeight = postion.y + scale.y + groundHeight; //上判定
			}
			break;
		}

	}

	

	
	////四角柱　
	std::vector<Box*> boxes = scene->GetGameObjects<Box>();
	{
		for (Box* box : boxes)
		{


			D3DXVECTOR3 position = box->GetPosition();
			D3DXVECTOR3 scale = box->GetScale();
			D3DXVECTOR3 right = box->GetRight();	//X分離軸
			D3DXVECTOR3 forward = box->GetForward();	//Z分離軸
			D3DXVECTOR3 up = box->GetUp();	//Y分離軸
			D3DXVECTOR3 direction = m_Position - position; //直方体からプレイヤーまでの方向ベクトル

			float obbx = D3DXVec3Dot(&direction, &right);	//X分離軸方向プレイヤー距離
			float obbz = D3DXVec3Dot(&direction, &forward); //Z分離軸方向プレイヤー距離

			//OBB
			if (fabs(obbx) < scale.x && fabs(obbz) < scale.z)
			{
				if (m_Position.y < position.y + scale.y * 2.0f - 0.5f)
				{
					// 壁の法線ベクトルを計算
					D3DXVECTOR3 wallNormal(1.0f, 0.0f, 0.0f);

					// プレイヤーの移動ベクトルと壁の法線ベクトルの射影を計算
					D3DXVECTOR3 projectedVector = m_MoveVector - D3DXVec3Dot(&m_MoveVector, &wallNormal) * wallNormal;

					// プレイヤーの位置を補正
					m_Position.x = oldPosition.x + projectedVector.x;
					m_Position.z = oldPosition.z + projectedVector.z;
				}
				else
				{
					groundHeight = position.y + groundHeight + scale.y * 2.0f;
				}
				break;

			}

			//AABB
			//// 壁上の特定の点（ここでは壁の中央）からプレイヤーへのベクトルを計算
			//D3DXVECTOR3 wallToPlayer = m_Position - D3DXVECTOR3(position.x, m_Position.y, position.z);

			//// 壁の法線ベクトルを計算
			//D3DXVECTOR3 wallNormal(0.0f, 0.0f, 0.0f);
			//if (D3DXVec3LengthSq(&wallToPlayer) > 0.0001f)
			//{
			//	D3DXVec3Normalize(&wallNormal, &wallToPlayer);
			//}

			//if (position.x - scale.x - 1.0f < m_Position.x &&
			//	m_Position.x < position.x + scale.x + 1.0f &&
			//	position.z - scale.z - 1.0f < m_Position.z &&
			//	m_Position.z < position.z + scale.z + 1.0f)
			//{
			//	if (m_Position.y < position.y + scale.y * 2.0f - 0.5f)
			//	{
			//		// 壁の法線ベクトルを計算
			//		D3DXVECTOR3 wallNormal(1.0f, 0.0f, 0.0f);

			//		// プレイヤーの移動ベクトルと壁の法線ベクトルの射影を計算
			//		D3DXVECTOR3 projectedVector = m_MoveVector - D3DXVec3Dot(&m_MoveVector, &wallNormal) * wallNormal;

			//		// プレイヤーの位置を補正
			//		m_Position.x = oldPosition.x + projectedVector.x;
			//		m_Position.z = oldPosition.z + projectedVector.z;
			//	}
			//	else
			//	{
			//		groundHeight = position.y + groundHeight + scale.y * 2.0f;
			//	}
			//	break;
			//}
		}
	}
	

	////弾　
	std::vector<Bullet*> bullets = scene->GetGameObjects<Bullet>();
	for (Bullet* bullet : bullets)
	{
		D3DXVECTOR3 position = bullet->GetPosition();
		D3DXVECTOR3 scale = bullet->GetScale()*0.5;
		D3DXVECTOR3 right = bullet->GetRight();	//X分離軸
		D3DXVECTOR3 forward = bullet->GetForward();	//Z分離軸
		D3DXVECTOR3 up = bullet->GetUp();	//Y分離軸
		D3DXVECTOR3 direction = m_Position - position; //直方体からプレイヤーまでの方向ベクトル

		float obbx = D3DXVec3Dot(&direction, &right);	//X分離軸方向プレイヤー距離
		float obbz = D3DXVec3Dot(&direction, &forward); //Z分離軸方向プレイヤー距離
		float obby = D3DXVec3Dot(&direction, &up);

		//OBB
		if (fabs(obbx) < scale.x && fabs(obbz) < scale.z && fabs(obby) < scale.y)
		{
			m_Rockhit = true;
			
		}
		else
		{
			m_Rockhit = false;
			break;
		}

	}

	if (enemy != nullptr)
	{
		if (m_HP > 0)
		{
			if (enemy->GetEnemyHitPlayer() && !m_SuccessGuard || m_Rockhit && !m_SuccessGuard) {
				hpgage->SetDamage(-80);
			}
		}
	}
	


	//死亡処理
	if (m_HP <=0)
	{
		
		if (m_NextAnimationName != "IsDead")
		{
			m_Time = 0.0f;
			m_AnimationName = m_NextAnimationName;
			m_NextAnimationName = "IsDead";
			m_BlendTime = 0.0f;
		}
		m_PlayerState= PLAYER_STATE_DEAD;
	}
	
	if (enemy != nullptr)
	{
		if (enemy->GetEnemyHitPlayer() && !m_SuccessGuard && !m_HitInpact || m_Rockhit && !m_SuccessGuard && !m_HitInpact)
		{

			if (m_NextAnimationName != "HitSmallImpact")
			{
				m_Time = 0.0f;
				m_AnimationName = m_NextAnimationName;
				m_NextAnimationName = "HitSmallImpact";
				m_BlendTime = 0.0f;
				m_HitInpact = true;
			}
		}
	}
	

	if (m_HitInpact)
	{
		m_hitInpactDelay++;
		if (m_hitInpactDelay > 30)
		{
			m_hitInpactDelay = 0;
			m_HitInpact = false;
		}
	}

	//重力
	m_Velocity.y -= 0.015f;

	//ジャンプ用移動
	m_Position += m_Velocity;

	//接地
	if (m_Position.y < groundHeight && m_Velocity.y < 0.0f)
	{
		m_IsGround = true;
		m_Position.y = groundHeight;
		m_Velocity.y = 0.0f;
	}
	else
	{
		m_IsGround = false;
	}

	

	GameObject::Update();

}

void Player::Draw()
{
	GameObject::Draw();

	//入力レイアウト
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//シェーダ設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	
	//マトリクス設定
	D3DXMATRIX  world,scale, rot, trans,euler;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationQuaternion(&rot, &m_Quaternion);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	D3DXMatrixRotationYawPitchRoll(&euler, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	m_Matrix = scale * rot * trans;//親のmatrixをかける
	Renderer::SetWorldMatrix(&m_Matrix);

	m_Model->Update(m_AnimationName.c_str(), m_Time, m_NextAnimationName.c_str(), m_Time, m_BlendTime);



	if (m_PlayerState == PLAYER_STATE_ATTACK3)
	{
		m_Time += 0.6;
	}
	else if (m_run || m_walk)
	{
		m_Time += 0.5f;
	}
	else
	{
		m_Time += 0.7;
	}
	

	if (m_BlendTime < 1.0f)
	{
		m_BlendTime += 0.1f;
	}

	m_Model->Draw();

	GameObject::Draw();
}

void Player::UpdateGround()
{
	
	Scene* scene = Manager::GetScene();
	Enemy* enemy = scene->GetGameObject<Enemy>();
	

	//武器の取り出し
	if (Input::GetKeyTrigger('Y')/*(VK_LBUTTON)*/ && !m_sworddrawn)
	{
		
			if (m_NextAnimationName != "onSword")
			{
				m_Time = 0.0f;
				m_AnimationName = m_NextAnimationName;
				m_NextAnimationName = "onSword";
				m_OnWeponSE->Volume(0.01f);
				m_OnWeponSE->Play();
				m_BlendTime = 0.0f;
			}
			m_onSword = true;
			m_sworddrawn = true;
		
	}

	if (Input::GetKeyTrigger('R'))
	{
		if (m_sworddrawn)//納刀
		{
			if (m_NextAnimationName != "offSword")
			{
				m_Time = 0.0f;
				m_AnimationName = m_NextAnimationName;
				m_NextAnimationName = "offSword";
				m_OffWeponSE->Volume(0.01f);
				m_OffWeponSE->Play();
				m_BlendTime = 0.0f;
			}
			m_offSword = true;
			
		}
		
	}
	
	if (m_onSword)
	{
		m_AnimationDelay++;
		if (m_AnimationDelay > 35)
		{
			m_onSword = false;
			m_AnimationDelay = 0;
		}
	
	}
	if (m_offSword)
	{
		m_AnimationDelay++;
		if (m_AnimationDelay > 50)
		{
			m_sworddrawn = false;
			m_AnimationDelay = 0;
			m_offSword = false;
		}

	}

	////サードパーソンビュー(斜め移動)
	if (Input::GetKeyPress('W')) {

		if (Input::GetKeyPress(VK_LSHIFT) && m_Stamina>0)
		{
			
			directionZ = cameraFoward * m_speed;
			if (m_sworddrawn)
			{
				m_speed = 0.1f;
				if (m_NextAnimationName != "SwordRun")
				{
					m_AnimationName = m_NextAnimationName;
					m_NextAnimationName = "SwordRun";
					m_BlendTime = 0.0f;
				}
			}
			else
			{
				m_speed = 0.15f;
				if (m_NextAnimationName != "Run")
				{
					m_AnimationName = m_NextAnimationName;
					m_NextAnimationName = "Run";
					m_BlendTime = 0.0f;
				}
			}	
			D3DXQUATERNION quat;
			D3DXVECTOR3 axis = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			float angle = atan2f(cameraFoward.x, cameraFoward.z);
			D3DXQuaternionRotationAxis(&quat, &axis, angle);
			D3DXQuaternionSlerp(&m_Quaternion, &m_Quaternion, &quat, 0.3f);	//球面線形補間
			m_idle = false;
			m_move = true;
			m_walk = false;
			m_run = true;
		}
		else
		{
			m_speed = 0.05f;
			directionZ = cameraFoward * m_speed;

			if (m_sworddrawn)
			{
				if (m_NextAnimationName != "SwordWalk")
				{
					m_AnimationName = m_NextAnimationName;
					m_NextAnimationName = "SwordWalk";
					m_BlendTime = 0.0f;
				}
			}
			else
			{
				if (m_NextAnimationName != "Walk")
				{
					m_AnimationName = m_NextAnimationName;
					m_NextAnimationName = "Walk";
					m_BlendTime = 0.0f;
				}
			}
			
			D3DXQUATERNION quat;
			D3DXVECTOR3 axis = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			float angle = atan2f(cameraFoward.x, cameraFoward.z);
			D3DXQuaternionRotationAxis(&quat, &axis, angle);
			D3DXQuaternionSlerp(&m_Quaternion, &m_Quaternion, &quat, 0.3f);	//球面線形補間
			m_idle = true;
			m_move = true;
			m_walk = true;
			m_run = false;
		}
		

	}

	if (Input::GetKeyPress('S')) {
		
		if (Input::GetKeyPress(VK_LSHIFT) && m_Stamina > 0)
		{
			m_speed = 0.1f;
			directionZ = -cameraFoward * m_speed;
			if (m_sworddrawn)
			{
				m_speed = 0.1f;
				if (m_NextAnimationName != "SwordRun")
				{
					m_AnimationName = m_NextAnimationName;
					m_NextAnimationName = "SwordRun";
					m_BlendTime = 0.0f;
				}
			}
			else
			{
				m_speed = 0.15f;
				if (m_NextAnimationName != "Run")
				{
					m_AnimationName = m_NextAnimationName;
					m_NextAnimationName = "Run";
					m_BlendTime = 0.0f;
				}
			}
			D3DXQUATERNION quat;
			D3DXVECTOR3 axis = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			float angle = atan2f(-cameraFoward.x, -cameraFoward.z);
			/*D3DXQuaternionRotationAxis(&quat, &axis, D3DX_PI);*/
			D3DXQuaternionRotationAxis(&quat, &axis, angle);
			D3DXQuaternionSlerp(&m_Quaternion, &m_Quaternion, &quat, 0.3f);	//球面線形補間
			m_idle = false;
			m_move = true;
			m_walk = false;
			m_run = true;
		}
		else
		{
			m_speed = 0.05f;
			directionZ = -cameraFoward * m_speed;

			if (m_sworddrawn)
			{
				if (m_NextAnimationName != "SwordWalk")
				{
					m_AnimationName = m_NextAnimationName;
					m_NextAnimationName = "SwordWalk";
					m_BlendTime = 0.0f;
				}
			}
			else
			{
				if (m_NextAnimationName != "Walk")
				{
					m_AnimationName = m_NextAnimationName;
					m_NextAnimationName = "Walk";
					m_BlendTime = 0.0f;
				}
			}
			D3DXQUATERNION quat;
			D3DXVECTOR3 axis = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			float angle = atan2f(-cameraFoward.x, -cameraFoward.z);
			/*D3DXQuaternionRotationAxis(&quat, &axis, D3DX_PI);*/
			D3DXQuaternionRotationAxis(&quat, &axis, angle);
			D3DXQuaternionSlerp(&m_Quaternion, &m_Quaternion, &quat, 0.3f);	//球面線形補間
			m_idle = true;
			m_run = false;
			m_walk = true;
			m_move = true;
		}
		
	}

	if (Input::GetKeyPress('A')) {
	
		if (Input::GetKeyPress(VK_LSHIFT) && m_Stamina > 0)
		{
			m_speed = 0.1f;
			directionX = -cameraRight * m_speed;

			D3DXQUATERNION quat;
			D3DXVECTOR3 axis = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			float angle = atan2f(-cameraRight.x, -cameraRight.z);
			/*D3DXQuaternionRotationAxis(&quat, &axis, -D3DX_PI/2.0f);*/
			D3DXQuaternionRotationAxis(&quat, &axis, angle);
			D3DXQuaternionSlerp(&m_Quaternion, &m_Quaternion, &quat, 0.3f);	//球面線形補間
			

			if (m_sworddrawn)
			{
				m_speed = 0.1f;
				if (m_NextAnimationName != "SwordRun")
				{
					m_AnimationName = m_NextAnimationName;
					m_NextAnimationName = "SwordRun";
					m_BlendTime = 0.0f;
				}
			}
			else
			{
				m_speed = 0.15f;
				if (m_NextAnimationName != "Run")
				{
					m_AnimationName = m_NextAnimationName;
					m_NextAnimationName = "Run";
					m_BlendTime = 0.0f;
				}
			}
			m_idle = false;
			m_move = true;
			m_walk = false;
			m_run = true;
		}
		else
		{
			m_speed = 0.05f;
			directionX = -cameraRight * m_speed;

			D3DXQUATERNION quat;
			D3DXVECTOR3 axis = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			float angle = atan2f(-cameraRight.x, -cameraRight.z);
			/*D3DXQuaternionRotationAxis(&quat, &axis, -D3DX_PI/2.0f);*/
			D3DXQuaternionRotationAxis(&quat, &axis, angle);
			D3DXQuaternionSlerp(&m_Quaternion, &m_Quaternion, &quat, 0.3f);	//球面線形補間
			

			if (m_sworddrawn)
			{
				if (m_NextAnimationName != "SwordWalk")
				{
					m_AnimationName = m_NextAnimationName;
					m_NextAnimationName = "SwordWalk";
					m_BlendTime = 0.0f;
				}
			}
			else
			{
				if (m_NextAnimationName != "Walk")
				{
					m_AnimationName = m_NextAnimationName;
					m_NextAnimationName = "Walk";
					m_BlendTime = 0.0f;
				}
			}
			m_idle = true;
			m_run = false;
			m_walk = true;
			m_move = true;
		}
		
	}

	if (Input::GetKeyPress('D')) {
	
		if (Input::GetKeyPress(VK_SHIFT) && m_Stamina > 0)
		{
			m_speed = 0.1f;
			directionX = cameraRight * m_speed;

			D3DXQUATERNION quat;
			D3DXVECTOR3 axis = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			float angle = atan2f(cameraRight.x, cameraRight.z);
			/*D3DXQuaternionRotationAxis(&quat, &axis, D3DX_PI / 2.0f);*/
			D3DXQuaternionRotationAxis(&quat, &axis, angle);
			D3DXQuaternionSlerp(&m_Quaternion, &m_Quaternion, &quat, 0.3f);	//球面線形補間
			

			if (m_sworddrawn)
			{
				m_speed = 0.1f;
				if (m_NextAnimationName != "SwordRun")
				{
					m_AnimationName = m_NextAnimationName;
					m_NextAnimationName = "SwordRun";
					m_BlendTime = 0.0f;
				}
			}
			else
			{
				m_speed = 0.15f;
				if (m_NextAnimationName != "Run")
				{
					m_AnimationName = m_NextAnimationName;
					m_NextAnimationName = "Run";
					m_BlendTime = 0.0f;
				}
			}

			m_idle = false;
			m_move = true;
			m_walk = false;
			m_run = true;
		}
		else
		{
			m_speed = 0.05f;
			directionX = cameraRight * m_speed;

			D3DXQUATERNION quat;
			D3DXVECTOR3 axis = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			float angle = atan2f(cameraRight.x, cameraRight.z);
			/*D3DXQuaternionRotationAxis(&quat, &axis, D3DX_PI / 2.0f);*/
			D3DXQuaternionRotationAxis(&quat, &axis, angle);
			D3DXQuaternionSlerp(&m_Quaternion, &m_Quaternion, &quat, 0.3f);	//球面線形補間
		

			if (m_sworddrawn)
			{
				if (m_NextAnimationName != "SwordWalk")
				{
					m_AnimationName = m_NextAnimationName;
					m_NextAnimationName = "SwordWalk";
					m_BlendTime = 0.0f;
				}
			}
			else
			{
				if (m_NextAnimationName != "Walk")
				{
					m_AnimationName = m_NextAnimationName;
					m_NextAnimationName = "Walk";
					m_BlendTime = 0.0f;
				}
			}

			m_idle = true;
			m_run = false;
			m_walk = true;
			m_move = true;
		}
		
	}



	if (m_move == false && m_attack == false && !m_onSword && !m_offSword && !m_HitInpact)
	{
		m_run = false;
		m_walk = false;
		m_idle = true;
		//m_WalkSoundBGM->Stop();
		//m_RunSoundBGM->Stop();
		if (m_sworddrawn)
		{
			if (m_NextAnimationName != "SwordIdle")
			{
				m_AnimationName = m_NextAnimationName;
				m_NextAnimationName = "SwordIdle";
				m_comboCount = 0;
				m_BlendTime = 0.0f;
			}
		}
		else
		{
			if (m_NextAnimationName != "Idle")
			{
				m_AnimationName = m_NextAnimationName;
				m_NextAnimationName = "Idle";
				m_comboCount = 0;
				m_BlendTime = 0.0f;
			}
		}
		
	}
	//x,zを加算します
	D3DXVECTOR3 direction = directionX + directionZ;


	//正規化します
	D3DXVec3Normalize(&direction, &direction);

	//PositonにSpeed加算します
	m_Position += direction *m_speed;

	// プレイヤーの移動ベクトルを更新
	//m_MoveVector = m_Velocity * m_speed;

	/*if (Input::GetKeyTrigger(VK_SPACE) && m_Position.y <= 10.5)
	{
		m_Velocity.y = 0.35f;
		if (m_NextAnimationName != "Jump")
		{
			m_AnimationName = m_NextAnimationName;
			m_NextAnimationName = "Jump";
			m_BlendTime = 0.0f;
		}
		m_idle = false;
		m_move = true;
		m_PlayerState = PLAYER_STATE_JUMP;
	}*/

	D3DXVECTOR3 m_ColliderPos = m_Position + GetForward() * 2.0f;

	if (Input::GetKeyPress(VK_RBUTTON) && !m_startGuard && m_sworddrawn)
	{
		if (m_NextAnimationName != "StartGuard")
		{
			m_AnimationName = m_NextAnimationName;
			m_NextAnimationName = "StartGuard";
			m_BlendTime = 0.0f;
		}
		m_idle = false;
		m_startGuard = true;
		m_PlayerState = PLAYER_STATE_GUARD;
	}



	//回転攻撃
	/*if (Input::GetKeyTrigger(VK_LBUTTON) && m_run)
	{
		if (m_NextAnimationName != "RotationAttack")
		{
			m_Time = 0.0f;
			m_BlendTime = 0.0f;
			m_AnimationName = m_NextAnimationName;
			m_NextAnimationName = "RotationAttack";
			m_attack = true;
			m_move = true;
			m_PlayerState = PLAYER_STATE_ATTACK;
		}
	}*/
			
	
	//コンボ攻撃
	if (Input::GetKeyTrigger(VK_LBUTTON) && !m_run && m_sworddrawn && !m_onSword)
	{
		if (m_NextAnimationName != "SlashAttack")
		{
			m_Time = 0.0f;
			m_BlendTime = 0.0f;
			m_AnimationName = m_NextAnimationName;
			m_NextAnimationName = "SlashAttack";
			m_attack = true;
			m_comboCount = 1;
			m_move = true;		
			m_idle = false;
			m_AttackSE->Volume(0.1f);
			m_AttackSE->Play();
			m_PlayerState = PLAYER_STATE_ATTACK;
		}

	}

	
	

	if (Input::GetKeyPress(VK_SPACE))
	{
		if (m_NextAnimationName != "IsRoll")
		{
			m_Time = 0.0f;
			m_AnimationName = m_NextAnimationName;
			m_NextAnimationName = "IsRoll";
			m_move = true;
			m_roll = true;
			m_idle = false;
			m_PlayerState = PLAYER_STATE_ROLL;
		}
	}
}

void Player::UpdateRoll()
{
	if (m_roll==true)
	{
		m_AnimationDelay++;
		if (Input::GetKeyPress('W')) {
			directionZ = cameraFoward * 0.1f;
		}
		else
		{
			directionZ = GetForward() * 0.1f;
		}
		if (Input::GetKeyPress('S')) {
			directionZ = -cameraFoward * 0.1f;
		}
		if (Input::GetKeyPress('A')) {
			directionX = -cameraRight * 0.1f;
		}
		if (Input::GetKeyPress('D')) {
			directionX = cameraRight * 0.1f;
		}
		if (m_AnimationDelay >= 65)
		{
			m_AnimationDelay = 0;
			m_roll = false;
			m_move = false;
			m_idle = true;
			m_PlayerState = PLAYER_STATE_GROUND;
		}	

		//x,zを加算します
		D3DXVECTOR3 direction = directionX + directionZ;


		//正規化します
		D3DXVec3Normalize(&direction, &direction);

		//PositonにSpeed加算します
		m_Position += direction * m_speed;
	}
}

void Player::UpdateAttack()
{
	m_idle = true;
	if (m_attack)
	{
		m_AnimationDelay++;
		
		if (m_HitInpact)
		{
			if (m_AnimationDelay >= 30)
			{
				m_Time = 0;
				m_AnimationDelay = 0;
				m_attack = false;
				m_move = false;

				m_PlayerState = PLAYER_STATE_GROUND;
			}
		}
		else if (m_AnimationDelay >= 185 && !m_HitInpact)
		{
			m_Time = 0;
			m_AnimationDelay = 0;
			m_attack = false;
			m_move = false;
			
			m_PlayerState = PLAYER_STATE_GROUND;
		}

		

		//攻撃モーション1
		if (m_HitInpact)
		{
			if (m_AnimationDelay >= 30)
			{
				m_Time = 0;
				m_AnimationDelay = 0;
				m_attack = false;
				m_move = false;

				m_PlayerState = PLAYER_STATE_GROUND;
			}
		}
		else if (m_AnimationDelay >= 70 && m_comboCount == 1 && !m_HitInpact)
		{
			m_Time = 0;
			m_AnimationDelay = 0;
			m_attack = false;
			m_move = false;
			m_PlayerState = PLAYER_STATE_GROUND;
		}

		



		if (60 <= m_AnimationDelay && m_AnimationDelay < 80)
		{
			//コンボアニメーション2
			if (Input::GetKeyTrigger(VK_LBUTTON) && m_comboCount == 1 )
			{
				m_attack = false;
				if (m_NextAnimationName != "SlashAttack2")
				{
					m_Time = 0.0f;
					m_BlendTime = 0.0f;
					m_AnimationDelay = 0;
					m_AnimationName = m_NextAnimationName;
					m_NextAnimationName = "SlashAttack2";
					m_attack = true;
					m_comboCount = 2;
					m_AnimationDelay = 0;
					m_AttackSE->Volume(0.1f);
					m_AttackSE->Play();
					m_move = true;
				}
				m_PlayerState = PLAYER_STATE_ATTACK2;
			}
		}

		
	}
}

void Player::UpdateAttack2()
{
	m_idle = true;
	if (m_attack)
	{
		m_AnimationDelay++;
		if (m_AnimationDelay >= 70 && m_comboCount == 2)
		{
			m_AnimationDelay = 0;
			m_attack = false;
			m_fainalAttack = true;
			m_move = false;
			m_PlayerState = PLAYER_STATE_GROUND;
		}
		//コンボアニメーション3
		if (60 <= m_AnimationDelay && m_AnimationDelay < 85)
		{
			if (Input::GetKeyTrigger(VK_LBUTTON) && m_fainalAttack)
			{
				m_attack = false;
				if (m_NextAnimationName != "SlashAttack3")
				{
					m_Time = 0.0f;
					m_BlendTime = 0.0f;
					m_AnimationName = m_NextAnimationName;
					m_NextAnimationName = "SlashAttack3";
					m_attack = true;
					m_comboCount = 3;
					m_AttackSE->Volume(0.1f);
					m_AttackSE->Play();
					m_move = true;

					
					

				}
				m_PlayerState = PLAYER_STATE_ATTACK3;
			}
		}
	}
	
}

void Player::UpdateAttack3()
{
	m_idle = true;
	if (m_attack)
	{
		m_AnimationDelay++;
		m_fainalAttack = false;
		/*m_speed = 0.1f;
		directionZ = cameraFoward * m_speed;*/
		if (m_AnimationDelay >= 180 && m_comboCount == 3)
		{	
			m_AnimationDelay = 0;
			m_attack = false;
			m_move = false;
			m_comboCount = 0;
			m_speed = 0.3f;
			directionZ = m_speed * GetForward();
			m_PlayerState = PLAYER_STATE_GROUND;
		}
		if (m_AnimationDelay >= 140 && m_AnimationDelay <=150)
		{
			Scene* scene = Manager::GetScene();
			Camera* camera = scene->GetGameObject<Camera>();
			camera->Shake(0.1f);
			
		}
	}
	D3DXVECTOR3 direction = directionX + directionZ;
	//正規化します
	D3DXVec3Normalize(&direction, &direction);
	//PositonにSpeed加算します
	m_Position += direction * m_speed;
}

void Player::UpdateJump()
{
	m_idle = true;
	/*D3DXVECTOR3 directionX(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 directionZ(0.0f, 0.0f, 0.0f);*/

	if (Input::GetKeyPress('W')) {
		directionZ = cameraFoward * 0.1f;
	}
	if (Input::GetKeyPress('S')) {
		directionZ = -cameraFoward * 0.1f;
	}
	if (Input::GetKeyPress('A')) {
		directionX = -cameraRight * 0.1f;
	}
	if (Input::GetKeyPress('D')) {
		directionX = cameraRight * 0.1f;
	}


	//x,zを加算します
	D3DXVECTOR3 direction = directionX + directionZ;
	//正規化します
	D3DXVec3Normalize(&direction, &direction);
	//PositonにSpeed加算します
	m_Position += direction * m_speed;

	if (m_IsGround == true)
	{
		
		m_PlayerState = PLAYER_STATE_GROUND;
	}
}

void Player::UpdateGuard()
{
	m_idle = false;
	Scene* scene = Manager::GetScene();
	Enemy* enemy = scene->GetGameObject<Enemy>();

	if (m_startGuard && enemy->GetEnemyHitPlayer() && !m_InpactGuard || 
		m_startGuard && m_Rockhit && !m_InpactGuard)
	{
		if (m_NextAnimationName != "GuardImpact")
		{
			m_Time = 0.0f;
			m_AnimationName = m_NextAnimationName;
			m_NextAnimationName = "GuardImpact";
			m_move = true;
			m_InpactGuard = true;
			m_SuccessGuard = true;

			
		}
		
	}

	

	if (Input::GetKeyPress(VK_RBUTTON) && m_startGuard && !m_InpactGuard)
	{
		if (m_NextAnimationName != "IsGuard")
		{
			m_Time = 0.0f;
			m_AnimationName = m_NextAnimationName;
			m_NextAnimationName = "IsGuard";
			m_move = true;
			m_isGuard = true;
		}
	}
	else if(!Input::GetKeyPress(VK_RBUTTON))
	{
		if (m_NextAnimationName != "EndGuard" && !m_EndGuard)
		{
			m_Time = 0.0f;
			m_AnimationName = m_NextAnimationName;
			m_NextAnimationName = "EndGuard";
			m_move = false;
			m_EndGuard = true;

		}	
	}

	if (m_InpactGuard)
	{
		m_AnimationDelay++;
		m_speed = 0.1f;
		directionZ = -cameraFoward * m_speed;
	}

	if (m_AnimationDelay > 40 && m_InpactGuard)
	{
		m_AnimationDelay = 0;
		m_InpactGuard = false;
		m_SuccessGuard = false;
	}


	if (m_EndGuard)
	{
		m_AnimationDelay++;
	}

	if (m_AnimationDelay > 20 && m_EndGuard)
	{
		m_AnimationDelay = 0;
		m_isGuard = m_startGuard = m_EndGuard = m_InpactGuard =  m_SuccessGuard = false;
		m_PlayerState = PLAYER_STATE_GROUND;
	}

	//x,zを加算します
	D3DXVECTOR3 direction = directionX + directionZ;


	//正規化します
	D3DXVec3Normalize(&direction, &direction);

	//PositonにSpeed加算します
	m_Position += direction * m_speed;
}

void Player::UpdateDead()
{
	m_AnimationDelay++;
	if (m_AnimationDelay >= 100)
	{
		m_Time = 120;

	}
	if (m_AnimationDelay >= 180)
	{
		m_GameOver = true;
	}
	
}

void Player::SetCollision(aiNode* node, aiMatrix4x4 matrix)
{
	Scene* scene = Manager::GetScene();
	Enemy* enemy = scene->GetGameObject<Enemy>();

	std::string BoneName = node->mName.C_Str();

	//boneの位置特定
	if (BoneName == "mixamorig:RightHandPinky4")
	{

		if (m_BonePos.x - m_BoneScale.x - 0.5f < enemy->GetPosition().x &&
			enemy->GetPosition().x < m_BonePos.x + m_BoneScale.x + 0.5f &&
			m_BonePos.z - m_BoneScale.z - 0.5f < enemy->GetPosition().z &&
			enemy->GetPosition().z < m_BonePos.z + m_BoneScale.z + 0.5f && !m_InvincibilityFlag
			&& length<5.0f)
		{
			m_PlayerHitEnemy = true;
		}
		else
		{
			m_PlayerHitEnemy = false;
		}
	}

	if (BoneName == "mixamorig:RightFoot")
	{

	}

	//Matrix変換
	m_WorldMatrix._11 = matrix.a1; 
	m_WorldMatrix._12 = matrix.b1; 
	m_WorldMatrix._13 = matrix.c1; 
	m_WorldMatrix._14 = matrix.d1;

	m_WorldMatrix._21 = matrix.a2; 
	m_WorldMatrix._22 = matrix.b2; 
	m_WorldMatrix._23 = matrix.c2; 
	m_WorldMatrix._24 = matrix.d2;

	m_WorldMatrix._31 = matrix.a3; 
	m_WorldMatrix._32 = matrix.b3;
	m_WorldMatrix._33 = matrix.c3; 
	m_WorldMatrix._34 = matrix.d3;


	m_WorldMatrix._41 = matrix.a4; 
	m_WorldMatrix._42 = matrix.b4; 
	m_WorldMatrix._43 = matrix.c4; 
	m_WorldMatrix._44 = matrix.d4;

	//posの変換
	m_BonePos.x = m_WorldMatrix._41; // 行列の右下の要素がX軸方向の移動成分
	m_BonePos.y = m_WorldMatrix._42; // 行列の右下の要素がY軸方向の移動成分
	m_BonePos.z = m_WorldMatrix._43; // 行列の右下の要素がZ軸方向の移動成分

	//scale変換
	D3DXVECTOR3 x = D3DXVECTOR3(m_WorldMatrix._11, m_WorldMatrix._12, m_WorldMatrix._13);
	D3DXVECTOR3 y = D3DXVECTOR3(m_WorldMatrix._21, m_WorldMatrix._22, m_WorldMatrix._23);
	D3DXVECTOR3 z = D3DXVECTOR3(m_WorldMatrix._31, m_WorldMatrix._32, m_WorldMatrix._33);

	if (m_comboCount == 0)
	{
		m_BoneScale.x = D3DXVec3Length(&x) + 0.1f; //数値は微調整
		m_BoneScale.y = D3DXVec3Length(&y) + 0.1f;
		m_BoneScale.z = D3DXVec3Length(&z) + 0.1f;

		m_BonePos.x += m_Position.x-36.5; //微調整
		m_BonePos.y += m_Position.y;
		m_BonePos.z += m_Position.z-22;
	}


	if (m_comboCount == 1)
	{
		m_BoneScale.x = (D3DXVec3Length(&x) + 9.8f)*10; //数値は微調整
		m_BoneScale.y = (D3DXVec3Length(&y) + 9.8f)*10;
		m_BoneScale.z = (D3DXVec3Length(&z) + 9.8f)*10;

		m_BonePos.x += m_Position.x - 36.5; //微調整
		m_BonePos.y += m_Position.y;
		m_BonePos.z += m_Position.z-22;
	}

	if (m_comboCount == 2)
	{
		m_BoneScale.x = (D3DXVec3Length(&x) + 9.8f) * 10; //数値は微調整
		m_BoneScale.y = (D3DXVec3Length(&y) + 9.8f) * 10;
		m_BoneScale.z = (D3DXVec3Length(&z) + 9.8f) * 10;

		m_BonePos.x += m_Position.x - 36.5; //微調整
		m_BonePos.y += m_Position.y;
		m_BonePos.z += m_Position.z - 22;
	}

	if (m_comboCount == 3)
	{
		m_BoneScale.x = (D3DXVec3Length(&x) + 9.8f) * 10; //数値は微調整
		m_BoneScale.y = (D3DXVec3Length(&y) + 9.8f) * 10;
		m_BoneScale.z = (D3DXVec3Length(&z) + 9.8f) * 10;

		m_BonePos.x += m_Position.x - 36.5; //微調整
		m_BonePos.y += m_Position.y;
		m_BonePos.z += m_Position.z - 22;
	}
	
}

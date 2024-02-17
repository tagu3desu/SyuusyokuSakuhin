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
#include"animationModel.h"
#include"meshField.h"
#include"camera.h"
#include"enemy.h"
#include"staminagage.h"
#include"hpgage.h"
#include"potioncount.h"
#include"field.h"
#include"howleffect.h"
#include"GuardInpacteffect.h"
#include"wepon_sword.h"
#include"collider.h"
#include"title.h"
#include"game.h"
#include"rock.h"
#include"titletexturemanager.h"
#include"rockeffect.h"



void Player::Init()
{
	m_Scene = Manager::GetScene();
	m_Camera = m_Scene->GetGameObject<Camera>();
	m_Enemy = m_Scene->GetGameObject<Enemy>();
	m_MeshField = m_Scene->GetGameObject<MeshField>();
	m_Bullet = m_Scene->GetGameObject<Bullet>();
	m_RockEffect = m_Scene->GetGameObject<RockEffect>();

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
	m_Model->LoadAnimation("asset\\model\\Sword And Shield Idle2.fbx", "SwordIdle2");
	m_Model->LoadAnimation("asset\\model\\Sheath Sword 2.fbx", "onSword");
	m_Model->LoadAnimation("asset\\model\\Sheath Sword 1.fbx", "offSword");
	m_Model->LoadAnimation("asset\\model\\Sword And Shield Slash.fbx", "SlashAttack");
	m_Model->LoadAnimation("asset\\model\\Sword And Shield Slash2.fbx", "SlashAttack2");
	m_Model->LoadAnimation("asset\\model\\Sword And Shield Slash3.fbx", "SlashAttack3");
	m_Model->LoadAnimation("asset\\model\\RotationAttack.fbx", "RotationAttack");
	m_Model->LoadAnimation("asset\\model\\Stable Sword Inward Slash.fbx", "CounterAttack");
	m_Model->LoadAnimation("asset\\model\\GreatSwordBackWalk.fbx", "BackWalk");
	m_Model->LoadAnimation("asset\\model\\Sword And Shield BlockStart.fbx", "StartGuard");
	m_Model->LoadAnimation("asset\\model\\Sword And Shield Block Idle.fbx", "IsGuard");
	m_Model->LoadAnimation("asset\\model\\Sword And Shield BlockEnd.fbx", "EndGuard");
	m_Model->LoadAnimation("asset\\model\\Sword And Shield Impact.fbx", "GuardImpact");
	m_Model->LoadAnimation("asset\\model\\Sword And Shield HitSmallAttack.fbx", "HitSmallImpact");

	//タイトル用のモーション
	m_Model->LoadAnimation("asset\\model\\Sitting.fbx", "TitleIdle");
	

	m_AnimationName = "Idle";
	m_NextAnimationName = "Idle";

	
	m_Scale = D3DXVECTOR3(0.015f, 0.015f, 0.015f);
	m_Speed = 0.1f;

	m_DepthEnable = true;
	
#if 1
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\DepthShadowMappingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
			"shader\\DepthShadowMappingPS.cso");

#else
	Renderer::CreateSkiningVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\skiningVertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\VertexLightingPS.cso");

#endif // 0

	

	

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
	
	m_HitInpactDelay = 0;

	 m_DirectionX = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	 m_DirectionZ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_Sworddrawn = false;
	m_ComboCount=0;
	m_Stamina = 0;
	
	
	if (!Title::GetCheckTitle())
	{
		m_PlayerCollider = m_Scene->AddGameObject<Collider>();
		m_PlayerCollider->SetScale(D3DXVECTOR3(70.0f, 170.0f, 70.0f));
		m_PlayerCollider->SetPosition(D3DXVECTOR3(0.0f, 85.0f, 0.0f));
		m_PlayerCollider->SetTag(PLAYER_TAG);

		m_AnimationCorrection = m_Scene->AddGameObject<AnimationCorrection>();
	}
	


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
	
	
}

void Player::Update()
{



	if ( !Title::GetCheckTitle())
	{
		HPgage* hpgage = m_Scene->GetGameObject<HPgage>();
		PotionCount* potioncount = m_Scene->GetGameObject<PotionCount>();
		Staminagage* staminagage = m_Scene->GetGameObject<Staminagage>();

		 m_DirectionX = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		 m_DirectionZ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		m_Move = false;

		GameObject::Update();
		

		m_Stamina = staminagage->GetStamina();

		m_CameraFoward = m_Camera->GetForward();
		m_CameraRight = m_Camera->GetRight();
		m_CameraFoward.y = 0.0f;
		m_CameraRight.y = 0.0f;
		D3DXVec3Normalize(&m_CameraRight, &m_CameraRight);
		D3DXVec3Normalize(&m_CameraFoward, &m_CameraFoward);

		//HP関連

		m_HP = hpgage->GetHp();


		if (m_SuccessGuard)
		{
			m_InviciblilityStartFlag = true;
		}


		//プレイヤーコライダー
		m_PlayerCollider->SetMatrix(m_Matrix);
		SetColliderInfo(m_PlayerCollider->GetMatrix(),false);


	



		//OBB判定　
		std::vector<Box*> boxes = m_Scene->GetGameObjects<Box>();
		{
			for (Box* box : boxes)
			{
				if (m_PlayerCollider->CollisionChecker(this, box, 0.7f))
				{
					m_PlayerCollider->SetColliderColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
				}
				else
				{
					m_PlayerCollider->SetColliderColor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
				}
			}
		}

	

		m_Potioncount = potioncount->GetCount();
		if (m_Potioncount > 0)
		{
			if (Input::GetKeyTrigger('F'))
			{
				potioncount->SubstractCount(1);
				hpgage->SetHealPoint(200);
			}
		}

	
		

		if (m_RockEffect != nullptr)
		{
			if (!m_InvincibilityFlag && m_RockEffect->GetHit() && !m_SuccessGuard)
			{
				hpgage->SetDamage(100);
				m_InviciblilityStartFlag = true;
				m_DamageReaction = true;
			}
		}
		if (m_Bullet != nullptr)
		{
			if (!m_InvincibilityFlag && m_Bullet->GetHit() && !m_SuccessGuard)
			{
				hpgage->SetDamage(100);
				m_InviciblilityStartFlag = true;
				m_DamageReaction = true;
			}
		}
		

		//無敵時間
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

		

		//GUIにパラメータ表示
		ImGui::SetNextWindowSize(ImVec2(300, 250));
		ImGui::Begin("Player");
		ImGui::InputFloat3("Position", m_Position);
		ImGui::InputFloat("Frame", &m_AnimationDelay);
		ImGui::End();


		//ダメージ処理
		{
			if (m_Enemy != nullptr)
			{
				if (m_DamageReaction && !m_SuccessGuard && !m_HitInpact)
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
				m_HitInpactDelay++;
				if (m_HitInpactDelay > 30)
				{
					m_HitInpactDelay = 0;
					m_DamageReaction = false;
					m_HitInpact = false;
				}
			}
		}



		//死亡処理
		if (m_HP <= 0)
		{

			if (m_NextAnimationName != "IsDead")
			{
				m_Time = 0.0f;
				m_AnimationName = m_NextAnimationName;
				m_NextAnimationName = "IsDead";
				m_BlendTime = 0.0f;
			}
			m_PlayerState = PLAYER_STATE_DEAD;
		}
		//重力
		m_Velocity.y -= 0.015f;

		//ジャンプ用移動
		m_Position += m_Velocity;

		if (m_ComboCount == 3 || m_PlayerState==PLAYER_STATE_GROUND)
		{
			
			//m_Position.x += (m_AnimationCorrection->GetAnimationPosition().x - m_Position.x) / 10.0f;
			//m_Position.z += (m_AnimationCorrection->GetAnimationPosition().z - m_Position.z) / 10.0f;
		}
	

	}
	
	switch (m_PlayerState)
	{
	case PLAYER_STATE_GROUND:
		UpdateGround();
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
	case PLAYER_STATE_ROTATION_ATTACK:
		UpdateRotationAttack();
		break;
	case PLAYER_STATE_COUNTER_ATTACK:
		UpdateCounterAttack();
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
	case PLAYER_STATE_TITLEIDLE:
		UpdateTitleIdle();
		break;
	default:
		break;
	}

	if (Title::GetCheckTitle())
	{
		m_PlayerState = PLAYER_STATE_TITLEIDLE;
	}



	if (m_MeshField != nullptr)
	{
		
		m_MeshField = m_Scene->GetGameObject<MeshField>();
		m_GroundHeight = m_MeshField->GetHeight(m_Position);
		
	}

	
	
	//コンボの入力用
	if (m_AttackMotion1)
	{
		m_ConboflagisAttack2 = true;
	}

	if (m_ConboflagisAttack2)
	{
		m_Framwait++;
		if (m_Framwait > 60)
		{
			m_Framwait = 0;
			m_ConboflagisAttack2 = false;
		}
	}

	if (m_AttackMotion2)
	{
		m_ConboflagisAttack3 = true;	
	}

	if (m_ConboflagisAttack3)
	{
		m_Framwait++;
		if (m_Framwait > 60)
		{
			m_Framwait = 0;
			m_ConboflagisAttack3 = false;
		}

	}



	

	

	//接地
	if (m_Position.y < m_GroundHeight && m_Velocity.y < 0.0f)
	{
		m_IsGround = true;
		m_Position.y = m_GroundHeight;
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

	//m_BoxCollider->Draw();

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
	if (Title::GetCheckTitle())
	{
		m_Matrix = scale * euler * trans;
	}
	else if(!Title::GetCheckTitle())
	{
		m_Matrix = scale * rot * trans;
	}
	
	Renderer::SetWorldMatrix(&m_Matrix);

	m_Model->Update(m_AnimationName.c_str(), m_Time, m_NextAnimationName.c_str(), m_Time, m_BlendTime);


	
	
	if (m_HitStopFlag)
	{
		m_Time += 0.0f;
	}
	else if (m_PlayerState == PLAYER_STATE_ATTACK3)
	{
		m_Time += 0.6f;
	}
	else if (m_Run || m_Walk)
	{
		m_Time += 0.5f;
	}
	else
	{
		m_Time += 0.7f;
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
	//武器の取り出し
	if (Input::GetKeyTrigger('Y')/*(VK_LBUTTON)*/ && !m_Sworddrawn)
	{
		
			if (m_NextAnimationName != "onSword")
			{
				m_Time = 0.0f;
				m_AnimationName = m_NextAnimationName;
				m_NextAnimationName = "onSword";
				m_OnWeponSE->Volume(Scene::m_SEVolume * 0.2);
				m_OnWeponSE->PlaySE();
				m_BlendTime = 0.0f;
			}
			m_OnSword = true;
			m_Sworddrawn = true;
		
	}

	if (Input::GetKeyTrigger('R'))
	{
		if (m_Sworddrawn)//納刀
		{
			if (m_NextAnimationName != "offSword")
			{
				m_Time = 0.0f;
				m_AnimationName = m_NextAnimationName;
				m_NextAnimationName = "offSword";
				m_OffWeponSE->Volume(Scene::m_SEVolume * 0.2);
				m_OffWeponSE->PlaySE();
				m_BlendTime = 0.0f;
			}
			m_OffSword = true;
			
		}
		
	}
	
	if (m_OnSword)
	{
		m_AnimationDelay++;
		if (m_AnimationDelay > 35)
		{
			m_OnSword = false;
			m_AnimationDelay = 0;
		}
	
	}
	if (m_OffSword)
	{
		m_AnimationDelay++;
		if (m_AnimationDelay > 50)
		{
			m_Sworddrawn = false;
			m_AnimationDelay = 0;
			m_OffSword = false;
		}

	}

	////サードパーソンビュー(斜め移動)
	if (Input::GetKeyPress('W')) {

		if (Input::GetKeyPress(VK_LSHIFT) && m_Stamina>0)
		{
			
			 m_DirectionZ = m_CameraFoward * m_Speed;
			if (m_Sworddrawn)
			{
				m_Speed = 0.15f;
				if (m_NextAnimationName != "SwordRun")
				{
					m_AnimationName = m_NextAnimationName;
					m_NextAnimationName = "SwordRun";
					m_BlendTime = 0.0f;
				}
			}
			else
			{
				m_Speed = 0.2f;
				if (m_NextAnimationName != "Run")
				{
					m_AnimationName = m_NextAnimationName;
					m_NextAnimationName = "Run";
					m_BlendTime = 0.0f;
				}
			}	
			D3DXQUATERNION quat;
			D3DXVECTOR3 axis = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			float angle = atan2f(m_CameraFoward.x, m_CameraFoward.z);
			D3DXQuaternionRotationAxis(&quat, &axis, angle);
			D3DXQuaternionSlerp(&m_Quaternion, &m_Quaternion, &quat, 0.3f);	//球面線形補間
			m_Idle = false;
			m_Move = true;
			m_Walk = false;
			m_Run = true;
		}
		else
		{
			m_Speed = 0.1f;
			 m_DirectionZ = m_CameraFoward * m_Speed;

			if (m_Sworddrawn)
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
			float angle = atan2f(m_CameraFoward.x, m_CameraFoward.z);
			D3DXQuaternionRotationAxis(&quat, &axis, angle);
			D3DXQuaternionSlerp(&m_Quaternion, &m_Quaternion, &quat, 0.3f);	//球面線形補間
			m_Idle = true;
			m_Move = true;
			m_Walk = true;
			m_Run = false;
		}
		

	}

	if (Input::GetKeyPress('S')) {
		
		if (Input::GetKeyPress(VK_LSHIFT) && m_Stamina > 0)
		{
			m_Speed = 0.1f;
			 m_DirectionZ = -m_CameraFoward * m_Speed;
			if (m_Sworddrawn)
			{
				m_Speed = 0.15f;
				if (m_NextAnimationName != "SwordRun")
				{
					m_AnimationName = m_NextAnimationName;
					m_NextAnimationName = "SwordRun";
					m_BlendTime = 0.0f;
				}
			}
			else
			{
				m_Speed = 0.2f;
				if (m_NextAnimationName != "Run")
				{
					m_AnimationName = m_NextAnimationName;
					m_NextAnimationName = "Run";
					m_BlendTime = 0.0f;
				}
			}
			D3DXQUATERNION quat;
			D3DXVECTOR3 axis = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			float angle = atan2f(-m_CameraFoward.x, -m_CameraFoward.z);
			/*D3DXQuaternionRotationAxis(&quat, &axis, D3DX_PI);*/
			D3DXQuaternionRotationAxis(&quat, &axis, angle);
			D3DXQuaternionSlerp(&m_Quaternion, &m_Quaternion, &quat, 0.3f);	//球面線形補間
			m_Idle = false;
			m_Move = true;
			m_Walk = false;
			m_Run = true;
		}
		else
		{
			m_Speed = 0.1f;
			 m_DirectionZ = -m_CameraFoward * m_Speed;

			if (m_Sworddrawn)
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
			float angle = atan2f(-m_CameraFoward.x, -m_CameraFoward.z);
			D3DXQuaternionRotationAxis(&quat, &axis, angle);
			D3DXQuaternionSlerp(&m_Quaternion, &m_Quaternion, &quat, 0.3f);	//球面線形補間
			m_Idle = true;
			m_Run = false;
			m_Walk = true;
			m_Move = true;
		}
		
	}

	if (Input::GetKeyPress('A')) {
	
		if (Input::GetKeyPress(VK_LSHIFT) && m_Stamina > 0)
		{
			m_Speed = 0.1f;
			 m_DirectionX = -m_CameraRight * m_Speed;

			D3DXQUATERNION quat;
			D3DXVECTOR3 axis = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			float angle = atan2f(-m_CameraRight.x, -m_CameraRight.z);
			D3DXQuaternionRotationAxis(&quat, &axis, angle);
			D3DXQuaternionSlerp(&m_Quaternion, &m_Quaternion, &quat, 0.3f);	//球面線形補間
			

			if (m_Sworddrawn)
			{
				m_Speed = 0.15f;
				if (m_NextAnimationName != "SwordRun")
				{
					m_AnimationName = m_NextAnimationName;
					m_NextAnimationName = "SwordRun";
					m_BlendTime = 0.0f;
				}
			}
			else
			{
				m_Speed = 0.2f;
				if (m_NextAnimationName != "Run")
				{
					m_AnimationName = m_NextAnimationName;
					m_NextAnimationName = "Run";
					m_BlendTime = 0.0f;
				}
			}
			m_Idle = false;
			m_Move = true;
			m_Walk = false;
			m_Run = true;
		}
		else
		{
			m_Speed = 0.1f;
			m_DirectionX = -m_CameraRight * m_Speed;

			D3DXQUATERNION quat;
			D3DXVECTOR3 axis = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			float angle = atan2f(-m_CameraRight.x, -m_CameraRight.z);
			D3DXQuaternionRotationAxis(&quat, &axis, angle);
			D3DXQuaternionSlerp(&m_Quaternion, &m_Quaternion, &quat, 0.3f);	//球面線形補間
			

			if (m_Sworddrawn)
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
			m_Idle = true;
			m_Run = false;
			m_Walk = true;
			m_Move = true;
		}
		
	}

	if (Input::GetKeyPress('D')) {
	
		if (Input::GetKeyPress(VK_SHIFT) && m_Stamina > 0)
		{
			m_Speed = 0.1f;
			 m_DirectionX = m_CameraRight * m_Speed;

			D3DXQUATERNION quat;
			D3DXVECTOR3 axis = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			float angle = atan2f(m_CameraRight.x, m_CameraRight.z);
			D3DXQuaternionRotationAxis(&quat, &axis, angle);
			D3DXQuaternionSlerp(&m_Quaternion, &m_Quaternion, &quat, 0.3f);	//球面線形補間
			

			if (m_Sworddrawn)
			{
				m_Speed = 0.15f;
				if (m_NextAnimationName != "SwordRun")
				{
					m_AnimationName = m_NextAnimationName;
					m_NextAnimationName = "SwordRun";
					m_BlendTime = 0.0f;
				}
			}
			else
			{
				m_Speed = 0.2f;
				if (m_NextAnimationName != "Run")
				{
					m_AnimationName = m_NextAnimationName;
					m_NextAnimationName = "Run";
					m_BlendTime = 0.0f;
				}
			}

			m_Idle = false;
			m_Move = true;
			m_Walk = false;
			m_Run = true;
		}
		else
		{
			m_Speed = 0.1f;
			 m_DirectionX = m_CameraRight * m_Speed;

			D3DXQUATERNION quat;
			D3DXVECTOR3 axis = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			float angle = atan2f(m_CameraRight.x, m_CameraRight.z);
			D3DXQuaternionRotationAxis(&quat, &axis, angle);
			D3DXQuaternionSlerp(&m_Quaternion, &m_Quaternion, &quat, 0.3f);	//球面線形補間
		

			if (m_Sworddrawn)
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

			m_Idle = true;
			m_Run = false;
			m_Walk = true;
			m_Move = true;
		}
		
	}


	//待機状態
	if (m_Move == false && m_Attack == false && !m_OnSword && !m_OffSword && !m_HitInpact)
	{
		m_Run = false;
		m_Walk = false;
		m_Idle = true;
		if (m_Sworddrawn)
		{
			/*if (m_ComboCount == 3)
			{
				m_AnimationCorrection = m_Scene->GetGameObject<AnimationCorrection>();
				m_Position.x = m_AnimationCorrection->GetAnimationPosition().x;
				m_Position.z = m_AnimationCorrection->GetAnimationPosition().z;
			}*/
			

			if (m_NextAnimationName != "SwordIdle")
			{

				m_AnimationName = m_NextAnimationName;
				m_NextAnimationName = "SwordIdle";
				m_ComboCount = 0;
				m_BlendTime = 0.0f;
			}
		}
		else
		{
			if (m_NextAnimationName != "Idle")
			{
				m_AnimationName = m_NextAnimationName;
				m_NextAnimationName = "Idle";
				m_ComboCount = 0;
				m_BlendTime = 0.0f;
			}
		}
		
	}
	//x,zを加算します
	D3DXVECTOR3 direction =  m_DirectionX +  m_DirectionZ;


	//正規化します
	D3DXVec3Normalize(&direction, &direction);

	//PositonにSpeed加算します
	m_Position += direction *m_Speed;

	
	// プレイヤーの移動ベクトルを更新
	//m_MoveVector = m_Velocity * m_Speed;


	D3DXVECTOR3 m_ColliderPos = m_Position + GetForward() * 2.0f;

	if (Input::GetKeyPress(VK_RBUTTON) && !m_StartGuard && m_Sworddrawn)
	{
		if (m_NextAnimationName != "StartGuard")
		{
			m_AnimationName = m_NextAnimationName;
			m_NextAnimationName = "StartGuard";
			m_BlendTime = 0.0f;
		}
		m_Idle = false;
		m_StartGuard = true;
		m_PlayerState = PLAYER_STATE_GUARD;
	}

	//カウンター攻撃
	if (Input::GetKeyTrigger(VK_LBUTTON) && Input::GetKeyPress(VK_LCONTROL) && !m_Run && m_Sworddrawn && !m_OnSword)
	{
		if (m_NextAnimationName != "CounterAttack")
		{
			m_Time = 0.0f;
			m_BlendTime = 0.0f;
			m_AnimationName = m_NextAnimationName;
			m_NextAnimationName = "CounterAttack";
			m_Attack = true;
			m_Move = true;
			m_Idle = false;
			m_PlayerState = PLAYER_STATE_COUNTER_ATTACK;
		}
	}

	//通常攻撃
	else if (Input::GetKeyTrigger(VK_LBUTTON) && !m_Run && m_Sworddrawn && !m_OnSword && !m_ConboflagisAttack2 && !m_ConboflagisAttack3)
	{
	    	if (m_NextAnimationName != "SlashAttack")
	    	{
	    		m_Time = 0.0f;
	    		m_BlendTime = 0.0f;
	    		m_AnimationName = m_NextAnimationName;
	    		m_NextAnimationName = "SlashAttack";
	    		m_Attack = true;
	    		m_ComboCount = 1;
	    		m_Move = true;
	    		m_Idle = false;
	    		m_AttackMotion1 = true;
	    		m_PlayerState = PLAYER_STATE_ATTACK;
	    	}
	}

	//2段目攻撃
	if (Input::GetKeyTrigger(VK_LBUTTON) && !m_Run && m_Sworddrawn && !m_OnSword && m_ConboflagisAttack2)
	{
		if (m_NextAnimationName != "SlashAttack2")
		{
			m_Time = 0.0f;
			m_BlendTime = 0.0f;
			m_AnimationName = m_NextAnimationName;
			m_NextAnimationName = "SlashAttack2";
			m_Attack = true;
			m_ComboCount = 2;
			m_Move = true;
			m_Idle = false;
			m_AttackMotion2 = true;
			m_PlayerState = PLAYER_STATE_ATTACK2;
		}
	}

	////3段目攻撃
	if (Input::GetKeyTrigger(VK_LBUTTON) && !m_Run && m_Sworddrawn && !m_OnSword && m_ConboflagisAttack3)
	{
		if (m_NextAnimationName != "SlashAttack3")
		{
			m_Time = 0.0f;
			m_BlendTime = 0.0f;
			m_AnimationName = m_NextAnimationName;
			m_NextAnimationName = "SlashAttack3";
			m_Attack = true;
			m_ComboCount = 3;
			m_Move = true;
			m_Idle = false;
			m_PlayerState = PLAYER_STATE_ATTACK3;
		}
	}



	//回転攻撃
	if (Input::GetKeyTrigger('T') && !m_Run && m_Sworddrawn && !m_OnSword)
	{
		if (m_NextAnimationName != "RotationAttack")
		{
			m_Time = 0.0f;
			m_BlendTime = 0.0f;
			m_AnimationName = m_NextAnimationName;
			m_NextAnimationName = "RotationAttack";
			m_Attack = true;
			m_Move = true;
			m_Idle = false;
			m_PlayerState = PLAYER_STATE_ROTATION_ATTACK;
		}
	}

	
	if (Input::GetKeyPress(VK_SPACE))
	{
		if (m_NextAnimationName != "IsRoll")
		{
			m_Time = 0.0f;
			m_AnimationName = m_NextAnimationName;
			m_NextAnimationName = "IsRoll";
			m_Move = true;
			m_Roll = true;
			m_Idle = false;
			m_PlayerState = PLAYER_STATE_ROLL;
		}
	}
}

void Player::UpdateRoll()
{
	if (m_Roll==true)
	{
		m_AnimationDelay++;
		if (Input::GetKeyPress('W')) {
			 m_DirectionZ = m_CameraFoward * 0.1f;
		}
		else
		{
			 m_DirectionZ = GetForward() * 0.1f;
		}
		if (Input::GetKeyPress('S')) {
			 m_DirectionZ = -m_CameraFoward * 0.1f;
		}
		if (Input::GetKeyPress('A')) {
			 m_DirectionX = -m_CameraRight * 0.1f;
		}
		if (Input::GetKeyPress('D')) {
			 m_DirectionX = m_CameraRight * 0.1f;
		}
		if (m_AnimationDelay >= 65)
		{
			m_AnimationDelay = 0;
			m_Roll = false;
			m_Move = false;
			m_Idle = true;
			m_PlayerState = PLAYER_STATE_GROUND;
		}	

		//x,zを加算します
		D3DXVECTOR3 direction =  m_DirectionX +  m_DirectionZ;


		//正規化します
		D3DXVec3Normalize(&direction, &direction);

		//PositonにSpeed加算します
		m_Position += direction * m_Speed;
	}
}

void Player::UpdateAttack()
{
	m_Idle = true;
	if (m_Attack)
	{
		m_AnimationDelay++;

		if (m_AnimationDelay < 50 && 65 <= m_AnimationDelay)
		{
			m_AttackMotion1 = true;
		}
		
		//攻撃判定が発生する時間設定
		if (25 < m_AnimationDelay && m_AnimationDelay < 35)
		{
			m_AttackCollisionFlag = true;
		}
		else
		{
			m_AttackCollisionFlag = false;
		}

		if (m_AnimationDelay >=65 && m_ComboCount == 1)
		{
			m_Time = 0;
			m_AnimationDelay = 0;
			m_Attack = false;
			m_Move = false;
			m_AttackMotion1 = false;
			m_PlayerState = PLAYER_STATE_GROUND;	
		}
	}
}

void Player::UpdateAttack2()
{
	m_Idle = true;
	if (m_Attack)
	{
		m_AnimationDelay++;

		if (m_AnimationDelay < 50 && 70 <= m_AnimationDelay)
		{
			m_AttackMotion2 = true;
		}


		//攻撃判定が発生する時間設定
		if (35 < m_AnimationDelay && m_AnimationDelay < 50)
		{
			m_AttackCollisionFlag = true;
		}
		else
		{
			m_AttackCollisionFlag = false;
		}


		if (m_AnimationDelay >= 70 && m_ComboCount == 2)
		{
			m_AnimationDelay = 0;
			m_Attack = false;
			m_Move = false;
			m_ConboflagisAttack2 = false;
			m_AttackMotion2 = false;
			m_PlayerState = PLAYER_STATE_GROUND;
		}
	}
	
}

void Player::UpdateAttack3()
{
	m_Idle = true;
	if (m_Attack)
	{
		m_AnimationDelay++;

		//攻撃判定が発生する時間設定
		if (70 < m_AnimationDelay && m_AnimationDelay < 80)
		{
			m_AttackCollisionFlag = true;
		}
		else
		{
			m_AttackCollisionFlag = false;
		}

		if (m_AnimationDelay >= 120 && m_ComboCount == 3)
		{	
			m_AnimationDelay = 0;
			m_Attack = false;
			m_Move = false;
			//m_ComboCount = 0;
			m_DirectionZ = m_Speed * GetForward();
			m_ConboflagisAttack3 = false;
	
			
			m_PlayerState = PLAYER_STATE_GROUND;
		}
		if (m_AnimationDelay >= 80 && m_AnimationDelay <=85)
		{
			
			Camera* m_Camera = m_Scene->GetGameObject<Camera>();
			m_Camera->Shake(0.05f);
			
		}
	}

	

	//D3DXVECTOR3 direction =  m_DirectionX +  m_DirectionZ;
	////正規化します
	//D3DXVec3Normalize(&direction, &direction);
	////PositonにSpeed加算します
	//m_Position += direction * m_Speed;
}

void Player::UpdateRotationAttack()
{
	m_Idle = true;
	if (m_Attack)
	{
		m_AnimationDelay++;

		

		//攻撃判定が発生する時間設定
		if (40 < m_AnimationDelay && m_AnimationDelay < 55)
		{
			m_AttackCollisionFlag = true;
		}
		else
		{
			m_AttackCollisionFlag = false;
		}

		if (m_AnimationDelay >= 100)
		{
			m_Time = 0;
			m_AnimationDelay = 0;
			m_Attack = false;
			m_Move = false;
			m_AttackMotion1 = false;
			m_PlayerState = PLAYER_STATE_GROUND;
		}
	}
}

void Player::UpdateCounterAttack()
{
	m_Idle = true;
	if (m_Attack)
	{
		m_AnimationDelay++;

		//攻撃判定が発生する時間設定
		if (55 < m_AnimationDelay && m_AnimationDelay < 85)
		{
			m_AttackCollisionFlag = true;
		}
		else
		{
			m_AttackCollisionFlag = false;
		}

		if (m_AnimationDelay >= 90)
		{
			m_Time = 0;
			m_AnimationDelay = 0;
			m_Attack = false;
			m_Move = false;
			m_AttackMotion1 = false;
			m_PlayerState = PLAYER_STATE_GROUND;
		}
	}

}

void Player::UpdateGuard()
{
	m_Idle = false;
	

	if (m_RockEffect != nullptr)
	{
		if (m_StartGuard && m_RockEffect->GetHit() && !m_InpactGuard)
		{
			if (m_NextAnimationName != "GuardImpact")
			{
				m_Time = 0.0f;
				m_AnimationName = m_NextAnimationName;
				m_NextAnimationName = "GuardImpact";
				m_Move = true;
				m_InpactGuard = true;
				m_SuccessGuard = true;
			}

		}
	}

	if (m_Bullet != nullptr)
	{
		

		if (m_StartGuard && m_Bullet->GetHit() && !m_InpactGuard)
		{
			if (m_NextAnimationName != "GuardImpact")
			{
				m_Time = 0.0f;
				m_AnimationName = m_NextAnimationName;
				m_NextAnimationName = "GuardImpact";
				m_Move = true;
				m_InpactGuard = true;
				m_SuccessGuard = true;


			}

		}
	}

	

	if (Input::GetKeyPress(VK_RBUTTON) && m_StartGuard && !m_InpactGuard)
	{
		if (m_NextAnimationName != "IsGuard")
		{
			m_Time = 0.0f;
			m_AnimationName = m_NextAnimationName;
			m_NextAnimationName = "IsGuard";
			m_Move = true;
			m_IsGuard = true;
		}
	}
	else if(!Input::GetKeyPress(VK_RBUTTON))
	{
		if (m_NextAnimationName != "EndGuard" && !m_EndGuard)
		{
			m_Time = 0.0f;
			m_AnimationName = m_NextAnimationName;
			m_NextAnimationName = "EndGuard";
			m_Move = false;
			m_EndGuard = true;

		}	
	}

	if (m_InpactGuard)
	{
		m_AnimationDelay++;
		m_Speed = 0.1f;
		 m_DirectionZ = -m_CameraFoward * m_Speed;
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
		m_IsGuard = m_StartGuard = m_EndGuard = m_InpactGuard =  m_SuccessGuard = false;
		m_PlayerState = PLAYER_STATE_GROUND;
	}

	//x,zを加算します
	D3DXVECTOR3 direction =  m_DirectionX +  m_DirectionZ;

	//正規化します
	D3DXVec3Normalize(&direction, &direction);

	//PositonにSpeed加算します
	m_Position += direction * m_Speed;
}

void Player::UpdateTitleIdle()
{
	if (m_NextAnimationName != "TitleIdle")
	{
		m_AnimationName = m_NextAnimationName;
		m_NextAnimationName = "TitleIdle";
		m_BlendTime = 0.0f;
	}
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

//アニメーション補正用のクラス
void AnimationCorrection::Init()
{
	m_Scene = Manager::GetScene();
}

void AnimationCorrection::Uninit()
{

}

void AnimationCorrection::Update()
{
	Player* player = m_Scene->GetGameObject<Player>();
	//アニメーションのずれを補正
	AnimationModel* animationmodel;
	animationmodel = player->GetAnimationModel();
	BONE* bone;
	bone = animationmodel->GetBone("mixamorig:Hips");
	bone->WorldMatrix;
	m_Parent = animationmodel->ConvertMatrix(bone->WorldMatrix);
	m_AnimationPosition = MatrixtoPosition(m_Matrix);


	//GUIにパラメータ表示
	ImGui::SetNextWindowSize(ImVec2(300, 250));
	ImGui::Begin("AnimationCorrection");
	ImGui::InputFloat3("hipposition", m_AnimationPosition);
	ImGui::InputFloat3("hipmatrix", m_Matrix);
	ImGui::End();
}

void AnimationCorrection::Draw()
{
	Player* player = m_Scene->GetGameObject<Player>();
	//マトリクス設定
	D3DXMATRIX scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	m_Matrix = scale * rot * trans * m_Parent * player->GetMatrix();
	Renderer::SetWorldMatrix(&m_Matrix);
}

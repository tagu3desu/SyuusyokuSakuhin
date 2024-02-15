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
#include"trail.h"
#include"collider.h"
#include"campField.h"
#include"title.h"
#include"game.h"
#include"rock.h"
#include"titletexturemanager.h"
#include"rockeffect.h"
#include"areachangecollider.h"


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
	//m_Model->LoadAnimation("asset\\model\\Sit To Stand.fbx", "TitleStart");


	m_AnimationName = "Idle";
	m_NextAnimationName = "Idle";

	
	m_Scale = D3DXVECTOR3(0.015f, 0.015f, 0.015f);
	//m_MoveVector = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_speed = 0.1f;

	m_DepthEnable = true;
	

	/*Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\DepthShadowMappingVS.cso");*/

	/*Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\DepthShadowMappingPS.cso");*/
	Renderer::CreateSkiningVertexShader(&m_VertexShader, &m_VertexLayout, 
		"shader\\skiningVertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\VertexLightingPS.cso");

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
	
	m_hitInpactDelay = 0;

	directionX = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	directionZ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_sworddrawn = false;
	m_comboCount=0;
	m_Stamina = 0;
	scene = Manager::GetScene();
	
	if (!Title::GetCheckTitle())
	{
		m_PlayerCollider = scene->AddGameObject<Collider>();
		m_PlayerCollider->SetScale(D3DXVECTOR3(70.0f, 170.0f, 70.0f));
		m_PlayerCollider->SetPosition(D3DXVECTOR3(0.0f, 85.0f, 0.0f));
		m_PlayerCollider->SetTag(PLAYER_TAG);
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

	//m_BoxCollider->Uninit();
}

void Player::Update()
{
	Scene* scene = Manager::GetScene();
	Camera* camera = scene->GetGameObject<Camera>();

	if ( !Title::GetCheckTitle())
	{
		Enemy* enemy = scene->GetGameObject<Enemy>();
		Staminagage* staminagage = scene->GetGameObject<Staminagage>();
		HPgage* hpgage = scene->GetGameObject<HPgage>();
		PotionCount* potioncount = scene->GetGameObject<PotionCount>();
		RockEffect* rockeffect = scene->GetGameObject<RockEffect>();
		Bullet* bullet = scene->GetGameObject<Bullet>();
		AreaChange* areachange = scene->GetGameObject<AreaChange>();


		directionX = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		directionZ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		m_move = false;

		GameObject::Update();
		D3DXVECTOR3 oldPosition = m_Position;

		m_Stamina = staminagage->GetStamina();

		cameraFoward = camera->GetForward();
		cameraRight = camera->GetRight();
		cameraFoward.y = 0.0f;
		cameraRight.y = 0.0f;
		D3DXVec3Normalize(&cameraRight, &cameraRight);
		D3DXVec3Normalize(&cameraFoward, &cameraFoward);

		//HP関連

		m_HP = hpgage->GetHp();

		
		
	/*	if (areachange->GetAreaChangeFlag())
		{
			m_Position = D3DXVECTOR3(1.4f, 0.0f, -36.0f);
			areachange->SetAreaChangeFlag(false);
		}*/


		if (m_SuccessGuard)
		{
			m_InviciblilityStartFlag = true;
		}


		//プレイヤーコライダー
		m_PlayerCollider->SetMatrix(m_Matrix);
		SetColliderInfo(m_PlayerCollider->GetMatrix(),false);





		//OBB判定　
		std::vector<Box*> boxes = scene->GetGameObjects<Box>();
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

		if (enemy != nullptr)
		{
			enemyhitflag = m_PlayerCollider->CollisionChecker(this, enemy, 1.5f);
		}
		pa = m_PlayerCollider->GetMinDirection();

		



		m_potioncount = potioncount->GetCount();
		if (m_potioncount > 0)
		{
			if (Input::GetKeyTrigger('F'))
			{
				potioncount->SubstractCount(1);
				hpgage->SetHealPoint(200);
			}
		}

	
		if (enemy != nullptr)
		{
			direction = enemy->GetPosition() - m_Position;
			length = D3DXVec3Length(&direction);
		}

		if (rockeffect != nullptr)
		{
			if (!m_InvincibilityFlag && rockeffect->GetHit() && !m_SuccessGuard)
			{
				hpgage->SetDamage(100);
				m_InviciblilityStartFlag = true;
				m_DamageReaction = true;
			}
		}
		if (bullet != nullptr)
		{
			if (!m_InvincibilityFlag && bullet->GetHit() && !m_SuccessGuard)
			{
				hpgage->SetDamage(100);
				m_InviciblilityStartFlag = true;
				m_DamageReaction = true;
			}
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

		

		//GUIにパラメータ表示
		ImGui::SetNextWindowSize(ImVec2(300, 250));
		ImGui::Begin("Player");
		ImGui::InputFloat("Direction", &pa);
		ImGui::InputFloat3("Position", m_Position);
		ImGui::InputFloat("Frame", &m_AnimationDelay);
		ImGui::InputFloat3("HipPosition", m_HipBonePosition);
		ImGui::End();


		////円柱
		//std::vector<Cylinder*> Cylinders = scene->GetGameObjects<Cylinder>();
		//for (Cylinder* cylinder : Cylinders)//範囲for
		//{
		//	D3DXVECTOR3 postion = cylinder->GetPosition();
		//	D3DXVECTOR3 scale = cylinder->GetScale();

		//	D3DXVECTOR3 direction2 = m_Position - postion;
		//	direction2.y = 0.0f;
		//	float length = D3DXVec3Length(&direction2);

		//	if (length < scale.x)
		//	{
		//		if (m_Position.y < postion.y + scale.y - 0.5f)
		//		{
		//			m_Position.x = oldPosition.x;
		//			m_Position.z = oldPosition.z;
		//		}
		//		else
		//		{
		//			groundHeight = postion.y + scale.y + groundHeight; //上判定
		//		}
		//		break;
		//	}

		//}



		//ダメージ処理
		{
			if (enemy != nullptr)
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
				m_hitInpactDelay++;
				if (m_hitInpactDelay > 30)
				{
					m_hitInpactDelay = 0;
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



	//メッシュフィールドとの衝突判定
	//groundHeight = 0.0f;
	MeshField* meshField = scene->GetGameObject<MeshField>();
	BaseCamp* campField = scene->GetGameObject<BaseCamp>();
	

	if (meshField != nullptr)
	{
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
			groundHeight = campField->GetHeight(m_Position);
		}

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


	/*if (!m_HitStopFlag)
	{
		
	}*/
	/*else if(m_HitStopFlag)
	{
		m_Time += 0.0f;
	}*/
	
	if (m_HitStopFlag)
	{
		m_Time += 0.0f;
	}
	else if (m_PlayerState == PLAYER_STATE_ATTACK3)
	{
		m_Time += 0.6f;
	}
	else if (m_run || m_walk)
	{
		m_Time += 0.5f;
	}
	else
	{
		m_Time += 0.7f;
	}

	/*else
	{
		
	}*/


	
	

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

	if (m_AnimationInterpolation)
	{
		m_speed = 4.0f;
		m_AnimationInterpolation = false;
	}

	//武器の取り出し
	if (Input::GetKeyTrigger('Y')/*(VK_LBUTTON)*/ && !m_sworddrawn)
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
				m_OffWeponSE->Volume(Scene::m_SEVolume * 0.2);
				m_OffWeponSE->PlaySE();
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
				m_speed = 0.15f;
				if (m_NextAnimationName != "SwordRun")
				{
					m_AnimationName = m_NextAnimationName;
					m_NextAnimationName = "SwordRun";
					m_BlendTime = 0.0f;
				}
			}
			else
			{
				m_speed = 0.2f;
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
			m_speed = 0.1f;
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
				m_speed = 0.15f;
				if (m_NextAnimationName != "SwordRun")
				{
					m_AnimationName = m_NextAnimationName;
					m_NextAnimationName = "SwordRun";
					m_BlendTime = 0.0f;
				}
			}
			else
			{
				m_speed = 0.2f;
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
			m_speed = 0.1f;
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
				m_speed = 0.15f;
				if (m_NextAnimationName != "SwordRun")
				{
					m_AnimationName = m_NextAnimationName;
					m_NextAnimationName = "SwordRun";
					m_BlendTime = 0.0f;
				}
			}
			else
			{
				m_speed = 0.2f;
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
				m_speed = 0.15f;
				if (m_NextAnimationName != "SwordRun")
				{
					m_AnimationName = m_NextAnimationName;
					m_NextAnimationName = "SwordRun";
					m_BlendTime = 0.0f;
				}
			}
			else
			{
				m_speed = 0.2f;
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


	//待機状態
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

	


	//カウンター攻撃
	if (Input::GetKeyTrigger(VK_LBUTTON) && Input::GetKeyPress(VK_LCONTROL) && !m_run && m_sworddrawn && !m_onSword)
	{
		if (m_NextAnimationName != "CounterAttack")
		{
			m_Time = 0.0f;
			m_BlendTime = 0.0f;
			m_AnimationName = m_NextAnimationName;
			m_NextAnimationName = "CounterAttack";
			m_attack = true;
			m_move = true;
			m_idle = false;
			m_PlayerState = PLAYER_STATE_COUNTER_ATTACK;
		}
	}
	//通常攻撃
	else if (Input::GetKeyTrigger(VK_LBUTTON) && !m_run && m_sworddrawn && !m_onSword && !m_ConboflagisAttack2 && !m_ConboflagisAttack3)
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
	    		m_AttackMotion1 = true;
	    		m_PlayerState = PLAYER_STATE_ATTACK;
	    	}
	}

	//2段目攻撃
	if (Input::GetKeyTrigger(VK_LBUTTON) && !m_run && m_sworddrawn && !m_onSword && m_ConboflagisAttack2)
	{
		if (m_NextAnimationName != "SlashAttack2")
		{
			m_Time = 0.0f;
			m_BlendTime = 0.0f;
			m_AnimationName = m_NextAnimationName;
			m_NextAnimationName = "SlashAttack2";
			m_attack = true;
			m_comboCount = 2;
			m_move = true;
			m_idle = false;
			m_AttackMotion2 = true;
			m_PlayerState = PLAYER_STATE_ATTACK2;
		}
	}

	////3段目攻撃
	if (Input::GetKeyTrigger(VK_LBUTTON) && !m_run && m_sworddrawn && !m_onSword && m_ConboflagisAttack3)
	{
		if (m_NextAnimationName != "SlashAttack3")
		{
			m_Time = 0.0f;
			m_BlendTime = 0.0f;
			m_AnimationName = m_NextAnimationName;
			m_NextAnimationName = "SlashAttack3";
			m_attack = true;
			m_comboCount = 3;
			m_move = true;
			m_idle = false;
			m_PlayerState = PLAYER_STATE_ATTACK3;
		}
	}



	//回転攻撃
	if (Input::GetKeyTrigger('T') && !m_run && m_sworddrawn && !m_onSword)
	{
		if (m_NextAnimationName != "RotationAttack")
		{
			m_Time = 0.0f;
			m_BlendTime = 0.0f;
			m_AnimationName = m_NextAnimationName;
			m_NextAnimationName = "RotationAttack";
			m_attack = true;
			m_move = true;
			m_idle = false;
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

		if (m_AnimationDelay < 50 && 65 <= m_AnimationDelay)
		{
			m_AttackMotion1 = true;
		}
		
		//攻撃判定が発生する時間設定
		if (21 < m_AnimationDelay && m_AnimationDelay < 33)
		{
			m_AttackCollisionFlag = true;
		}
		else
		{
			m_AttackCollisionFlag = false;
		}

		if (m_AnimationDelay >=65 && m_comboCount == 1)
		{
			m_Time = 0;
			m_AnimationDelay = 0;
			m_attack = false;
			m_move = false;
			m_AttackMotion1 = false;
			m_PlayerState = PLAYER_STATE_GROUND;	
		}
	}
}

void Player::UpdateAttack2()
{
	m_idle = true;
	if (m_attack)
	{
		m_AnimationDelay++;

		if (m_AnimationDelay < 50 && 70 <= m_AnimationDelay)
		{
			m_AttackMotion2 = true;
		}


		//攻撃判定が発生する時間設定
		if (30 < m_AnimationDelay && m_AnimationDelay < 50)
		{
			m_AttackCollisionFlag = true;
		}
		else
		{
			m_AttackCollisionFlag = false;
		}


		if (m_AnimationDelay >= 70 && m_comboCount == 2)
		{
			m_AnimationDelay = 0;
			m_attack = false;
			m_fainalAttack = true;
			m_move = false;
			m_ConboflagisAttack2 = false;
			m_AttackMotion2 = false;
			m_PlayerState = PLAYER_STATE_GROUND;
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
		
		/*D3DXMATRIX hipmatrix;
		AnimationModel* animationmodel;
		animationmodel = GetAnimationModel();
		BONE* bone;
		bone = animationmodel->GetBone("mixamorig:Hips");
		hipmatrix = animationmodel->ConvertMatrix(bone->WorldMatrix);*/
		
		D3DXMATRIX hipmatrix;
		AnimationModel* animationmodel;
		animationmodel = GetAnimationModel();
		BONE* bone;
		bone = animationmodel->GetBone("mixamorig:Hips");
		hipmatrix = animationmodel->ConvertMatrix(bone->WorldMatrix);


		if (98 <= m_AnimationDelay && m_AnimationDelay < 100)
		{
			m_HipBonePosition = MatrixtoPosition(hipmatrix);
		}

		//攻撃判定が発生する時間設定
		if (65 < m_AnimationDelay && m_AnimationDelay < 80)
		{
			m_AttackCollisionFlag = true;
		}
		else
		{
			m_AttackCollisionFlag = false;
		}

		if (m_AnimationDelay >= 100 && m_comboCount == 3)
		{	
			m_AnimationDelay = 0;
			m_attack = false;
			m_move = false;
			m_comboCount = 0;
			m_speed = 0.3f;
			directionZ = m_speed * GetForward();
			m_ConboflagisAttack3 = false;
			m_AnimationInterpolation = true;
			
			m_PlayerState = PLAYER_STATE_GROUND;
		}
		if (m_AnimationDelay >= 80 && m_AnimationDelay <=85)
		{
			Scene* scene = Manager::GetScene();
			Camera* camera = scene->GetGameObject<Camera>();
			camera->Shake(0.03f);
			
		}
	}

	

	D3DXVECTOR3 direction = directionX + directionZ;
	//正規化します
	D3DXVec3Normalize(&direction, &direction);
	//PositonにSpeed加算します
	m_Position += direction * m_speed;
}

void Player::UpdateRotationAttack()
{
	m_idle = true;
	if (m_attack)
	{
		m_AnimationDelay++;

		

		//攻撃判定が発生する時間設定
		if (35 < m_AnimationDelay && m_AnimationDelay < 55)
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
			m_attack = false;
			m_move = false;
			m_AttackMotion1 = false;
			m_PlayerState = PLAYER_STATE_GROUND;
		}
	}
}

void Player::UpdateCounterAttack()
{
	m_idle = true;
	if (m_attack)
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
			m_attack = false;
			m_move = false;
			m_AttackMotion1 = false;
			m_PlayerState = PLAYER_STATE_GROUND;
		}
	}

}

void Player::UpdateGuard()
{
	m_idle = false;
	Scene* scene = Manager::GetScene();
	RockEffect* rockeffect = scene->GetGameObject<RockEffect>();
	Bullet* bullet = scene->GetGameObject<Bullet>();

	if (rockeffect != nullptr)
	{
		if (m_startGuard && rockeffect->GetHit() && !m_InpactGuard)
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
	}

	if (bullet != nullptr)
	{
		

		if (m_startGuard && bullet->GetHit() && !m_InpactGuard)
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



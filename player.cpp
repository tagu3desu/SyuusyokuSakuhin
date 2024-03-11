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
#include"itemcount.h"
#include"field.h"
#include"howleffect.h"
#include"GuardInpacteffect.h"
#include"wepon_sword.h"
#include"boxcollider.h"
#include"title.h"
#include"game.h"
#include"rock.h"
#include"titletexturemanager.h"
#include"rockeffect.h"
#include"wepon_shield.h"
#include"shieldefect.h"
#include"healefect.h"
#include"hpgage.h"
#include"staminagage.h"
#include"result.h"
#include"ItemManger.h"
#include"potion.h"
#include"whetstone.h"
#include"inputx.h"
#include"debug.h"
#include"trail.h"
#include"tutorialenemy.h"
void Player::Init()
{
	m_Scene = Manager::GetScene();
	m_Camera = m_Scene->GetGameObject<Camera>();
	m_Enemy = m_Scene->GetGameObject<Enemy>();
	m_MeshField = m_Scene->GetGameObject<MeshField>();



	m_Model = new AnimationModel();
	m_Model->Load("asset\\model\\player\\Paladin J Nordstrom.fbx");


	//納刀状態モーション
	m_Model->LoadAnimation("asset\\model\\player\\Walking.fbx", "Walk");
	m_Model->LoadAnimation("asset\\model\\player\\Standard Run.fbx", "Run");
	m_Model->LoadAnimation("asset\\model\\player\\Unarmed Idle 01.fbx", "Idle");
	m_Model->LoadAnimation("asset\\model\\player\\Sword And Shield Death.fbx", "IsDead");
	m_Model->LoadAnimation("asset\\model\\player\\Sprinting Forward Roll.fbx", "IsRoll");

	//剣モーション
	m_Model->LoadAnimation("asset\\model\\player\\Sword And Shield Walk.fbx", "SwordWalk");
	m_Model->LoadAnimation("asset\\model\\player\\Sword And Shield Run.fbx", "SwordRun");
	m_Model->LoadAnimation("asset\\model\\player\\Sword And Shield Idle.fbx", "SwordIdle");
	m_Model->LoadAnimation("asset\\model\\player\\Sheath Sword 2.fbx", "onSword");
	m_Model->LoadAnimation("asset\\model\\player\\Sheath Sword 1.fbx", "offSword");
	m_Model->LoadAnimation("asset\\model\\player\\Sword And Shield Slash.fbx", "SlashAttack");
	m_Model->LoadAnimation("asset\\model\\player\\Sword And Shield Slash2.fbx", "SlashAttack2");
	m_Model->LoadAnimation("asset\\model\\player\\Sword And Shield Slash3.fbx", "SlashAttack3");
	m_Model->LoadAnimation("asset\\model\\player\\Standing Melee Attack 360 High.fbx", "RotationAttack");
	m_Model->LoadAnimation("asset\\model\\player\\Sword And Shield BlockStart.fbx", "StartGuard");
	m_Model->LoadAnimation("asset\\model\\player\\Sword And Shield Block Idle.fbx", "IsGuard");
	m_Model->LoadAnimation("asset\\model\\player\\Sword And Shield BlockEnd.fbx", "EndGuard");
	m_Model->LoadAnimation("asset\\model\\player\\Sword And Shield Impact.fbx", "GuardImpact");
	m_Model->LoadAnimation("asset\\model\\player\\Victory.fbx", "HealMotion");
	m_Model->LoadAnimation("asset\\model\\player\\Sword And Shield HitSmallAttack.fbx", "HitSmallImpact");
	m_Model->LoadAnimation("asset\\model\\player\\Grinding1.fbx", "StartGlinding");
	m_Model->LoadAnimation("asset\\model\\player\\Grinding2.fbx", "IsGlinding");
	m_Model->LoadAnimation("asset\\model\\player\\Grinding3.fbx", "EndGlinding");
	m_Model->LoadAnimation("asset\\model\\player\\Shoulder Hit And Fall.fbx", "HitBigImpact");
	m_Model->LoadAnimation("asset\\model\\player\\Standing Up.fbx", "ReturnHitBigImpact");



	//タイトル用のモーション
	m_Model->LoadAnimation("asset\\model\\player\\Sitting.fbx", "TitleIdle");


	m_AnimationName = "Idle";
	m_NextAnimationName = "Idle";


	m_Scale = D3DXVECTOR3(0.015f, 0.015f, 0.015f);
	m_Speed = 0.1f;

	m_HP = 300;
	m_Stamina = 1000;

	m_DepthEnable = true;


	Renderer::CreateSkiningVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\skiningVertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\VertexLightingPS.cso");



	m_OnWeponSE = AddComponent<Audio>();
	m_OnWeponSE->Load("asset\\audio\\SE\\剣を抜く.wav");

	m_OffWeponSE = AddComponent<Audio>();
	m_OffWeponSE->Load("asset\\audio\\SE\\剣を鞘にしまう.wav");

	m_GuardSE = AddComponent<Audio>();
	m_GuardSE->Load("asset\\audio\\SE\\剣で打ち合う2.wav");

	m_HealSE = AddComponent<Audio>();
	m_HealSE->Load("asset\\audio\\SE\\回復魔法1.wav");

	m_FootSE = AddComponent<Audio>();
	m_FootSE->Load("asset\\audio\\SE\\足音.wav");

	m_GlindingSE = AddComponent<Audio>();
	m_GlindingSE->Load("asset\\audio\\SE\\武器を研ぐ.wav");

	m_AttackCV1 = AddComponent<Audio>();
	m_AttackCV1->Load("asset\\audio\\SE\\攻撃1段目.wav");

	m_AttackCV2 = AddComponent<Audio>();
	m_AttackCV2->Load("asset\\audio\\SE\\攻撃2段目.wav");


	m_AttackCV3 = AddComponent<Audio>();
	m_AttackCV3->Load("asset\\audio\\SE\\攻撃3段目.wav");

	m_GetDamegeCVS = AddComponent<Audio>();
	m_GetDamegeCVS->Load("asset\\audio\\SE\\「うっ！」.wav");

	m_GetDamegeCVB = AddComponent<Audio>();
	m_GetDamegeCVB->Load("asset\\audio\\SE\\「くおぉっ！」.wav");

	m_Time = 0.0f;
	m_BlendTime = 0.0f;
	m_AnimationDelay = 0.0f;

	m_HitInpactDelay = 0;

	m_DirectionX = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_DirectionZ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_Sworddrawn = false;
	m_ComboCount = 0;


	m_Sword = m_Scene->AddGameObject<Sword>();
	m_Shield = m_Scene->AddGameObject<Shield>();
	if (!Title::GetCheckTitle())
	{
		m_ItemManager = m_Scene->AddGameObject<ItemManager>();

		m_PlayerCollider = m_Scene->AddGameObject<BoxCollider>();
		m_PlayerCollider->SetScale(D3DXVECTOR3(70.0f, 170.0f, 70.0f));
		m_PlayerCollider->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	


		m_HPgage = m_Scene->AddGameObject<HPgage>(SPRITE_LAYER);
		m_Staminagage = m_Scene->AddGameObject<Staminagage>(SPRITE_LAYER);

		m_PlayerAnimationCorrection = m_Scene->AddGameObject<PlayerAnimationCorrection>();
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
	m_Camera = m_Scene->GetGameObject<Camera>();



	if (!Title::GetCheckTitle())
	{
		
		m_TutorialEnemy = m_Scene->GetGameObject<TutorialEnemy>();
		HPgage* hpgage = m_Scene->GetGameObject<HPgage>();
		Staminagage* staminagage = m_Scene->GetGameObject<Staminagage>();
		Potion* potion = m_Scene->GetGameObject<Potion>();
		WheteStone* whetestone = m_Scene->GetGameObject<WheteStone>();
		Trail* trail = m_Scene->GetGameObject<Trail>();
		m_DebugSystem = m_Scene->GetGameObject<DebugSystem>();
		m_RockEffect = m_Scene->GetGameObject<RockEffect>();
		m_Bullet = m_Scene->GetGameObject<Bullet>();
		m_Enemy = m_Scene->GetGameObject<Enemy>();
		m_Sword = m_Scene->GetGameObject<Sword>();


		m_DirectionX = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_DirectionZ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		m_Move = false;


		if (m_DebugSystem->GetDebugWindowEnable())
		{
			bool  checkhit = m_Sword->GetSwordHit();

			////GUIにパラメータ表示
			ImGui::SetNextWindowSize(ImVec2(300, 250));
			ImGui::Begin("Player");
			ImGui::InputFloat3("Position", m_Position);
			ImGui::InputFloat("Frame", &m_AnimationDelay);
			ImGui::InputFloat("HitFrame", &m_HitInpactDelay);
			ImGui::InputInt("HP", &m_HP);
			ImGui::InputInt("Stamina", &m_Stamina);
			ImGui::Checkbox("AttackHit", &checkhit);
			ImGui::Checkbox("TrailEnable", &m_TrailEnable);
			ImGui::Checkbox("StartGuard", &m_StartGuard);
			ImGui::Checkbox("IsGuard", &m_IsGuard);
			ImGui::Checkbox("EndGuard", &m_EndGuard);
			ImGui::End();

			trail->SetTrailEnable(m_TrailEnable);
		}


		GameObject::Update();


		m_CameraFoward = m_Camera->GetForward();
		m_CameraRight = m_Camera->GetRight();
		m_CameraFoward.y = 0.0f;
		m_CameraRight.y = 0.0f;
		D3DXVec3Normalize(&m_CameraRight, &m_CameraRight);
		D3DXVec3Normalize(&m_CameraFoward, &m_CameraFoward);

		//HP関連
		if (hpgage != nullptr)
		{
			m_HP = hpgage->GetHp();
		}
		if (staminagage != nullptr)
		{
			m_Stamina = staminagage->GetStamina();
		}


		if (m_SuccessGuard)
		{
			m_InviciblilityStartFlag = true;
		}


		//プレイヤーコライダー
		m_PlayerCollider->SetMatrix(m_Matrix);
		AnimationModel* animationmodel;
		animationmodel = GetAnimationModel();
		BONE* bone;
		bone = animationmodel->GetBone("mixamorig:Hips");
		m_PlayerCollider->SetBoneEnable(true);
		m_PlayerCollider->SetBoneMatrix(animationmodel->ConvertMatrix(bone->WorldMatrix));

		SetColliderInfo(m_PlayerCollider->GetMatrix());









		if ((Input::GetKeyTrigger('F') || (InputX::IsButtonTriggered(0, XINPUT_GAMEPAD_X))) && !m_Glinding && !m_UsePotion && !m_Animating && !m_Attack && !m_Sworddrawn
			&& !m_ItemManager->GetShowFlag())
		{
			m_Run = false;
			m_Walk = false;
			if (m_ItemManager->GetEnablePotion())
			{
				if (potion->GetCount() >= 1)
				{
					m_ItemManager->UsePotion();
					m_UsePotion = true;
				}

			}
			if (m_ItemManager->GetEnableWheteSton())
			{
				if (whetestone->GetCount() >= 1)
				{
					m_ItemManager->UseWheteStone();
					m_Glinding = true;
					m_StartGlinding = true;
				}

			}
		}


		//砥ぐ
		if (m_Glinding)
		{
			m_AnimationDelay++;
			{//砥ぎ開始

				if (m_NextAnimationName != "StartGlinding" && m_StartGlinding)
				{
					m_Time = 0.0f;
					m_AnimationName = m_NextAnimationName;
					m_NextAnimationName = "StartGlinding";
					m_Animating = true;
					m_BlendTime = 0.0f;
				}

				if (m_AnimationDelay > 20 && m_StartGlinding)
				{
					m_AnimationDelay = 0.0f;
					m_Animating = false;
					m_StartGlinding = false;
					m_IsGlinding = true;
				}
			}
			{//砥ぎ中
				if (m_NextAnimationName != "IsGlinding" && m_IsGlinding)
				{
					m_Time = 0.0f;
					m_AnimationName = m_NextAnimationName;
					m_NextAnimationName = "IsGlinding";
					m_Animating = true;
					m_BlendTime = 0.0f;
				}

				if (m_AnimationDelay > 70 && m_IsGlinding)
				{
					m_SharpnessUpFlag = true;
					if (!m_GlindingSEFlag)
					{
						m_GlindingSE->Volume(Scene::m_SEVolume);
						m_GlindingSE->PlaySE();
						m_GlindingSEFlag = true;
					}
				}

				if (m_AnimationDelay > 100 && m_IsGlinding)
				{
					m_AnimationDelay = 0.0f;
					m_Animating = false;
					m_IsGlinding = false;
					m_EndGlinding = true;
				}
			}
			{//砥ぎ中
				if (m_NextAnimationName != "EndGlinding" && m_EndGlinding)
				{
					m_Time = 0.0f;
					m_AnimationName = m_NextAnimationName;
					m_NextAnimationName = "EndGlinding";
					m_Animating = true;

					m_BlendTime = 0.0f;
				}
				if (m_AnimationDelay > 40 && m_EndGlinding)
				{
					m_AnimationDelay = 0.0f;
					m_Animating = false;
					m_IsGlinding = false;
					m_EndGlinding = false;
					m_Glinding = false;
					m_GlindingSEFlag = false;
				}
			}
		}

		if (m_SharpnessUpFlag)
		{
			m_SharpnessUpCount++;
			if (m_SharpnessUpCount >= 100)
			{
				m_SharpnessUpCount = 0.0f;
				m_SharpnessUpFlag = false;
			}
		}

		//回復薬使用

		if (m_UsePotion && !m_Healing)
		{
			m_Healing = true;
			m_HealSE->Volume(Scene::m_SEVolume * 0.5);
			m_HealSE->PlaySE();
			HealEffect* healeffect = m_Scene->AddGameObject<HealEffect>(EFFECT_LAYER);
			healeffect->SetScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
			healeffect->SetPosition(m_Position + (D3DXVECTOR3(0.0f, 1.5f, 0.0f)));
			m_Animating = true;
			hpgage->SetHealPoint(50);
		}

		if (m_Healing)
		{
			if (m_NextAnimationName != "HealMotion")
			{
				m_Time = 0.0f;
				m_AnimationName = m_NextAnimationName;
				m_NextAnimationName = "HealMotion";
				m_BlendTime = 0.0f;
			}
			m_HealAnimationDelay++;
			if (m_HealAnimationDelay > 70)
			{
				m_HealAnimationDelay = 0.0f;
				m_Healing = false;
				m_UsePotion = false;
				m_Animating = false;
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

		//カメラ補正用
		m_CameraCorrectionPosition = D3DXVECTOR3(m_PlayerAnimationCorrection->GetAnimationPosition().x, m_Position.y, m_PlayerAnimationCorrection->GetAnimationPosition().z);
		

		//被ダメアニメーション
		{
			//ダメージリアクション大
			if (m_BigDamageReaction && !m_SuccessGuard && !m_BigHitInpact)
			{
				m_Attack = false;
				m_Move = false;
				m_Run = false;
				m_Walk = false;
				m_HitInpactDelay = 0;
				m_AttackCollisionFlag = false;
				m_PlayerState = PLAYER_STATE_GROUND;
				if (m_NextAnimationName != "HitBigImpact")
				{
					m_Time = 0.0f;
					m_AnimationName = m_NextAnimationName;
					m_NextAnimationName = "HitBigImpact";
					m_BlendTime = 0.0f;
					m_BigHitInpact = true;
				}
			}

			if (m_BigHitInpact)
			{
				
				m_Speed = 0.05f;
				m_DirectionZ = -GetForward() * m_Speed;
				m_HitInpactDelay++;
				m_Animating = true;
				if (m_HitInpactDelay > 80)
				{
					m_HitInpactDelay = 0;
					m_Speed = 0.0f;
					m_ReturnHitInpact = true;

				}

				if (m_ReturnHitInpact)
				{
					if (m_NextAnimationName != "ReturnHitBigImpact")
					{
						m_Time = 0.0f;
						m_AnimationName = m_NextAnimationName;
						m_NextAnimationName = "ReturnHitBigImpact";
						m_BlendTime = 0.0f;
						m_ReturnHitAnimation = true;
						m_Speed = 0.0f;
					}

					if (m_ReturnHitAnimation)
					{
						m_Animating = true;
						m_ReturnInpactDelay++;
						m_Speed = 0.0f;
						if (m_ReturnInpactDelay > 60)
						{
							m_ReturnHitAnimation = false;
							m_ReturnHitInpact = false;
							m_Animating = false;
							m_BigDamageReaction = false;
							m_BigHitInpact = false;
						}
					}


				}

				//x,zを加算します
				D3DXVECTOR3 direction = m_DirectionX + m_DirectionZ;

				//正規化します
				D3DXVec3Normalize(&direction, &direction);

				//PositonにSpeed加算します
				m_Position += direction * m_Speed;
			}

			//ダメージリアクション小
			if (m_SmallDamageReaction && !m_SuccessGuard && !m_SmallHitInpact)
			{
				m_Attack = false;
				m_Move = false;
				m_HitInpactDelay = 0;
				m_AttackCollisionFlag = false;
				m_PlayerState = PLAYER_STATE_GROUND;
				if (m_NextAnimationName != "HitSmallImpact")
				{
					m_Time = 0.0f;
					m_AnimationName = m_NextAnimationName;
					m_NextAnimationName = "HitSmallImpact";
					m_BlendTime = 0.0f;
					m_SmallHitInpact = true;
				}
			}

			if (m_SmallHitInpact)
			{
				
				m_HitInpactDelay++;
				m_Animating = true;
				if (m_HitInpactDelay > 30)
				{
					m_Animating = false;
					m_HitInpactDelay = 0;
					m_SmallDamageReaction = false;
					m_SmallHitInpact = false;
				}
			}
		}



		//死亡処理
		if (m_HP <= 0)
		{
			m_Dead = true;
			if (!m_DeadUIFlag)
			{
				m_DeadUIFlag = true;
			}
			if (m_NextAnimationName != "IsDead")
			{
				m_Time = 0.0f;
				m_AnimationName = m_NextAnimationName;
				m_NextAnimationName = "IsDead";
				m_BlendTime = 0.0f;
			}
			m_PlayerState = PLAYER_STATE_DEAD;
		}

		if (m_DeadUIFlag)
		{
			m_DeadUIFlagCount++;
			if (m_DeadUIFlagCount > 150)
			{
				m_DeadUIFlag = false;
			}
		}

		//重力
		m_Velocity.y -= 0.015f;

		//ジャンプ用移動
		m_Position += m_Velocity;




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

	//OBB判定　

	std::vector<Rock*> rocks = m_Scene->GetGameObjects<Rock>();
	{
		for (Rock* rock : rocks)
		{
			if (m_PlayerCollider->CollisionChecker(this, rock, 0.7f))
			{
				m_PlayerCollider->SetColliderColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
				break;
			}
			else
			{
				m_PlayerCollider->SetColliderColor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
			}
		
			
		}
	}

	//プレイヤーの被ダメ処理
	if (!Title::GetCheckTitle())
	{
		HPgage* hpgage = m_Scene->GetGameObject<HPgage>();
		m_RockEffect = m_Scene->GetGameObject<RockEffect>();
		m_Shield = m_Scene->GetGameObject<Shield>();
		m_Sword = m_Scene->GetGameObject<Sword>();
		if (m_RockEffect != nullptr)
		{
			if (m_PlayerCollider->CollisionChecker(this, m_RockEffect, 0.6f))
			{
				if (m_SuccessGuard && !m_GuardEffect)
				{
					m_GuardSE->Volume(Scene::m_SEVolume);
					m_GuardSE->PlaySE();

					ShieldEffect* shieldeffect = m_Scene->AddGameObject<ShieldEffect>(EFFECT_LAYER);
					shieldeffect->SetScale(D3DXVECTOR3(7.0f, 7.0f, 7.0f));
					shieldeffect->SetPosition(MatrixtoPosition(m_Shield->GetMatrix()));
					m_Camera->Shake(0.05f);
					m_GuardEffect = true;
				}
				else if (!m_InvincibilityFlag && !m_SuccessGuard)
				{
					hpgage->SetDamage(70);
					m_GetDamegeCVB->Volume(Scene::m_SEVolume * 0.5f);
					m_GetDamegeCVB->PlaySE();
					m_InviciblilityStartFlag = true;
					m_BigDamageReaction = true;
				}
			}
		}
		//チュートリアル
		if (m_TutorialEnemy != nullptr)
		{
			if (m_TutorialEnemy->GetPunchAttackHit())
			{
				if (m_SuccessGuard && !m_GuardEffect)
				{
					m_GuardSE->Volume(Scene::m_SEVolume);
					m_GuardSE->PlaySE();
					ShieldEffect* shieldeffect = m_Scene->AddGameObject<ShieldEffect>(EFFECT_LAYER);
					shieldeffect->SetScale(D3DXVECTOR3(5.0f, 5.0f, 5.0f));
					shieldeffect->SetPosition(MatrixtoPosition(m_Shield->GetMatrix()));
					m_Camera->Shake(0.05f);
					m_GuardEffect = true;
				}
				else if (!m_InvincibilityFlag && !m_SuccessGuard)
				{
					hpgage->SetDamage(40);
					m_GetDamegeCVS->Volume(Scene::m_SEVolume * 0.5f);
					m_GetDamegeCVS->PlaySE();
					m_InviciblilityStartFlag = true;
					m_SmallDamageReaction = true;
				}
			}
		}

		//ゲーム
		if (m_Enemy != nullptr)
		{
			if (m_Enemy->GetJumpAttackHit())
			{
				if (m_SuccessGuard && !m_GuardEffect)
				{
					m_GuardSE->Volume(Scene::m_SEVolume);
					m_GuardSE->PlaySE();
					ShieldEffect* shieldeffect = m_Scene->AddGameObject<ShieldEffect>(EFFECT_LAYER);
					shieldeffect->SetScale(D3DXVECTOR3(7.0f, 7.0f, 7.0f));
					shieldeffect->SetPosition(MatrixtoPosition(m_Shield->GetMatrix()));
					m_Camera->Shake(0.05f);
					m_GuardEffect = true;
				}
				else if (!m_InvincibilityFlag && !m_SuccessGuard)
				{
					hpgage->SetDamage(80);
					m_GetDamegeCVB->Volume(Scene::m_SEVolume * 0.5f);
					m_GetDamegeCVB->PlaySE();
					m_InviciblilityStartFlag = true;
					m_BigDamageReaction = true;
				}
			}

			if (m_Enemy->GetPunchAttackHit())
			{
				if (m_SuccessGuard && !m_GuardEffect)
				{
					m_GuardSE->Volume(Scene::m_SEVolume);
					m_GuardSE->PlaySE();
					ShieldEffect* shieldeffect = m_Scene->AddGameObject<ShieldEffect>(EFFECT_LAYER);
					shieldeffect->SetScale(D3DXVECTOR3(7.0f, 7.0f, 7.0f));
					shieldeffect->SetPosition(MatrixtoPosition(m_Shield->GetMatrix()));
					m_Camera->Shake(0.05f);
					m_GuardEffect = true;
				}
				else if (!m_InvincibilityFlag && !m_SuccessGuard)
				{
					m_GetDamegeCVS->Volume(Scene::m_SEVolume * 0.5f);
					m_GetDamegeCVS->PlaySE();
					hpgage->SetDamage(50);
					m_InviciblilityStartFlag = true;
					m_SmallDamageReaction = true;
				}
			}
		}

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
		m_FrameWait++;
		if (m_FrameWait > 60)
		{
			m_FrameWait = 0;
			m_ConboflagisAttack2 = false;
		}
	}

	if (m_AttackMotion2)
	{
		m_ConboflagisAttack3 = true;
	}

	if (m_ConboflagisAttack3)
	{
		m_FrameWait++;
		if (m_FrameWait > 55)
		{
			m_FrameWait = 0;
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


	//移動時の処理
	D3DXVECTOR3 direction = m_DirectionX + m_DirectionZ;
	D3DXVec3Normalize(&direction, &direction);
	m_Position += direction * m_Speed;


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
	D3DXMATRIX  world, scale, rot, trans, euler;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationQuaternion(&rot, &m_Quaternion);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	D3DXMatrixRotationYawPitchRoll(&euler, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	if (Title::GetCheckTitle())
	{
		m_Matrix = scale * euler * trans;
	}
	else if (!Title::GetCheckTitle())
	{
		m_Matrix = scale * rot * trans;
	}

	Renderer::SetWorldMatrix(&m_Matrix);

	m_Model->Update(m_AnimationName.c_str(), m_Time, m_NextAnimationName.c_str(), m_Time, m_BlendTime);




	if (m_HitStopFlag)
	{
		m_Time += 0.0f;
	}
	else if (m_PlayerState == PLAYER_STATE_ROTATION_ATTACK || m_PlayerState==PLAYER_STATE_ATTACK || m_PlayerState==PLAYER_STATE_ATTACK2)
	{
		m_Time += 0.9f;
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
	if ((Input::GetKeyTrigger('Y') || InputX::IsButtonTriggered(0, XINPUT_GAMEPAD_Y)) && !m_Sworddrawn && !m_Animating)
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

	if ((Input::GetKeyTrigger('R') || InputX::IsButtonTriggered(0, XINPUT_GAMEPAD_X)) && !m_Animating && !m_ItemManager->GetShowFlag())
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
		m_Animating = true;
		if (m_AnimationDelay > 35)
		{
			m_Animating = false;
			m_OnSword = false;
			m_AnimationDelay = 0;
		}

	}
	if (m_OffSword)
	{
		m_AnimationDelay++;
		m_Animating = true;
		if (m_AnimationDelay > 50)
		{
			m_Animating = false;
			m_Sworddrawn = false;
			m_AnimationDelay = 0;
			m_OffSword = false;
		}

	}

	////サードパーソンビュー(斜め移動)
	if ((Input::GetKeyPress('W') || InputX::GetThumbLeftY(0) >= 0.2) && !m_Animating) {

		if ((Input::GetKeyPress(VK_LSHIFT) || InputX::IsButtonPressed(0, XINPUT_GAMEPAD_RIGHT_SHOULDER)) && m_Stamina > 0)
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

	if ((Input::GetKeyPress('S') || InputX::GetThumbLeftY(0) <= -0.2) && !m_Animating) {

		if ((Input::GetKeyPress(VK_LSHIFT) || InputX::IsButtonPressed(0, XINPUT_GAMEPAD_RIGHT_SHOULDER)) && m_Stamina > 0)
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

	if ((Input::GetKeyPress('A') || InputX::GetThumbLeftX(0) <= -0.2) && !m_Animating) {

		if ((Input::GetKeyPress(VK_LSHIFT) || InputX::IsButtonPressed(0, XINPUT_GAMEPAD_RIGHT_SHOULDER)) && m_Stamina > 0)
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

	if ((Input::GetKeyPress('D') || InputX::GetThumbLeftX(0) >= 0.2) && !m_Animating) {

		if ((Input::GetKeyPress(VK_SHIFT) || InputX::IsButtonPressed(0, XINPUT_GAMEPAD_RIGHT_SHOULDER)) && m_Stamina > 0)
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
	if (!m_Move&& !m_Attack && !m_OnSword && !m_OffSword && !m_SmallHitInpact && !m_BigHitInpact && !m_Healing && !m_Animating)
	{
		m_Run = false;
		m_Walk = false;
		m_Idle = true;
		m_StartGuard = false;
		m_IsGuard = false;
		m_EndGuard = false;
		m_InpactGuard = false;
		m_FootSoundInterval = 0;
		if (m_Sworddrawn)
		{
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


	//ガード入力
	if ((Input::GetKeyPress(VK_RBUTTON) || InputX::GetRightTrigger(0) >= 0.2) && !m_StartGuard && m_Sworddrawn)
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

	

	//通常攻撃
	if ((Input::GetKeyTrigger(VK_LBUTTON) && !m_DebugSystem->GetDebugWindowEnable() || InputX::IsButtonTriggered(0, XINPUT_GAMEPAD_B)) && !m_Run && m_Sworddrawn && !m_OnSword && !m_ConboflagisAttack2 && !m_ConboflagisAttack3 && !m_Animating  ||
		Input::GetKeyTrigger('X') && !m_Run && m_Sworddrawn && !m_OnSword  && !m_ConboflagisAttack2 && !m_ConboflagisAttack3 && !m_Animating && m_DebugSystem->GetDebugWindowEnable())
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
			m_AttackMagnification = 1.1f;
			m_PlayerState = PLAYER_STATE_ATTACK;
			m_AttackCV1->Volume(Scene::m_SEVolume * 0.5f);
			m_AttackCV1->PlaySE();
		}
	}

	//2段目攻撃
	if ((Input::GetKeyTrigger(VK_LBUTTON) && !m_DebugSystem->GetDebugWindowEnable() || InputX::IsButtonTriggered(0, XINPUT_GAMEPAD_B)) && !m_Run && m_Sworddrawn && !m_OnSword && m_ConboflagisAttack2 && !m_Animating  ||
		Input::GetKeyTrigger('X') && !m_Run && m_Sworddrawn && !m_OnSword && m_ConboflagisAttack2 && !m_Animating && m_DebugSystem->GetDebugWindowEnable())
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
			m_AttackMagnification = 0.8f;
			m_PlayerState = PLAYER_STATE_ATTACK2;

		}
	}

	////3段目攻撃
	if ((Input::GetKeyTrigger(VK_LBUTTON) && !m_DebugSystem->GetDebugWindowEnable() || InputX::IsButtonTriggered(0, XINPUT_GAMEPAD_B)) && !m_Run && m_Sworddrawn && !m_OnSword && m_ConboflagisAttack3 && !m_Animating  ||
		Input::GetKeyTrigger('X') && !m_Run && m_Sworddrawn && !m_OnSword && m_ConboflagisAttack3 && !m_Animating && m_DebugSystem->GetDebugWindowEnable())
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
			m_AttackMagnification = 1.3f;
			m_PlayerState = PLAYER_STATE_ATTACK3;
			m_AttackCV3->Volume(Scene::m_SEVolume * 0.5f);
			m_AttackCV3->PlaySE();
		}
	}



	//回転攻撃
	if ((Input::GetKeyTrigger('T') && !m_DebugSystem->GetDebugWindowEnable() || InputX::IsButtonTriggered(0, XINPUT_GAMEPAD_Y)) && !m_Run && m_Sworddrawn && !m_OnSword && !m_Animating  ||
		Input::GetKeyTrigger('C') && !m_Run && m_Sworddrawn && !m_OnSword && m_DebugSystem->GetDebugWindowEnable())
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
			m_AttackMagnification = 1.4f;
			m_PlayerState = PLAYER_STATE_ROTATION_ATTACK;
			m_AttackCV3->Volume(Scene::m_SEVolume * 0.5f);
			m_AttackCV3->PlaySE();
		}
	}



	if ((Input::GetKeyPress(VK_SPACE) || InputX::IsButtonTriggered(0, XINPUT_GAMEPAD_A)) && !m_Animating)
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

	//足音
	if (m_Walk)
	{

		if (!m_FootSoundFlag)
		{
			m_FootSE->Volume(Scene::m_SEVolume * 0.05f);
			m_FootSE->PlaySE();
			m_FootSoundFlag = true;
		}
		if (m_FootSoundFlag)
		{
			m_FootSoundInterval++;
			if (m_FootSoundInterval >= 30)
			{
				m_FootSoundInterval = 0;
				m_FootSoundFlag = false;
			}
		}
	}

	if (m_Run)
	{
		if (!m_FootSoundFlag)
		{
			m_FootSE->Volume(Scene::m_SEVolume * 0.05f);
			m_FootSE->PlaySE();
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

}

void Player::UpdateRoll()
{
	if (m_Roll == true)
	{
		float speed = 0.01f;
		m_AnimationDelay++;

		
		m_Animating = true;
		m_DirectionZ = GetForward() * speed;

		if (m_AnimationDelay >= 50)
		{
			m_AnimationDelay = 0;
			m_Roll = false;
			m_Move = false;
			m_Idle = true;
			m_Animating = false;
			m_PlayerState = PLAYER_STATE_GROUND;
		}

	}
}

void Player::UpdateAttack()
{
	m_Idle = true;
	if (m_Attack)
	{
		m_AnimationDelay++;

		if (m_AnimationDelay < 40 && 55 <= m_AnimationDelay)
		{
			m_AttackMotion1 = true;
		}

		//攻撃判定が発生する時間設定
		if (20 < m_AnimationDelay && m_AnimationDelay < 30)
		{
			m_AttackCollisionFlag = true;
		}
		else
		{
			m_AttackCollisionFlag = false;
		}

		if (m_AnimationDelay >= 45 && m_ComboCount == 1)
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

		if (m_AnimationDelay < 35 && 60 <= m_AnimationDelay)
		{
			m_AttackMotion2 = true;
		}


		//攻撃判定が発生する時間設定
		if (20 < m_AnimationDelay && m_AnimationDelay < 35)
		{
			m_AttackCollisionFlag = true;
		}
		else
		{
			m_AttackCollisionFlag = false;
		}
		if (25 < m_AnimationDelay && m_AnimationDelay < 27)
		{
			m_AttackCV2->Volume(Scene::m_SEVolume * 0.5f);
			m_AttackCV2->PlaySE();
		}


		if (m_AnimationDelay >= 50 && m_ComboCount == 2)
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
	m_PlayerAnimationCorrection = m_Scene->GetGameObject<PlayerAnimationCorrection>();
	m_Idle = true;
	m_ConboflagisAttack3 = false;
	if (m_Attack)
	{

		
		m_AnimationDelay++;
		


		//攻撃判定が発生する時間設定
		if (50 < m_AnimationDelay && m_AnimationDelay < 70)
		{
			m_AttackCollisionFlag = true;
		}
		else
		{
			m_AttackCollisionFlag = false;
		}

		


		if (m_AnimationDelay >= 104.0f && m_ComboCount == 3)
		{
			m_AnimationDelay = 0;
			m_Attack = false;
			m_Move = false;
			m_DirectionZ = m_Speed * GetForward();
			//m_ConboflagisAttack3 = false;

			m_Position.x = m_PlayerAnimationCorrection->GetAnimationPosition().x;
			m_Position.z = m_PlayerAnimationCorrection->GetAnimationPosition().z;



			m_PlayerState = PLAYER_STATE_GROUND;
		}
		if (m_AnimationDelay >= 80 && m_AnimationDelay <= 85)
		{

			Camera* m_Camera = m_Scene->GetGameObject<Camera>();
			m_Camera->Shake(0.1f);

		}
	}

}

void Player::UpdateRotationAttack()
{
	m_Idle = true;
	if (m_Attack)
	{
		m_AnimationDelay++;



		//攻撃判定が発生する時間設定
		if (25 < m_AnimationDelay && m_AnimationDelay < 45)
		{
			m_AttackCollisionFlag = true;
		}
		else
		{
			m_AttackCollisionFlag = false;
		}

		if (m_AnimationDelay >= 80)
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
	m_RockEffect = m_Scene->GetGameObject<RockEffect>();
	m_Bullet = m_Scene->GetGameObject<Bullet>();
	m_Shield = m_Scene->GetGameObject<Shield>();

	if (m_RockEffect != nullptr)
	{
		if (m_StartGuard && m_Shield->GetShieldHit() && !m_InpactGuard)
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

	if (m_Enemy != nullptr)
	{


		if (m_StartGuard && !m_InpactGuard && m_Enemy->GetJumpAttackHit())
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
		if (m_StartGuard && !m_InpactGuard && m_Enemy->GetPunchAttackHit())
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


	if (m_TutorialEnemy != nullptr)
	{
		if (m_StartGuard && !m_InpactGuard && m_TutorialEnemy->GetJumpAttackHit())
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
		if (m_StartGuard && !m_InpactGuard && m_TutorialEnemy->GetPunchAttackHit())
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

	if (m_InpactGuard)
	{
		InputX::SetVibration(0, 100);
	}
	else if(!m_InpactGuard)
	{
		InputX::StopVibration(0);
	}

	if ((Input::GetKeyPress(VK_RBUTTON) || InputX::GetRightTrigger(0) >= 0.1) && m_StartGuard && !m_InpactGuard)
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
	else if ((!Input::GetKeyPress(VK_RBUTTON) || InputX::GetRightTrigger(0) <= 0.1))
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
		m_DirectionZ = -GetForward() * m_Speed;
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
		m_IsGuard = m_StartGuard = m_EndGuard = m_InpactGuard = m_SuccessGuard = false;
		m_GuardEffect = false;
		m_PlayerState = PLAYER_STATE_GROUND;
	}

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
	if (m_AnimationDelay >= 325)
	{
		m_FaliedUIFlag = true;
	}

}

//アニメーション補正用のクラス
void PlayerAnimationCorrection::Init()
{
	m_Scene = Manager::GetScene();
}

void PlayerAnimationCorrection::Uninit()
{

}

void PlayerAnimationCorrection::Update()
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


	m_DifferencePosition = m_AnimationPosition - m_Oldposition;
	m_Oldposition = m_AnimationPosition;
}

void PlayerAnimationCorrection::Draw()
{
	Player* player = m_Scene->GetGameObject<Player>();
	//マトリクス設定
	if (player != nullptr)
	{
		D3DXMATRIX scale, rot, trans;
		D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
		D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
		D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
		m_Matrix = scale * rot * trans * m_Parent * player->GetMatrix();
		Renderer::SetWorldMatrix(&m_Matrix);
	}

}

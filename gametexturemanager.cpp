#include"main.h"
#include"renderer.h"
#include"manager.h"
#include"scene.h"
#include"gametexturemanager.h"
#include"textureload.h"
#include"Loading.h"
#include"title.h"
#include"game.h"
#include"enemy.h"
#include"input.h"
#include"sword.h"
#include"player.h"
#include"camera.h"
#include"ItemManger.h"
#include"timer.h"
#include"tutorialenemy.h"
#include"inputx.h"
#include"npcteacher.h"
#include"audio.h"
//ゲームUI
TextureLoad* texture_Dragon = new TextureLoad;
TextureLoad* texture_Clock = new TextureLoad;
TextureLoad* texture_GageBase = new TextureLoad;
TextureLoad* texture_TimelimitUI = new TextureLoad;
TextureLoad* texture_InfinitTimeUI = new TextureLoad;
TextureLoad* texture_ItemUI = new TextureLoad;
TextureLoad* texture_ItemRollUI = new TextureLoad;
TextureLoad* texture_WinUI = new TextureLoad;
TextureLoad* texture_WinUI2 = new TextureLoad;
TextureLoad* texture_ClearLogo = new TextureLoad;
TextureLoad* texture_PlayerName = new TextureLoad;
TextureLoad* texture_FindEye = new TextureLoad;
TextureLoad* texture_WeponLogo = new TextureLoad;
TextureLoad* texture_SharpnessRed = new TextureLoad;
TextureLoad* texture_SharpnessYellow = new TextureLoad;
TextureLoad* texture_SharpnessGreen = new TextureLoad;
TextureLoad* texture_SharpnessBlue = new TextureLoad;
TextureLoad* texture_SharpnessDown = new TextureLoad;
TextureLoad* texture_SharpnessUp = new TextureLoad;
TextureLoad* texture_DeadUI = new TextureLoad;
TextureLoad* texture_FaliedLogo = new TextureLoad;

//チュートリアル用操作表示
TextureLoad* texture_MoveText = new TextureLoad;
TextureLoad* texture_CameraMoveText = new TextureLoad;
TextureLoad* texture_RunText = new TextureLoad;
TextureLoad* texture_OnWeponText = new TextureLoad;
TextureLoad* texture_AttackText = new TextureLoad;
TextureLoad* texture_OffWeponText = new TextureLoad;
TextureLoad* texture_GuardText = new TextureLoad;
TextureLoad* texture_ItemDeploy = new TextureLoad;
TextureLoad* texture_ItemSelectText = new TextureLoad;
TextureLoad* texture_ItemUseText = new TextureLoad;
TextureLoad* texture_Arrow = new TextureLoad;

//チュートリアル用ストーリー表示
TextureLoad* texture_TStory1 = new TextureLoad;
TextureLoad* texture_TStory2 = new TextureLoad;
TextureLoad* texture_TStory3 = new TextureLoad;
TextureLoad* texture_TStory4 = new TextureLoad;
TextureLoad* texture_TStory5 = new TextureLoad;
TextureLoad* texture_TStory6 = new TextureLoad;
TextureLoad* texture_TStory7 = new TextureLoad;
TextureLoad* texture_TStory8 = new TextureLoad;
TextureLoad* texture_TStory9 = new TextureLoad;

bool GameTexture::m_ClearLogoFlag=false;
void GameTexture::Init()
{
	GameObject::Init();
	//HPバーの背景と時間表示
	texture_Dragon->Init("asset/texture/UI/dragonUI.png");
	texture_Dragon->SetTextureScale(180.0f, 180.0f);
	texture_Clock->Init("asset/texture/UI/clock.png");
	texture_Clock->SetTextureScale(150.0f, 150.0f);
	texture_GageBase->Init("asset/texture/UI/gagebase2.png");
	texture_GageBase->SetTextureScale(1600.0f, 50.0f);
	texture_TimelimitUI->Init("asset/texture/UI/timelimit.png");
	texture_TimelimitUI->SetTextureScale(300.0f, 80.0f);
	texture_InfinitTimeUI->Init("asset/texture/UI/TimeLimitInfinity.png");
	texture_InfinitTimeUI->SetTextureScale(150.0f, 150.0f);
	//アイテム欄の背景
	texture_ItemUI->Init("asset/texture/UI/ItemBG2.png");
	texture_ItemUI->SetTextureScale(150.0f, 150.0f);
	texture_ItemRollUI->Init("asset/texture/UI/ItemRoll.png");
	texture_ItemRollUI->SetTextureScale(300.0f, 100.0f);
	texture_WinUI->Init("asset/texture/UI/winlogo.png");
	texture_WinUI->SetTextureScale(500.0f, 100.0f);
	texture_WinUI2->Init("asset/texture/UI/winlogo2.png");
	texture_WinUI2->SetTextureScale(500.0f, 100.0f);
	texture_ClearLogo->Init("asset/texture/UI/clearlogo.png");
	texture_ClearLogo->SetTextureScale(SCREEN_WIDTH, SCREEN_HEIGHT);

	//プレイヤーの表示
	texture_PlayerName->Init("asset/texture/UI/nametag.png");
	texture_PlayerName->SetTextureScale(300.0f, 75.0f);
	texture_FindEye->Init("asset/texture/UI/findeye.png");
	texture_FindEye->SetTextureScale(50.0f, 50.0f);
	texture_WeponLogo->Init("asset/texture/UI/weponlogo.png");
	texture_WeponLogo->SetTextureScale(50.0f, 60.0f);

	//切れ味の処理
	texture_SharpnessRed->Init("asset/texture/UI/weponsharpness_red.png");
	texture_SharpnessRed->SetTextureScale(200.0f, 50.0f);
	texture_SharpnessYellow->Init("asset/texture/UI/weponsharpness_yellow.png");
	texture_SharpnessYellow->SetTextureScale(200.0f, 50.0f);
	texture_SharpnessGreen->Init("asset/texture/UI/weponsharpness_green.png");
	texture_SharpnessGreen->SetTextureScale(200.0f, 50.0f);
	texture_SharpnessBlue->Init("asset/texture/UI/weponsharpness_blue.png");
	texture_SharpnessBlue->SetTextureScale(200.0f, 50.0f);
	texture_SharpnessDown->Init("asset/texture/UI/DawnSharpness.png");
	texture_SharpnessDown->SetTextureScale(300.0f, 80.0f);
	texture_SharpnessUp->Init("asset/texture/UI/UpSharpness.png");
	texture_SharpnessUp->SetTextureScale(300.0f, 80.0f);
	texture_DeadUI->Init("asset/texture/UI/DeadAnnounce.png");
	texture_DeadUI->SetTextureScale(300.0f, 80.0f);
	texture_FaliedLogo->Init("asset/texture/UI/failedlogo.png");
	texture_FaliedLogo->SetTextureScale(SCREEN_WIDTH, SCREEN_HEIGHT);

	//チュートリアル操作表示
	texture_MoveText->Init("asset/texture/TutoriaruUI/movetutoriaru.png");
	texture_MoveText->SetTextureScale(400.0f, 70.0f);
	texture_CameraMoveText->Init("asset/texture/TutoriaruUI/CameraMoveTutoriaru.png");
	texture_CameraMoveText->SetTextureScale(400.0f, 70.0f);
	texture_RunText->Init("asset/texture/TutoriaruUI/RunTutoriaru.png");
	texture_RunText->SetTextureScale(430.0f, 70.0f);
	texture_OnWeponText->Init("asset/texture/TutoriaruUI/WeponTutoriaru2.png");
	texture_OnWeponText->SetTextureScale(400.0f, 70.0f);
	texture_AttackText->Init("asset/texture/TutoriaruUI/AttackTutoriaru.png");
	texture_AttackText->SetTextureScale(400.0f, 70.0f);
	texture_OffWeponText->Init("asset/texture/TutoriaruUI/WeponTutoriaru1.png");
	texture_OffWeponText->SetTextureScale(400.0f, 70.0f);
	texture_GuardText->Init("asset/texture/TutoriaruUI/GuardTutoriaru.png");
	texture_GuardText->SetTextureScale(400.0f, 70.0f);
	texture_ItemDeploy->Init("asset/texture/TutoriaruUI/ItemDeploymentTutoriaru.png");
	texture_ItemDeploy->SetTextureScale(400.0f, 70.0f);
	texture_ItemSelectText->Init("asset/texture/TutoriaruUI/ItemDeploymentTutoriaru.png");
	texture_ItemSelectText->SetTextureScale(400.0f, 70.0f);
	texture_ItemUseText->Init("asset/texture/TutoriaruUI/ItemUseTutoriaru.png");
	texture_ItemUseText->SetTextureScale(400.0f, 70.0f);
	texture_Arrow->Init("asset/texture/TutoriaruUI/arrow.png");
	texture_Arrow->SetTextureScale(50.0f, 25.0f);

	//チュートリアル用ストーリー表示
	texture_TStory1->Init("asset/texture/TutoriaruUI/story1.png");
	texture_TStory1->SetTextureScale(550.0f, 150.0f);
	texture_TStory2->Init("asset/texture/TutoriaruUI/story2.png");
	texture_TStory2->SetTextureScale(550.0f, 150.0f);
	texture_TStory3->Init("asset/texture/TutoriaruUI/story3.png");
	texture_TStory3->SetTextureScale(550.0f, 150.0f);
	texture_TStory4->Init("asset/texture/TutoriaruUI/story4.png");
	texture_TStory4->SetTextureScale(550.0f, 150.0f);
	texture_TStory5->Init("asset/texture/TutoriaruUI/story5.png");
	texture_TStory5->SetTextureScale(550.0f, 150.0f);
	texture_TStory6->Init("asset/texture/TutoriaruUI/story6.png");
	texture_TStory6->SetTextureScale(550.0f, 150.0f);
	texture_TStory7->Init("asset/texture/TutoriaruUI/story7.png");
	texture_TStory7->SetTextureScale(550.0f, 150.0f);
	texture_TStory8->Init("asset/texture/TutoriaruUI/story8.png");
	texture_TStory8->SetTextureScale(550.0f, 150.0f);
	texture_TStory9->Init("asset/texture/TutoriaruUI/story9.png");
	texture_TStory9->SetTextureScale(550.0f, 150.0f);

	

	m_Scene = Manager::GetScene();
	
	m_ClearLogoFlag = false;

	m_FrameWait = 0;
	m_ReturnCampCount=0;
	m_ReturnCampCount = 0;
	
	m_DecideSE = AddComponent<Audio>();
	m_DecideSE->Load("asset\\audio\\SE\\チュートリアル用.wav");

	m_FallSE = AddComponent<Audio>();
	m_FallSE->Load("asset\\audio\\SE\\怪獣の足音.wav");
}

void GameTexture::Uninit()
{
	GameObject::Uninit();
	texture_Dragon->SetDestroy();
	texture_Clock->SetDestroy();
	texture_TimelimitUI->SetDestroy();
	texture_InfinitTimeUI->SetDestroy();
	texture_GageBase->SetDestroy();
	texture_WinUI->SetDestroy();
	texture_WinUI2->SetDestroy();
	texture_ClearLogo->SetDestroy();
	texture_PlayerName->SetDestroy();
	texture_FindEye->SetDestroy();
	texture_WeponLogo->SetDestroy();
	texture_SharpnessRed->SetDestroy();
	texture_SharpnessYellow->SetDestroy();
	texture_SharpnessGreen->SetDestroy();
	texture_SharpnessBlue->SetDestroy();
	texture_SharpnessDown->SetDestroy();
	texture_SharpnessUp->SetDestroy();
	texture_DeadUI->SetDestroy();
	texture_FaliedLogo->SetDestroy();
	texture_MoveText->SetDestroy();
	texture_CameraMoveText->SetDestroy();
	texture_RunText->SetDestroy();
	texture_OnWeponText->SetDestroy();
	texture_AttackText->SetDestroy();
	texture_OffWeponText->SetDestroy();
	texture_GuardText->SetDestroy();
	texture_ItemDeploy->SetDestroy();
	texture_ItemSelectText->SetDestroy();
	texture_ItemUseText->SetDestroy();
	texture_TStory1->SetDestroy();
	texture_TStory2->SetDestroy();
	texture_TStory3->SetDestroy();
	texture_TStory4->SetDestroy();
	texture_TStory5->SetDestroy();
	texture_TStory6->SetDestroy();
	texture_TStory7->SetDestroy();
	texture_TStory8->SetDestroy();
	texture_TStory9->SetDestroy();
	texture_Arrow->SetDestroy();
}

void GameTexture::Update()
{
	GameObject::Update();
	switch (m_GameScene)
	{
	case TUTORIAL_SCENE:
		TutorialUpdate();
		break;
	case QUEST1_SCENE:
		QuestUpdate();
		
		break;
	default:
		break;
	}
}

void GameTexture::Draw()
{
	switch (m_GameScene)
	{
	case TUTORIAL_SCENE:
		TutorialDraw();
		break;
	case QUEST1_SCENE: 
		QuestDraw();
		
		break;
	default:
		break;
	}
	GameObject::Draw();
}

void GameTexture::TutorialUpdate()
{
	m_TutorialEnemy = m_Scene->GetGameObject<TutorialEnemy>();
	m_Sword = m_Scene->GetGameObject<Sword>();
	m_Player = m_Scene->GetGameObject<Player>();
	m_ItemManager = m_Scene->GetGameObject<ItemManager>();
	m_NPC = m_Scene->GetGameObject<NpcTeacher>();
	//クリア時
	if (m_TutorialEnemy != nullptr)
	{
		if (m_TutorialEnemy->GetDead())
		{
			m_WinLogoPosY = texture_WinUI->UiMove(160, texture_WinUI, 150);
			texture_WinUI->SetEnable(true);
			m_FrameWait++;
			if (m_FrameWait > 130)
			{
				texture_WinUI->SetEnable(false);
			}
			if (m_FrameWait > 220)
			{
				m_WinLogo2PosY = texture_WinUI2->UiMove(160, texture_WinUI2, 150);
				m_ClearLogoCountFlag = true;
				texture_WinUI2->SetEnable(true);
			}
			if (m_FrameWait > 350)
			{
				texture_WinUI2->SetEnable(false);
			}
		}
	}

	switch (m_TutorialStory)
	{
	case TUTORIAL_STORY1:		//移動チュートリアル
		if ((InputX::IsButtonTriggered(0, XINPUT_GAMEPAD_B)))
		{
			m_DecideSE->Volume(Scene::m_SEVolume * 0.5f); 
			m_DecideSE->PlaySE();
			m_TutorialStory = static_cast<TUTORIAL_STORY>(static_cast<int>(m_TutorialStory) + 1);
		}
		break;
	case TUTORIAL_STORY2:	//移動チュートリアル
		if ((InputX::IsButtonTriggered(0, XINPUT_GAMEPAD_B)))
		{
			m_TutorialStory = static_cast<TUTORIAL_STORY>(static_cast<int>(m_TutorialStory) + 1);
			m_DecideSE->Volume(Scene::m_SEVolume * 0.5f);
			m_DecideSE->PlaySE();
		}
		break;
	case TUTORIAL_STORY3:	//視点移動チュートリアル
		if ((InputX::GetThumbRightY(0) >= 0.2 || InputX::GetThumbRightY(0) <= -0.2 || InputX::GetThumbRightX(0) <= -0.2 || InputX::GetThumbRightX(0) >= 0.2) && m_NPC->GetHit())
		{
			m_FrameWait++;
			if (m_FrameWait > 60)
			{
				m_FrameWait = 0;
				m_DecideSE->Volume(Scene::m_SEVolume * 0.5f);
				m_DecideSE->PlaySE();
				m_TutorialNumber = static_cast<TUTORIAL_NUMBER>(static_cast<int>(m_TutorialNumber) + 1);
				m_TutorialStory = static_cast<TUTORIAL_STORY>(static_cast<int>(m_TutorialStory) + 1);
			}	
		}
		break;
	case TUTORIAL_STORY4: //ストーリー進行
		if ((InputX::IsButtonTriggered(0, XINPUT_GAMEPAD_B)))
		{
			m_TutorialStory = static_cast<TUTORIAL_STORY>(static_cast<int>(m_TutorialStory) + 1);
			m_DecideSE->Volume(Scene::m_SEVolume * 0.5f);
			m_DecideSE->PlaySE();
			
		}
		break;
	case TUTORIAL_STORY5: //アイテムスロット展開
		if (InputX::IsButtonPressed(0, XINPUT_GAMEPAD_LEFT_SHOULDER))
		{
			m_FrameWait++;
			if (m_FrameWait > 30)
			{
				m_FrameWait = 0;
				m_DecideSE->Volume(Scene::m_SEVolume * 0.5f);
				m_DecideSE->PlaySE();
				m_TutorialStory = static_cast<TUTORIAL_STORY>(static_cast<int>(m_TutorialStory) + 1);
				m_TutorialNumber = TUTORIAL_ITEM;
			}
		}
		break;
	case TUTORIAL_STORY6:  //アイテム選択
		if (InputX::IsButtonTriggered(0, XINPUT_GAMEPAD_X) || InputX::IsButtonTriggered(0, XINPUT_GAMEPAD_B))
		{
			m_ItemSelectCount++;
		}
		if (m_ItemSelectCount >= 1)
		{
			if (InputX::IsButtonTriggered(0, XINPUT_GAMEPAD_B) && !InputX::IsButtonPressed(0, XINPUT_GAMEPAD_LEFT_SHOULDER))
			{
				m_EnemyCallCountFlag = true;
				m_DecideSE->Volume(Scene::m_SEVolume * 0.5f);
				m_DecideSE->PlaySE();
				
			}
			if (m_EnemyCallCountFlag)//敵を呼び出す
			{
				m_FrameWait++;
				if (m_FrameWait > 90 && !m_EnemyCallFlag)
				{
					m_EnemyCallFlag = true;
					m_TutorialEnemy = m_Scene->AddGameObject<TutorialEnemy>();
					m_TutorialEnemy->SetPosition(D3DXVECTOR3(0.0f, 20.0f, 25.0f));
				}
				if (140 <m_FrameWait  && m_FrameWait < 150)
				{
					Camera* m_Camera = m_Scene->GetGameObject<Camera>();
					if (!m_FallSEFlag)
					{
						m_FallSE->Volume(Scene::m_SEVolume*0.5f);
						m_FallSE->PlaySE();
						m_FallSEFlag = true;
					}
					
					m_Camera->Shake(0.3f);
					
				}
				if(150 <m_FrameWait)
				{
					m_FrameWait = 0;
					m_DecideSE->Volume(Scene::m_SEVolume * 0.5f);
					m_DecideSE->PlaySE();
					m_TutorialStory = static_cast<TUTORIAL_STORY>(static_cast<int>(m_TutorialStory) + 1);
					m_TutorialNumber = TUTORIAL_ONWEPON;
				}
			}
		}
		break;
	case TUTORIAL_STORY7: //戦闘開始時のセリフ
		m_FrameWait++;
		if (60 < m_FrameWait)
		{
			m_EnemyHowlFlag = true;
		}
		if (m_TutorialEnemy->GetHP() < 40)
		{
			m_FrameWait = 0;
			m_TutorialStory = static_cast<TUTORIAL_STORY>(static_cast<int>(m_TutorialStory) + 1);
			m_DecideSE->Volume(Scene::m_SEVolume * 0.5f);
			m_DecideSE->PlaySE();
		}
		break;
	case TUTORIAL_STORY8: //敵を倒した時のセリフ
		m_FrameWait++;
		if (m_TutorialEnemy->GetDead())
		{
			m_FrameWait = 0;
			m_TutorialStory = static_cast<TUTORIAL_STORY>(static_cast<int>(m_TutorialStory) + 1);
			m_DecideSE->Volume(Scene::m_SEVolume * 0.5f);
			m_DecideSE->PlaySE();
		}
		break;
	case TUTORIAL_STORY9:
		m_FrameWait++;
		break;
	default:
		break;
	}

	

	switch (m_TutorialNumber)
	{
	case TUTORIAL_MOVE: //歩行チュートリアル
		if ((InputX::GetThumbLeftY(0) >= 0.2 || InputX::GetThumbLeftY(0) <= -0.2 || InputX::GetThumbLeftX(0) <= -0.2 || InputX::GetThumbLeftX(0) >= 0.2))
		{
			m_FrameWait++;
			if (m_FrameWait > 30)
			{
				m_FrameWait = 0;
				m_TutorialNumber = static_cast<TUTORIAL_NUMBER>(static_cast<int>(m_TutorialNumber) + 1);
			}
		}
		break;
	case TUTORIAL_RUN: //移動チュートリアル
		if ((InputX::GetThumbLeftY(0) >= 0.2 || InputX::GetThumbLeftY(0) <= -0.2 || InputX::GetThumbLeftX(0) <= -0.2 || InputX::GetThumbLeftX(0) >= 0.2) && InputX::IsButtonPressed(0, XINPUT_GAMEPAD_RIGHT_SHOULDER))
		{
			if (m_NPC->GetHit())
			{
				m_TutorialNumber = static_cast<TUTORIAL_NUMBER>(static_cast<int>(m_TutorialNumber) + 1);
			}
		}
		break;
	case TUTORIAL_MOVECAMERA: //視点移動チュートリアル
		break;
	case TUTORIAL_ITEM: //アイテム系チュートリアル
		break;
	case TUTORIAL_ONWEPON:	//戦闘チュートリアル
		if (InputX::IsButtonTriggered(0, XINPUT_GAMEPAD_Y))
		{
			m_TutorialNumber = static_cast<TUTORIAL_NUMBER>(static_cast<int>(m_TutorialNumber) + 1);
		}
		break;
	case TUTORIAL_ATTACK:	//攻撃チュートリアル
		if (m_TutorialEnemy->GetDead())
		{
			m_TutorialNumber = static_cast<TUTORIAL_NUMBER>(static_cast<int>(m_TutorialNumber) + 1);
		}
		break;
	default:
		break;
	}

	

	if (m_ClearLogoCountFlag)
	{
		m_ReturnCampCount++;
		if (m_ReturnCampCount > 700)
		{
			m_ChangeSceneFlag = true;
		}
	}

	//戦闘時のプレイヤーアイコンの処理
	m_ChangeIconCount++;

	//切れ味ダウン
	if (m_Sword->GetSharpnessUIFlag())
	{
		m_SharpnessDownY = texture_SharpnessDown->UiMove(160, texture_SharpnessDown, 30);
		texture_SharpnessDown->SetEnable(true);
	}


	//切れ味アップ
	if (m_Player->GetSharpnessUpFlag())
	{
		m_SharpnessUpY = texture_SharpnessUp->UiMove(160, texture_SharpnessUp, 30);
		texture_SharpnessUp->SetEnable(true);
	}

	//力尽きた時
	if (m_Player->GetPlayerDeadUIFlag())
	{
		m_DeadUIY = texture_DeadUI->UiMove(160, texture_DeadUI, 100);
		texture_DeadUI->SetEnable(true);
	}

	//クエスト失敗時のテクスチャ
	if (m_FaliedLogoCountFlag)
	{
		m_ReturnCampCount++;
		if (m_ReturnCampCount > 80)
		{
			m_ChangeSceneFlag = true;
		}
	}

	

}

void GameTexture::TutorialDraw()
{
	m_TutorialEnemy = m_Scene->GetGameObject<TutorialEnemy>();
	m_Sword = m_Scene->GetGameObject<Sword>();
	m_Player = m_Scene->GetGameObject<Player>();
	m_ItemManager = m_Scene->GetGameObject<ItemManager>();

	if (m_ReturnCampCount > 600) //クエストクリアのロゴがでている時
	{
		m_ClearLogoFlag = true;
		texture_ClearLogo->Draw(0.0f, 0.0f);
		
	}
	else
	{
		texture_Dragon->Draw(0.0f, 0.0f);
		texture_Clock->Draw(5.0f, 8.0f);
		texture_InfinitTimeUI->Draw(5.0f, 8.0f);
		texture_PlayerName->Draw(10.0f, 90.0f);
		texture_GageBase->Draw(80.0f, 5.0f);
		

		switch (m_TutorialStory)
		{
		case TUTORIAL_STORY1:
			texture_TStory1->Draw(350.0f, 400.0f);
			break;
		case TUTORIAL_STORY2:
			texture_TStory2->Draw(350.0f, 400.0f);
			break;
		case TUTORIAL_STORY3:
			if (m_NPC->GetHit())
			{
				texture_TStory3->Draw(350.0f, 400.0f);
			}
			break;
		case TUTORIAL_STORY4:
			texture_TStory4->Draw(350.0f, 400.0f);
			break;
		case TUTORIAL_STORY5:
			texture_TStory5->Draw(350.0f, 400.0f);
			break;
		case TUTORIAL_STORY6:
			if (!m_EnemyCallCountFlag)
			{
				texture_TStory6->Draw(350.0f, 400.0f);
			}
			break;
		case TUTORIAL_STORY7:
			if (m_FrameWait < 90)
			{
				texture_TStory7->Draw(350.0f, 400.0f);
			}
			
			break;
		case TUTORIAL_STORY8:
			if (m_FrameWait < 90)
			{
				texture_TStory8->Draw(350.0f, 400.0f);
			}
			break;
		case TUTORIAL_STORY9:
			if (m_FrameWait < 1000)
			{
				texture_TStory9->Draw(350.0f, 400.0f);
			}
			break;
		default:
			break;
		}


		switch (m_TutorialNumber)
		{
		case TUTORIAL_MOVE:
			texture_MoveText->Draw(400.0f, 130.0f);
			break;
		case TUTORIAL_RUN:
			texture_RunText->Draw(400.0f, 130.0f);
			texture_Arrow->Draw(490.0f, 110.0f);
			texture_MoveText->Draw(400.0f, 70.0f);
			break;
		case TUTORIAL_MOVECAMERA:
			texture_CameraMoveText->Draw(400.0f, 130.0f);
			break;
		case TUTORIAL_ITEM:
			texture_ItemSelectText->Draw(400.0f, 130.0f);
			texture_ItemUseText->Draw(400.0f, 170.0f);
			break;
		case TUTORIAL_ONWEPON:
			texture_OnWeponText->Draw(400.0f, 130.0f);
			break;
		case TUTORIAL_ATTACK:
			texture_OnWeponText->Draw(400.0f, 70.0f);
			texture_Arrow->Draw(540.0f, 110.0f);
			texture_Arrow->Draw(390.0f, 110.0f);
			texture_AttackText->Draw(300.0f, 130.0f);
			texture_GuardText->Draw(500.0f, 130.0f);
			texture_Arrow->Draw(470.0f, 170.0f);
			texture_OffWeponText->Draw(400.0f, 200.0f);
			break;
		default:
			break;
		}
	

		if (m_ItemManager->GetShowFlag())
		{
			texture_ItemRollUI->Draw(760.0f, 410.0f);
		}

		texture_ItemUI->Draw(800.0f, 405.0f);
		if (m_Sword != nullptr)
		{
			switch (m_Sword->GetWeponSharpnes())
			{
			case SHARPNES_RED:
				texture_SharpnessRed->Draw(100.0f, 30.0f);
				break;
			case SHARPNES_YELLOW:
				texture_SharpnessYellow->Draw(100.0f, 30.0f);
				break;
			case SHARPNES_GREEN:
				texture_SharpnessGreen->Draw(100.0f, 30.0f);
				break;
			case SHARPNES_BLUE:
				texture_SharpnessBlue->Draw(100.0f, 30.0f);
				break;
			default:
				break;
			}

			if (m_Sword->GetSharpnessUIFlag())
			{
				texture_SharpnessDown->Draw(400.0f, m_SharpnessDownY);
			}
		}
		if (m_Player != nullptr)
		{
			if (m_Player->GetSharpnessUpFlag())
			{
				texture_SharpnessUp->Draw(400.0f, m_SharpnessUpY);
			}
			if (m_Player->GetPlayerDeadUIFlag())
			{
				texture_DeadUI->Draw(400.0f, m_DeadUIY);
			}

			if (m_Player->GetFaliedFlag())
			{
				m_FaliedLogoCountFlag = true;
				texture_FaliedLogo->Draw(0.0f, 0.0f);
			}
		}


	}

	if (m_TutorialEnemy != nullptr)
	{

		if (m_TutorialEnemy->GetEnemyHowlFinish() && !m_TutorialEnemy->GetDead() && !m_Player->GetPlayerDead())
		{
			if (m_ChangeIconCount <= 60)
			{

				texture_WeponLogo->Draw(8.5f, 90.0f);
			}
			else if (m_ChangeIconCount <= 120)
			{

				texture_FindEye->Draw(10.0f, 92.0f);
			}
			else
			{
				m_ChangeIconCount = 0;
			}
		}
		else 
		{
			texture_WeponLogo->Draw(8.5f, 90.0f);
		}



		if (m_TutorialEnemy->GetDead())
		{

			texture_WinUI->Draw(350.0f, m_WinLogoPosY);

			if (m_FrameWait > 220)
			{

				texture_WinUI2->Draw(350.0f, m_WinLogo2PosY);
			}
		}
	}
	else 
	{
		texture_WeponLogo->Draw(8.5f, 90.0f);
	}
}

void GameTexture::QuestUpdate()
{
	m_Enemy = m_Scene->GetGameObject<Enemy>();
	m_Sword = m_Scene->GetGameObject<Sword>();
	m_Player = m_Scene->GetGameObject<Player>();

	if (!m_GameStasrtFlag)
	{
		m_TimeLimitPosY = texture_TimelimitUI->UiMove(160, texture_TimelimitUI, 70);
		texture_TimelimitUI->SetEnable(true);
		m_LimitUICount++;
		if (m_LimitUICount >= 130)
		{
			m_GameStasrtFlag = true;
			m_LimitUICount = 0;
		}
	}



	//クリア時
	if (m_Enemy != nullptr)
	{
		if (m_Enemy->GetDead())
		{
			m_WinLogoPosY = texture_WinUI->UiMove(160, texture_WinUI, 150);
			texture_WinUI->SetEnable(true);
			m_FrameWait++;
			if (m_FrameWait > 130)
			{
				texture_WinUI->SetEnable(false);
			}
			if (m_FrameWait > 220)
			{
				m_WinLogo2PosY = texture_WinUI2->UiMove(160, texture_WinUI2, 150);
				m_ClearLogoCountFlag = true;
				texture_WinUI2->SetEnable(true);
			}
			if (m_FrameWait > 350)
			{
				texture_WinUI2->SetEnable(false);
			}
		}

	}
	if (m_ClearLogoCountFlag)
	{
		m_ReturnCampCount++;
		if (m_ReturnCampCount > 700)
		{
			m_ChangeSceneFlag = true;
		}
	}

	//戦闘時のプレイヤーアイコンの処理
	m_ChangeIconCount++;

	//切れ味ダウン
	if (m_Sword->GetSharpnessUIFlag())
	{
		m_SharpnessDownY = texture_SharpnessDown->UiMove(160, texture_SharpnessDown, 30);
		texture_SharpnessDown->SetEnable(true);
	}


	//切れ味アップ
	if (m_Player->GetSharpnessUpFlag())
	{
		m_SharpnessUpY = texture_SharpnessUp->UiMove(160, texture_SharpnessUp, 30);
		texture_SharpnessUp->SetEnable(true);
	}

	//力尽きた時
	if (m_Player->GetPlayerDeadUIFlag())
	{
		m_DeadUIY = texture_DeadUI->UiMove(160, texture_DeadUI, 100);
		texture_DeadUI->SetEnable(true);
	}

	if (m_FaliedLogoCountFlag)
	{
		m_ReturnCampCount++;
		if (m_ReturnCampCount > 80)
		{
			m_ChangeSceneFlag = true;
		}
	}
}

void GameTexture::QuestDraw()
{
	m_Enemy = m_Scene->GetGameObject<Enemy>();
	m_Sword = m_Scene->GetGameObject<Sword>();
	m_Player = m_Scene->GetGameObject<Player>();
	m_ItemManager = m_Scene->GetGameObject<ItemManager>();
	//ゲームUI

	if (m_ReturnCampCount > 600) //クエストクリアのロゴがでている時
	{
		m_ClearLogoFlag = true;

		texture_ClearLogo->Draw(0.0f, 0.0f);
		m_TimeLimitPosY = -50.0f;
	}
	else
	{
		texture_Dragon->Draw(0.0f, 0.0f);
		texture_Clock->Draw(5.0f, 8.0f);
		texture_PlayerName->Draw(10.0f, 90.0f);
		texture_GageBase->Draw(80.0f, 5.0f);
		texture_TimelimitUI->Draw(400.0f, m_TimeLimitPosY);

		if (m_ItemManager->GetShowFlag())
		{
			texture_ItemRollUI->Draw(760.0f, 410.0f);
		}

		texture_ItemUI->Draw(800.0f, 405.0f);
		//武器の切れ味UI表示
		if (m_Sword != nullptr)
		{
			switch (m_Sword->GetWeponSharpnes())
			{
			case SHARPNES_RED:
				texture_SharpnessRed->Draw(100.0f, 30.0f);
				break;
			case SHARPNES_YELLOW:
				texture_SharpnessYellow->Draw(100.0f, 30.0f);
				break;
			case SHARPNES_GREEN:
				texture_SharpnessGreen->Draw(100.0f, 30.0f);
				break;
			case SHARPNES_BLUE:
				texture_SharpnessBlue->Draw(100.0f, 30.0f);
				break;
			default:
				break;
			}
			//切れ味ダウンのUI表示
			if (m_Sword->GetSharpnessUIFlag())
			{
				texture_SharpnessDown->Draw(400.0f, m_SharpnessDownY);
			}
		}

		if (m_Player != nullptr)
		{
			//武器砥ぎ時のUI
			if (m_Player->GetSharpnessUpFlag())
			{
				texture_SharpnessUp->Draw(400.0f, m_SharpnessUpY);
			}
			//死亡時
			if (m_Player->GetPlayerDeadUIFlag())
			{
				texture_DeadUI->Draw(400.0f, m_DeadUIY);
			}

			//クエスト失敗時
			if (m_Player->GetFaliedFlag())
			{
				m_FaliedLogoCountFlag = true;
				texture_FaliedLogo->Draw(0.0f, 0.0f);
			}
		}


	}

	if (m_Enemy != nullptr)
	{

		if (m_Enemy->GetEnemyHowlFinish() && !m_Enemy->GetDead() && !m_Player->GetPlayerDead())
		{
			if (m_ChangeIconCount <= 60)
			{

				texture_WeponLogo->Draw(8.5f, 90.0f);
			}
			else if (m_ChangeIconCount <= 120)
			{

				texture_FindEye->Draw(10.0f, 92.0f);
			}
			else
			{
				m_ChangeIconCount = 0;
			}
		}
		else if (!GetGameClear())
		{
			texture_WeponLogo->Draw(8.5f, 90.0f);
		}


		//クリア時のロゴ表示
		if (m_Enemy->GetDead())
		{
			texture_WinUI->Draw(350.0f, m_WinLogoPosY);

			if (m_FrameWait > 220)
			{

				texture_WinUI2->Draw(350.0f, m_WinLogo2PosY);
			}
		}
	}
}

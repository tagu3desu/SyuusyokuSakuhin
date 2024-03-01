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
#include"wepon_sword.h"
#include"player.h"
#include"camera.h"
#include"ItemManger.h"
#include"timer.h"
#include"tutorialenemy.h"
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

	
	m_Scene = Manager::GetScene();
	

	m_FrameWait = 0;
	m_ReturnCampCount=0;
	m_ReturnCampCount = 0;
	
}

void GameTexture::Uninit()
{
	GameObject::Uninit();
	texture_Dragon->SetDestroy();
	texture_Clock->SetDestroy();
	texture_TimelimitUI->SetDestroy();
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
		texture_PlayerName->Draw(10.0f, 90.0f);
		texture_GageBase->Draw(80.0f, 5.0f);
		

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
		else if (!GetGameClear())
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

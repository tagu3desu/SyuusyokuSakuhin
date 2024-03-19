#include"main.h"
#include"renderer.h"
#include"scene.h"
#include"manager.h"
#include"titletexturemanager.h"
#include"textureload.h"
#include"title.h"
#include"input.h"
#include"audio.h"
#include"inputx.h"
TextureLoad* texture_PushSpace = new TextureLoad;
TextureLoad* texture_GameStart = new TextureLoad;
TextureLoad* texture_OPTION = new TextureLoad;
TextureLoad* texture_TitleLogo = new TextureLoad;
TextureLoad* texture_TitleSelect = new TextureLoad;
TextureLoad* texture_OPTIONUI = new TextureLoad;
TextureLoad* texture_BuckButton = new TextureLoad;
TextureLoad* texture_BGMThumb = new TextureLoad;
TextureLoad* texture_SEThumb = new TextureLoad;
TextureLoad* texture_SelectArrow = new TextureLoad;
TextureLoad* texture_TutorialButton = new TextureLoad;
TextureLoad* texture_TutorialButtonBG = new TextureLoad;
TextureLoad* texture_QuestButton = new TextureLoad;
TextureLoad* texture_QuestButtonBG = new TextureLoad;


float Scene::m_BGMVolume=0.0f;
float Scene::m_SEVolume=0.0f;

void TitleTexture::Init()
{
	texture_PushSpace->Init("asset/texture/UI/PushSpacetoB.png");
	texture_PushSpace->SetTextureScale(950.0f, 120.0f);

	texture_GameStart->Init("asset/texture/UI/questselectbutton.png");
	texture_GameStart->SetTextureScale(900.0f, 150.0f);

	texture_OPTION->Init("asset/texture/UI/option.png");
	texture_OPTION->SetTextureScale(900.0f, 150.0f);

	texture_TitleLogo->Init("asset/texture/UI/titlelogo.png");
	texture_TitleLogo->SetTextureScale(600.0f, 600.0f);

	texture_TitleSelect->Init("asset/texture/UI/menuselect.png");
	texture_TitleSelect->SetTextureScale(800.0f, 115.0f);

	texture_OPTIONUI->Init("asset/texture/UI/OPTIONUI.png");
	texture_OPTIONUI->SetTextureScale(600.0f, 600.0f);

	texture_BuckButton->Init("asset/texture/UI/BackButton2.png"); 
	texture_BuckButton->SetTextureScale(120.0f, 50.0f);

	texture_BGMThumb->Init("asset/texture/UI/OptionThumb.png");
	texture_BGMThumb->SetTextureScale(30.0f, 30.0f);

	texture_SEThumb->Init("asset/texture/UI/OptionThumb.png");
	texture_SEThumb->SetTextureScale(30.0f, 30.0f);

	texture_SelectArrow->Init("asset/texture/UI/SelectArrow.png");
	texture_SelectArrow->SetTextureScale(30.0f, 30.0f);

	texture_TutorialButton->Init("asset/texture/UI/TutorialButton.png");
	texture_TutorialButton->SetTextureScale(950.0f, 125.0f);
	texture_TutorialButtonBG->Init("asset/texture/UI/QuestBG2.png");
	texture_TutorialButtonBG->SetTextureScale(900.0f, 150.0f);
	texture_QuestButton->Init("asset/texture/UI/QuestButton.png");
	texture_QuestButton->SetTextureScale(950.0f, 125.0f);
	texture_QuestButtonBG->Init("asset/texture/UI/QuestBG2.png");
	texture_QuestButtonBG->SetTextureScale(900.0f, 150.0f);

	scene = Manager::GetScene();
	

	m_MenuSelectPosition = D3DXVECTOR2(50.0f, 312.0f);
	//145～325
	m_BGMThumbPosition = D3DXVECTOR2(157.0f, 154.0f);
	m_SEThumbPosition = D3DXVECTOR2(157.0f, 273.0f);

	m_DecisiveSE = AddComponent<Audio>();
	m_DecisiveSE->Load("asset\\audio\\SE\\決定音.wav");

	m_SelectUIPosY = 145.0f;


	m_BGMFlag = false;
	m_SEFlag = true;
	GameObject::Init();
}

void TitleTexture::Uninit()
{
	texture_PushSpace->SetDestroy();
	texture_GameStart->SetDestroy();
	texture_OPTION->SetDestroy();
	texture_TitleLogo->SetDestroy();
	texture_OPTIONUI->SetDestroy();
	texture_BuckButton->SetDestroy();
	texture_BGMThumb->SetDestroy();
	texture_SEThumb->SetDestroy();
	texture_SelectArrow->SetDestroy();
	texture_TutorialButton->SetDestroy();
	texture_TutorialButtonBG->SetDestroy();
	texture_QuestButton->SetDestroy();
	texture_QuestButtonBG->SetDestroy();

	GameObject::Uninit();
}

void TitleTexture::Update()
{
	GameObject::Update();
	m_MouseposX = GetMouseCursorPosXinWnd();
	m_MouseposY = GetMouseCursorPosYinWnd();

	

	if (Title::GetQuestSelect())
	{
		if (m_TutorialFlag)
		{
			if (InputX::IsButtonTriggered(0, XINPUT_GAMEPAD_DPAD_DOWN) || Input::GetKeyTrigger(VK_DOWN))
			{
				m_QuestFlag = true;
				m_TutorialFlag = false;
				m_DecisiveSE->Volume(GetSEVolume());
				m_DecisiveSE->PlaySE();
			}
			if (InputX::IsButtonTriggered(0, XINPUT_GAMEPAD_B) || Input::GetKeyTrigger(VK_SPACE))
			{
				m_DecidedTutorial = true;
			}

			texture_TutorialButtonBG->TextureRGBFlashing(70, 0.01f);
		}
		else
		{
			texture_TutorialButtonBG->SetColor(D3DXCOLOR(0.08f, 0.08f, 0.08f, 1.0f));
		}


		if (m_QuestFlag)
		{
			if (InputX::IsButtonTriggered(0, XINPUT_GAMEPAD_DPAD_UP) || Input::GetKeyTrigger(VK_UP))
			{
				m_TutorialFlag = true;
				m_QuestFlag = false;
				m_DecisiveSE->Volume(GetSEVolume());
				m_DecisiveSE->PlaySE();
			}
			if (InputX::IsButtonTriggered(0, XINPUT_GAMEPAD_B) || Input::GetKeyTrigger(VK_SPACE))
			{
				m_DecidedQuest = true;
			}
			texture_QuestButtonBG->TextureRGBFlashing(70, 0.01f);
		}
		else
		{
			texture_QuestButtonBG->SetColor(D3DXCOLOR(0.08f, 0.08f, 0.08f, 1.0f));
		}
	}


	if (Title::GetMenuControl()  && !Title::GetQuestSelect())
	{
		if ((Input::GetKeyTrigger(VK_UP) || InputX::IsButtonTriggered(0,XINPUT_GAMEPAD_DPAD_UP)  ||   (130< m_MouseposX &&  m_MouseposX < 860 &&  620 < m_MouseposY && m_MouseposY <720))  && !m_OptionFlag )
		{		
			m_MenuSelectPosition =(D3DXVECTOR2(50.0f, 312.0f));
			m_GameButtonOverlap = true;
			m_OptionButtonOverlap = false;
			m_DecisiveSE->Volume(GetSEVolume());
			m_DecisiveSE->PlaySE();
		}
		else if (Input::GetKeyTrigger(VK_DOWN) || InputX::IsButtonTriggered(0, XINPUT_GAMEPAD_DPAD_DOWN)  ||  ((130 < m_MouseposX && m_MouseposX < 860 && 760 < m_MouseposY && m_MouseposY < 860)))
		{
			m_MenuSelectPosition = (D3DXVECTOR2(50.0f, 382.0f));	
			m_GameButtonOverlap = false;
			m_OptionButtonOverlap = true;
			m_DecisiveSE->Volume(GetSEVolume());
			m_DecisiveSE->PlaySE();
		}
		

		if (m_OptionButtonOverlap)
		{
			if (Input::GetKeyTrigger(VK_SPACE) || Input::GetKeyPress(VK_LBUTTON) || InputX::IsButtonTriggered(0,XINPUT_GAMEPAD_B))
			{
				m_OptionFlag = true;
				m_DecisiveSE->Volume(GetSEVolume());
				m_DecisiveSE->PlaySE();
			}
		}
	
		//オプション画面の処理
		if (m_OptionFlag && !Title::GetQuestSelect())
		{
			
			if ((215 < m_MouseposX && m_MouseposX < 315 && 630 < m_MouseposY && m_MouseposY < 670))
			{
				texture_BuckButton->SetColor(D3DXCOLOR(0.9f, 0.5f, 0.1f,1.0f));
				
				//戻る処理
				if (Input::GetKeyTrigger(VK_LBUTTON))
				{
					m_DecisiveSE->Volume(GetSEVolume());
					m_DecisiveSE->PlaySE();
					m_OptionFlag = false;
				}
			}
			else if (InputX::IsButtonTriggered(0, XINPUT_GAMEPAD_A) || Input::GetKeyTrigger('B'))
			{
				m_DecisiveSE->Volume(GetSEVolume());
				m_DecisiveSE->PlaySE();
				m_OptionFlag = false;
			}
			else
			{
				texture_BuckButton->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
			
			//コントローラーの時の処理
			if (m_SelectUIPosY==145)
			{
				if (InputX::IsButtonPressed(0, XINPUT_GAMEPAD_DPAD_LEFT))
				{
					m_DecisiveSE->Volume(GetSEVolume());
					m_DecisiveSE->PlaySE();
					m_BGMThumbPosition.x -= 1.0f;
					texture_BGMThumb->SetColor(D3DXCOLOR(0.9f, 0.6f, 0.2f, 1.0f));
				}
				else if (InputX::IsButtonPressed(0, XINPUT_GAMEPAD_DPAD_RIGHT))
				{
					m_DecisiveSE->Volume(GetSEVolume());
					m_DecisiveSE->PlaySE();
					m_BGMThumbPosition.x += 1.0f;
					texture_BGMThumb->SetColor(D3DXCOLOR(0.9f, 0.6f, 0.2f, 1.0f));
				}
				else
				{
					texture_BGMThumb->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				}
				m_BGM_Volume = ((m_BGMThumbPosition.x - MAX_ThubPosition) / (MIN_ThubPosition - MAX_ThubPosition) * 100);
				if (InputX::IsButtonTriggered(0, XINPUT_GAMEPAD_DPAD_DOWN) || Input::GetKeyTrigger(VK_DOWN))
				{
					m_SelectUIPosY = 260.0f;
					m_BGMFlag = true;
					m_SEFlag = false;
					m_DecisiveSE->Volume(GetSEVolume());
					m_DecisiveSE->PlaySE();
				}
				
				
			}
			if (m_SelectUIPosY == 260)
			{
				if (InputX::IsButtonPressed(0, XINPUT_GAMEPAD_DPAD_LEFT))
				{
					m_DecisiveSE->Volume(GetSEVolume());
					m_DecisiveSE->PlaySE();
					m_SEThumbPosition.x -= 1.0f;
					texture_SEThumb->SetColor(D3DXCOLOR(0.9f, 0.6f, 0.2f, 1.0f));
				}
				else if (InputX::IsButtonPressed(0, XINPUT_GAMEPAD_DPAD_RIGHT))
				{
					m_DecisiveSE->Volume(GetSEVolume());
					m_DecisiveSE->PlaySE();
					m_SEThumbPosition.x += 1.0f;
					texture_SEThumb->SetColor(D3DXCOLOR(0.9f, 0.6f, 0.2f, 1.0f));
				}
				else
				{
					texture_SEThumb->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				}
				m_SE_Volume = ((m_SEThumbPosition.x - MAX_ThubPosition) / (MIN_ThubPosition - MAX_ThubPosition) * 100);
				if (InputX::IsButtonTriggered(0, XINPUT_GAMEPAD_DPAD_UP) || Input::GetKeyTrigger(VK_UP))
				{
					m_SelectUIPosY = 145.0f;
					m_BGMFlag = false;
					m_SEFlag = true;
					m_DecisiveSE->Volume(GetSEVolume());
					m_DecisiveSE->PlaySE();
				}	

				if (InputX::IsButtonTriggered(0, XINPUT_GAMEPAD_DPAD_DOWN) || Input::GetKeyTrigger(VK_DOWN) )
				{
					m_BackButton = true;
					m_BGMFlag = false;
					m_SEFlag = false;
					m_DecisiveSE->Volume(GetSEVolume());
					m_DecisiveSE->PlaySE();
				}
			}

			


			//マウスでの処理
			if (300 < m_MouseposY && m_MouseposY < 325)
			{
				m_SelectUIPosY = 145.0f;
				if ((MAX_ThubPosition-1 < m_BGMThumbPosition.x && m_BGMThumbPosition.x < MIN_ThubPosition+1 && Input::GetKeyPress(VK_LBUTTON)))
				{
					texture_BGMThumb->SetColor(D3DXCOLOR(0.9f, 0.6f, 0.2f, 1.0f));
					m_BGMThumbPosition.x = m_MouseposX * 0.47;
					m_BGM_Volume = ((m_BGMThumbPosition.x - MAX_ThubPosition) / (MIN_ThubPosition - MAX_ThubPosition) * 100);
				}
				else
				{
					texture_BGMThumb->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				}
			}		
			if (535 < m_MouseposY && m_MouseposY < 560 )
			{
				m_SelectUIPosY = 260.0f;
				if ((MAX_ThubPosition-1 < m_SEThumbPosition.x && m_SEThumbPosition.x < MIN_ThubPosition+1 && Input::GetKeyPress(VK_LBUTTON)))
				{
					texture_SEThumb->SetColor(D3DXCOLOR(0.9f, 0.6f, 0.2f, 1.0f));
					m_SEThumbPosition.x = m_MouseposX * 0.47;
					m_SE_Volume = ((m_SEThumbPosition.x - MAX_ThubPosition) / (MIN_ThubPosition - MAX_ThubPosition) * 100);
				}
				else
				{
					texture_SEThumb->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				}			
			}
		}
		//つまみが上限超えた時の補正
		if (m_BGMThumbPosition.x <= MAX_ThubPosition)
		{
			m_BGMThumbPosition.x = MAX_ThubPosition;
		}
		else if (m_BGMThumbPosition.x >= MIN_ThubPosition)
		{
			m_BGMThumbPosition.x = MIN_ThubPosition;
		}

		if (m_SEThumbPosition.x <= MAX_ThubPosition)
		{
			m_SEThumbPosition.x = MAX_ThubPosition;
		}
		else if (m_SEThumbPosition.x >= MIN_ThubPosition)
		{
			m_SEThumbPosition.x = MIN_ThubPosition;
		}
		//音量の補正
		if (m_BGM_Volume < 0)
		{
			m_BGM_Volume = 0;
		}
		else if (m_BGM_Volume > 100)
		{
			m_BGM_Volume = 100;
		}

		if (m_SE_Volume < 0)
		{
			m_SE_Volume = 0;
		}
		else if (m_SE_Volume > 100)
		{
			m_SE_Volume = 100;
		}

		Scene::m_BGMVolume = m_BGM_Volume;
		Scene::m_SEVolume = m_SE_Volume;

	}
	


	texture_TitleSelect->TextureFlashing(90,0.01f);
}

void TitleTexture::Draw() 
{
	GameObject::Draw();
	if (Title::GetQuestSelect())
	{
		texture_TutorialButtonBG->Draw(40.0f, 300.0f);
		texture_TutorialButton->Draw(55.0f, 305.0f);

		texture_QuestButtonBG->Draw(40.0f, 375.0f);
		texture_QuestButton->Draw(55.0f, 380.0f);
		
		
	}
	else if (!m_OptionFlag)
	{
			if (!Title::GetMenuControl())
			{
				texture_TitleSelect->Draw(50.0f, 312.0f);
				texture_PushSpace->Draw(40.0f, 310.0f);
				texture_TitleLogo->Draw(100.0f, 0.0f);
			}
			if (Title::GetMenuControl())
			{
				texture_TitleSelect->Draw(m_MenuSelectPosition.x, m_MenuSelectPosition.y);
				texture_GameStart->Draw(40.0f, 300.0f);
				texture_OPTION->Draw(40.0f, 372.0f);
				texture_TitleLogo->Draw(100.0f, 0.0f);
			}
	}
	else 
	{
		texture_OPTIONUI->Draw(100.0f, 60.0f);
		texture_BuckButton->Draw(110.0f, 320.0f);
		texture_BGMThumb->Draw(m_BGMThumbPosition.x, m_BGMThumbPosition.y);  
		texture_SEThumb->Draw(m_SEThumbPosition.x, m_SEThumbPosition.y);	
		texture_SelectArrow->Draw(110.0f, m_SelectUIPosY);
	}
	
	
}

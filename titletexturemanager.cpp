#include"main.h"
#include"renderer.h"
#include"scene.h"
#include"manager.h"
#include"titletexturemanager.h"
#include"textureload.h"
#include"title.h"
#include"input.h"
#include"audio.h"

TextureLoad* texture_PushSpace = new TextureLoad;
TextureLoad* texture_GameStart = new TextureLoad;
TextureLoad* texture_OPTION = new TextureLoad;
TextureLoad* texture_TitleLogo = new TextureLoad;
TextureLoad* texture_TitleSelect = new TextureLoad;
TextureLoad* texture_OPTIONUI = new TextureLoad;
TextureLoad* texture_BuckButton = new TextureLoad;
TextureLoad* texture_BGMThumb = new TextureLoad;
TextureLoad* texture_SEThumb = new TextureLoad;

float Scene::m_BGMVolume;
float Scene::m_SEVolume;

void TitleTexture::Init()
{
	texture_PushSpace->Init("asset/texture/UI/PushSpacetoB.png");
	texture_PushSpace->SetTextureScale(900.0f, 150.0f);

	texture_GameStart->Init("asset/texture/UI/GAMESTART.png");
	texture_GameStart->SetTextureScale(900.0f, 150.0f);

	texture_OPTION->Init("asset/texture/UI/OPTION.png");
	texture_OPTION->SetTextureScale(900.0f, 150.0f);

	texture_TitleLogo->Init("asset/texture/UI/titlelogo.png");
	texture_TitleLogo->SetTextureScale(600.0f, 600.0f);

	texture_TitleSelect->Init("asset/texture/UI/menuselect.png");
	texture_TitleSelect->SetTextureScale(800.0f, 115.0f);

	texture_OPTIONUI->Init("asset/texture/UI/OPTIONUI.png");
	texture_OPTIONUI->SetTextureScale(600.0f, 600.0f);

	texture_BuckButton->Init("asset/texture/UI/BackButton.png"); 
	texture_BuckButton->SetTextureScale(120.0f, 50.0f);

	texture_BGMThumb->Init("asset/texture/UI/OptionThumb.png");
	texture_BGMThumb->SetTextureScale(30.0f, 30.0f);

	texture_SEThumb->Init("asset/texture/UI/OptionThumb.png");
	texture_SEThumb->SetTextureScale(30.0f, 30.0f);

	scene = Manager::GetScene();
	

	m_MenuSelectPosition = (D3DXVECTOR2(50.0f, 312.0f));
	//145Å`325
	m_BGMThumbPosition = D3DXVECTOR2(157.0f, 154.0f);
	m_SEThumbPosition = D3DXVECTOR2(157.0f, 273.0f);

	m_DecisiveSE = AddComponent<Audio>();
	m_DecisiveSE->Load("asset\\audio\\SE\\åàíËâπ.wav");

}

void TitleTexture::Uninit()
{
	texture_PushSpace->SetDestroy();
	texture_PushSpace->SetDestroy();
	texture_GameStart->SetDestroy();
	texture_OPTION->SetDestroy();
	texture_TitleLogo->SetDestroy();
	texture_OPTIONUI->SetDestroy();

	m_DecisiveSE->Uninit();

}

void TitleTexture::Update()
{
	m_MouseposX = GetMouseCursorPosXinWnd();
	m_MouseposY = GetMouseCursorPosYinWnd();

	if (Title::GetMenuControl())
	{
		if ((Input::GetKeyTrigger(VK_UP) ||  (130< m_MouseposX &&  m_MouseposX < 860 &&  620 < m_MouseposY && m_MouseposY <720))  && !m_OptionFlag )
		{		
			m_MenuSelectPosition =(D3DXVECTOR2(50.0f, 312.0f));
			m_GameButtonOverlap = true;
			m_OptionButtonOverlap = false;
		}
		else if (Input::GetKeyTrigger(VK_DOWN) || ((130 < m_MouseposX && m_MouseposX < 860 && 760 < m_MouseposY && m_MouseposY < 860)))
		{
			m_MenuSelectPosition = (D3DXVECTOR2(50.0f, 382.0f));	
			m_GameButtonOverlap = false;
			m_OptionButtonOverlap = true;
		}
		

		if (m_OptionButtonOverlap)
		{
			if (Input::GetKeyTrigger(VK_SPACE) || Input::GetKeyPress(VK_LBUTTON))
			{
				m_DecisiveSE->Volume(GetSEVolume());
				m_DecisiveSE->PlaySE();
				m_OptionFlag = true;
			}
		}

		if (m_OptionFlag)
		{
			if ((215 < m_MouseposX && m_MouseposX < 315 && 630 < m_MouseposY && m_MouseposY < 670))
			{
				texture_BuckButton->SetColor(D3DXCOLOR(0.9f, 0.5f, 0.1f,1.0f));
				if (Input::GetKeyTrigger(VK_LBUTTON))
				{
					m_DecisiveSE->Volume(GetSEVolume());
					m_DecisiveSE->PlaySE();
					m_OptionFlag = false;
				}
			}
			else
			{
				texture_BuckButton->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
			
			if (300 < m_MouseposY && m_MouseposY < 325)
			{
				if (MAX_ThubPosition-1 < m_BGMThumbPosition.x && m_BGMThumbPosition.x < MIN_ThubPosition+1 && Input::GetKeyPress(VK_LBUTTON))
				{
					texture_BGMThumb->SetColor(D3DXCOLOR(0.9f, 0.6f, 0.2f, 1.0f));
					m_BGMThumbPosition.x = m_MouseposX * 0.47;
					m_BGM_Volume = ((m_BGMThumbPosition.x - MAX_ThubPosition) / (MIN_ThubPosition - MAX_ThubPosition) * 100);
				}
				else
				{
					texture_BGMThumb->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				}

				if (m_BGMThumbPosition.x <= MAX_ThubPosition)
				{
					m_BGMThumbPosition.x = MAX_ThubPosition;
				}
				else if (m_BGMThumbPosition.x >= MIN_ThubPosition)
				{
					m_BGMThumbPosition.x = MIN_ThubPosition;
				}

			}

			
			if (535 < m_MouseposY && m_MouseposY < 560)
			{
				if (MAX_ThubPosition-1 < m_SEThumbPosition.x && m_SEThumbPosition.x < MIN_ThubPosition+1 && Input::GetKeyPress(VK_LBUTTON))
				{
					texture_SEThumb->SetColor(D3DXCOLOR(0.9f, 0.6f, 0.2f, 1.0f));
					m_SEThumbPosition.x = m_MouseposX * 0.47;
					m_SE_Volume = ((m_SEThumbPosition.x - MAX_ThubPosition) / (MIN_ThubPosition - MAX_ThubPosition) * 100);
				}
				else
				{
					texture_SEThumb->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				}

				if (m_SEThumbPosition.x <= MAX_ThubPosition)
				{
					m_SEThumbPosition.x = MAX_ThubPosition;
				}
				else if (m_SEThumbPosition.x >= MIN_ThubPosition)
				{
					m_SEThumbPosition.x = MIN_ThubPosition;
				}
			}
		}

		//âπó ÇÃï‚ê≥
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

void TitleTexture::Draw() //50,312 || 382 
{
	if (!m_OptionFlag)
	{
		if (!Title::GetMenuControl())
		{
			texture_TitleSelect->Draw(50.0f, 312.0f);
			texture_PushSpace->Draw(40.0f, 300.0f);
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
		texture_BGMThumb->Draw(m_BGMThumbPosition.x, m_BGMThumbPosition.y);  //150,154
		texture_SEThumb->Draw(m_SEThumbPosition.x, m_SEThumbPosition.y);	//150,273

	}
	
	
}

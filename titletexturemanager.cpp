#include"main.h"
#include"renderer.h"
#include"titletexturemanager.h"
#include"textureload.h"
#include"title.h"
#include"input.h"

TextureLoad* texture_PushSpace = new TextureLoad;
TextureLoad* texture_GameStart = new TextureLoad;
TextureLoad* texture_OPTION = new TextureLoad;
TextureLoad* texture_TitleLogo = new TextureLoad;
TextureLoad* texture_TitleSelect = new TextureLoad;
TextureLoad* texture_OPTIONUI = new TextureLoad;
TextureLoad* texture_BuckButton = new TextureLoad;
TextureLoad* texture_BGMThumb = new TextureLoad;
TextureLoad* texture_SEThumb = new TextureLoad;

void TitleTexture::Init()
{
	texture_PushSpace->Init("asset/texture/UI/PUSHSPACE.png");
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

	/*m_X = 50.0f;
	m_Y = 312.0f;*/
	//145Å`325
	m_BGMThumbPosition = D3DXVECTOR2(145.0f, 154.0f);
	m_SEThumbPosition = D3DXVECTOR2(145.0f, 273.0f);
}

void TitleTexture::Uninit()
{
	delete texture_PushSpace;
	delete texture_GameStart;
	delete texture_OPTION;
	delete texture_TitleLogo;
	delete texture_OPTIONUI;

}

void TitleTexture::Update()
{
	m_MouseposX = GetMouseCursorPosXinWnd();
	m_MouseposY = GetMouseCursorPosYinWnd();

	



	ImGui::Begin("Mouse");
	ImGui::InputFloat3("PositionX", &m_MouseposX);
	ImGui::InputFloat3("PositionY", &m_MouseposY);

	float hoseiX = m_MouseposX - 155.0f;
	//float hoseiY = m_MouseposY - 159.0f;
	ImGui::InputFloat2("BGMPos", m_BGMThumbPosition);
	ImGui::InputFloat2("SEPos", m_SEThumbPosition);
	ImGui::InputFloat("bgmvolume", &m_BGM_Volume);
	ImGui::InputFloat("sevolume", &m_SE_Volume);
	//ImGui::InputFloat("Pos", &hoseiY);
	ImGui::End();



	if (Title::GetMenuControl())
	{
		if (Input::GetKeyTrigger(VK_UP) ||  (130< m_MouseposX &&  m_MouseposX < 860 &&  620 < m_MouseposY && m_MouseposY <720) && !m_OptionFlag )
		{		
			m_MenuSelectPosition =(D3DXVECTOR2(50.0f, 312.0f));
			m_GameButtonOverlap = true;
			m_OptionButtonOverlap = false;
		}
		else if (Input::GetKeyTrigger(VK_DOWN) ||   (130 < m_MouseposX && m_MouseposX < 860 && 760 < m_MouseposY && m_MouseposY < 860))
		{
			m_MenuSelectPosition = (D3DXVECTOR2(50.0f, 382.0f));
			m_GameButtonOverlap = false;
			m_OptionButtonOverlap = true;
		}

		if (m_OptionButtonOverlap)
		{
			if (Input::GetKeyTrigger(VK_SPACE) || Input::GetKeyPress(VK_LBUTTON))
			{
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

	}
	texture_TitleSelect->TextureFlashing(90);
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

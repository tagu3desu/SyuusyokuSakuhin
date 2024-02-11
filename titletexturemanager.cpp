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
TextureLoad* texture_BGMTumb = new TextureLoad;
TextureLoad* texture_SETumb = new TextureLoad;

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

	texture_BGMTumb->Init("asset/texture/UI/OptionThumb.png");
	texture_BGMTumb->SetTextureScale(100.0f, 100.0f);

	texture_SETumb->Init("asset/texture/UI/OptionThumb.png");
	texture_SETumb->SetTextureScale(100.0f, 100.0f);

	m_X = 50.0f;
	m_Y = 312.0f;
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
	ImGui::End();

	if (Title::GetMenuControl())
	{
		if (Input::GetKeyTrigger(VK_UP) ||  (130< m_MouseposX &&  m_MouseposX < 860 &&  620 < m_MouseposY && m_MouseposY <720))
		{		
			m_X = 50.0f;
			m_Y = 312.0f;
			m_GameButtonOverlap = true;
			m_OptionButtonOverlap = false;
		}
		else if (Input::GetKeyTrigger(VK_DOWN) ||   (130 < m_MouseposX && m_MouseposX < 860 && 760 < m_MouseposY && m_MouseposY < 860))
		{
			m_X = 50.0f;
			m_Y = 382.0f;
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
			texture_TitleSelect->Draw(m_X, m_Y);
			texture_GameStart->Draw(40.0f, 300.0f);
			texture_OPTION->Draw(40.0f, 372.0f);
			texture_TitleLogo->Draw(100.0f, 0.0f);
		}
	}
	else
	{
		texture_OPTIONUI->Draw(100.0f, 60.0f);
		texture_BuckButton->Draw(110.0f, 320.0f);
		texture_BGMTumb->Draw(150.0f, 320.0f);

	}
	
	
}

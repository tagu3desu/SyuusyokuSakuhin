#include "main.h"
#include "renderer.h"
#include"potion.h"
#include"sprite.h"
#include"camera.h"
#include"scene.h"
#include"input.h"
#include"manager.h"
#include"textureload.h"
#include"itemcount.h"
#include"ItemManger.h"
#include"gametexturemanager.h"
TextureLoad* texture_Potion = new TextureLoad;
void Potion::Init()
{
	texture_Potion->Init("asset/texture/UI/potion.png");
	texture_Potion->SetTextureScale(85.0f, 85.0f);

	m_Scene = Manager::GetScene();
	m_PotionItemCount = m_Scene->AddGameObject<ItemCount>(SPRITE_LAYER);
	m_PotionItemCount->SetMaxCount(10);

	m_ItemCount = m_PotionItemCount->GetCount();
}

void Potion::Uninit()
{
	GameObject::Uninit();
}

void Potion::Update()
{

	m_ItemManager = m_Scene->GetGameObject<ItemManager>();
	m_PotionItemCount->SetCount(m_ItemCount);
	m_PotionItemCount->SetEnable(m_Enable);

	

	if (m_ItemManager->GetEnablePotion())
	{
		m_X = 818.0f;
	}
	else if(!m_ItemManager->GetEnablePotion())
	{
		m_X = 765.0f;
	}

	

	GameObject::Update();
}

void Potion::Draw()
{
	GameTexture* gametexture = m_Scene->GetGameObject<GameTexture>();
	m_ItemManager = m_Scene->GetGameObject<ItemManager>();
	if ((m_ItemManager->GetEnablePotion() || m_ItemManager->GetShowFlag()) && !gametexture->GetGameClear())
	{
		texture_Potion->Draw(m_X, 418.0f);
	}
	//if(!m_Enable)
	//{
	//	texture_Potion->Draw(756.0f, 414.0f);
	//}
}
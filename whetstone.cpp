#include "main.h"
#include "renderer.h"
#include"whetstone.h"
#include"sprite.h"
#include"camera.h"
#include"scene.h"
#include"input.h"
#include"manager.h"
#include"textureload.h"
#include"itemcount.h"
#include"ItemManger.h"
#include"gametexturemanager.h"
TextureLoad* texture_WheteStone = new TextureLoad;
void WheteStone::Init()
{
	texture_WheteStone->Init("asset/texture/UI/WhetStone.png");
	texture_WheteStone->SetTextureScale(87.0f, 87.0f);

	m_Scene = Manager::GetScene();
	m_WheteStoneItemCount = m_Scene->AddGameObject<ItemCount>(SPRITE_LAYER);
	m_WheteStoneItemCount->SetMaxCount(10);

	m_ItemCount = m_WheteStoneItemCount->GetCount();
}

void WheteStone::Uninit()
{
	GameObject::Uninit();
}

void WheteStone::Update()
{
	m_ItemManager = m_Scene->GetGameObject<ItemManager>();
	m_WheteStoneItemCount->SetCount(m_ItemCount);
	m_WheteStoneItemCount->SetEnable(m_Enable);

	if (m_ItemManager->GetEnableWheteSton())
	{
		m_X = 818.0f;
	}
	else if (!m_ItemManager->GetEnableWheteSton())
	{
		m_X = 756.0f;
	}


	GameObject::Update();
}

void WheteStone::Draw()
{
	GameTexture* gametexture = m_Scene->GetGameObject<GameTexture>();
	m_ItemManager = m_Scene->GetGameObject<ItemManager>();
	if ((m_ItemManager->GetEnableWheteSton() || m_ItemManager->GetShowFlag()) && !gametexture->GetGameClear())
	{
		texture_WheteStone->Draw(m_X, 418.0f);
	}
	
}
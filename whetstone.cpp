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
TextureLoad* texture_WheteStone = new TextureLoad;
void WheteStone::Init()
{
	texture_WheteStone->Init("asset/texture/UI/WhetStone.png");
	texture_WheteStone->SetTextureScale(90.0f, 90.0f);

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
	m_WheteStoneItemCount->SetCount(m_ItemCount);
	m_WheteStoneItemCount->SetEnable(m_Enable);
	GameObject::Update();
}

void WheteStone::Draw()
{

	if (m_Enable)
	{
		texture_WheteStone->Draw(816.0f, 414.0f);
	}
}
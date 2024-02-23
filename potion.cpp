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
TextureLoad* texture_Potion = new TextureLoad;
void Potion::Init()
{
	texture_Potion->Init("asset/texture/UI/potion.png");
	texture_Potion->SetTextureScale(90.0f, 90.0f);

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
	m_PotionItemCount->SetCount(m_ItemCount);
	m_PotionItemCount->SetEnable(m_Enable);

	GameObject::Update();

	
}

void Potion::Draw()
{
	

	if (m_Enable)
	{
		texture_Potion->Draw(816.0f, 414.0f);
	}
}
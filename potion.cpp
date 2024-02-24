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

	m_ItemManager = m_Scene->GetGameObject<ItemManager>();
	m_PotionItemCount->SetCount(m_ItemCount);
	m_PotionItemCount->SetEnable(m_Enable);

	

	if (m_ItemManager->GetEnablePotion())
	{
		m_X = 816.0f;
	}
	else if(!m_ItemManager->GetEnablePotion())
	{
		m_X = 756.0f;
	}

	//GUIにパラメータ表示
	ImGui::SetNextWindowSize(ImVec2(300, 250));
	ImGui::Begin("Potion");
	ImGui::InputFloat("X", &m_X);
	ImGui::End();

	GameObject::Update();
}

void Potion::Draw()
{
	m_ItemManager = m_Scene->GetGameObject<ItemManager>();
	if (m_ItemManager->GetEnablePotion() || m_ItemManager->GetShowFlag())
	{
		texture_Potion->Draw(m_X, 414.0f);
	}
	//if(!m_Enable)
	//{
	//	texture_Potion->Draw(756.0f, 414.0f);
	//}
}
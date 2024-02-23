#include "main.h"
#include "renderer.h"
#include"manager.h"
#include "ItemManger.h"
#include"potion.h"
#include"whetstone.h"
#include"input.h"

void ItemManager::Init()
{
	m_Scene = Manager::GetScene();
	m_Potion = m_Scene->AddGameObject<Potion>(SPRITE_LAYER);
	m_WheteStone = m_Scene->AddGameObject<WheteStone>(SPRITE_LAYER);
}

void ItemManager::Uninit() {};

void ItemManager::Update()
{
	if (Input::GetKeyTrigger('Q') || Input::GetKeyTrigger('E'))
	{
		if (m_PotionEnable)
		{
			m_WheteStoneEnable = true;
			m_PotionEnable = false;
		}
		else if (m_WheteStoneEnable)
		{
			m_WheteStoneEnable = false;
			m_PotionEnable = true;
		}
	}

	

	m_Potion->SetEnable(m_PotionEnable);
	m_WheteStone->SetEnable(m_WheteStoneEnable);
	//GUIにパラメータ表示
	ImGui::SetNextWindowSize(ImVec2(300, 250));
	ImGui::Begin("Item");
	ImGui::Checkbox("Potion", &m_PotionEnable);
	ImGui::Checkbox("WheteSton", &m_WheteStoneEnable);
	ImGui::End();
}

void ItemManager::Draw()
{

}

void ItemManager::UsePotion()
{
	m_Potion->Use(1);
}

void ItemManager::UseWheteStone()
{
	m_WheteStone->Use(1);
}

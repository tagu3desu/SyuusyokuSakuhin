#include "main.h"
#include "renderer.h"
#include"manager.h"
#include "ItemManger.h"
#include"potion.h"
#include"whetstone.h"
#include"input.h"
#include"audio.h"
#include"scene.h"
#include"inputx.h"
void ItemManager::Init()
{
	m_Scene = Manager::GetScene();
	m_Potion = m_Scene->AddGameObject<Potion>(SPRITE_LAYER);
	m_WheteStone = m_Scene->AddGameObject<WheteStone>(SPRITE_LAYER);

	m_SelectSE = AddComponent<Audio>();
	m_SelectSE->Load("asset\\audio\\SE\\Œˆ’è‰¹.wav");
}

void ItemManager::Uninit() {
	m_SelectSE->Uninit();
};

void ItemManager::Update()
{
	m_Hweel = GetHweel();
	if (Input::GetKeyPress('Q') || InputX::IsButtonPressed(0,XINPUT_GAMEPAD_LEFT_SHOULDER))
	{
		m_ShowItemFlag = true;
		if (m_OldHweel + 1 == m_Hweel || InputX::IsButtonTriggered(0,XINPUT_GAMEPAD_X))
		{
			m_SelectSE->Volume(Scene::m_SEVolume*0.01f);
			m_SelectSE->PlaySE();
			if (m_NowItem == 0)
			{
				m_NowItem = static_cast<ITEM>(static_cast<int>(Item_Max) - 1);
			}
			else
			{
				m_NowItem = static_cast<ITEM>(static_cast<int>(m_NowItem) - 1);
			}
		}

		if (m_OldHweel - 1 == m_Hweel || InputX::IsButtonTriggered(0, XINPUT_GAMEPAD_B))
		{
			m_SelectSE->Volume(Scene::m_SEVolume*0.01f);
			m_SelectSE->PlaySE();
			if (m_NowItem == m_MaxItem)
			{
				m_NowItem = Item_Potion;
			}
			else
			{
				m_NowItem = static_cast<ITEM>(static_cast<int>(m_NowItem) + 1);
			}

		}
	}
	else
	{
		m_ShowItemFlag = false;
	}


	if (m_NowItem == 0)	//‰ñ•œ–ò
	{
		m_PotionEnable = true;
		m_WheteStoneEnable = false;
		m_ItemNumber = 0;

	}
	else if (m_NowItem == 1)	//“uÎ
	{
		m_WheteStoneEnable = true;
		m_PotionEnable = false;
		m_ItemNumber = 1;
	}
	else
	{
		m_ItemNumber = 2;
	}

	m_Potion->SetEnable(m_PotionEnable);
	m_WheteStone->SetEnable(m_WheteStoneEnable);

	m_OldHweel = m_Hweel;
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

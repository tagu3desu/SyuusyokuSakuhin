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
	m_ItemManager = m_Scene->GetGameObject<ItemManager>();
	m_WheteStoneItemCount->SetCount(m_ItemCount);
	m_WheteStoneItemCount->SetEnable(m_Enable);

	if (m_ItemManager->GetEnableWheteSton())
	{
		m_X = 816.0f;
	}
	else if (!m_ItemManager->GetEnableWheteSton())
	{
		m_X = 756.0f;
	}

	//GUIにパラメータ表示
	ImGui::SetNextWindowSize(ImVec2(300, 250));
	ImGui::Begin("WheteStone");
	ImGui::InputFloat("X", &m_X);
	ImGui::End();

	GameObject::Update();
}

void WheteStone::Draw()
{
	m_ItemManager = m_Scene->GetGameObject<ItemManager>();
	if (m_ItemManager->GetEnableWheteSton() || m_ItemManager->GetShowFlag())
	{
		texture_WheteStone->Draw(m_X, 414.0f);
	}
	
}
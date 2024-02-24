#pragma once
#include"gameobject.h"

enum ITEM
{
	Item_Potion,
	Item_WheteStone,
	Item_Max,
};

class ItemManager : public GameObject
{
private:
	ITEM m_NowItem = Item_Potion;
	ITEM m_MaxItem = static_cast<ITEM>(static_cast<int>(Item_Max) - 1);

	

	

	//アイテム関連
	bool m_PotionEnable = true;
	bool m_WheteStoneEnable = false;
	bool m_ShowItemFlag = false;
	int m_ItemNumber = 0;

	//マウスホイールの処理
	int m_Hweel = 0;
	int m_OldHweel = 0;
	
	//ポインタ変数
	class Scene* m_Scene;
	class Potion* m_Potion;
	class WheteStone* m_WheteStone;
	
	//サウンド関連
	class Audio* m_SelectSE{};

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void UsePotion();
	void UseWheteStone();
	bool GetEnablePotion() { return m_PotionEnable; }
	bool GetEnableWheteSton() { return m_WheteStoneEnable; }
	bool GetShowFlag() { return m_ShowItemFlag; }
	
};
#pragma once
#include"gameobject.h"
class ItemManager : public GameObject
{
private:

	class Scene* m_Scene;
	class Potion* m_Potion;
	class WheteStone* m_WheteStone;

	bool m_PotionEnable = true;
	bool m_WheteStoneEnable = false;

	bool m_UsePotion = false;
	bool m_UseWheteSton = false;
	bool m_ShowItemFlag = false;
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
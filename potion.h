#pragma once
#include"gameobject.h"

class	Potion :public GameObject
{
private:
	
	
	class Scene* m_Scene;
	class ItemCount* m_PotionItemCount;

	int m_ItemCount = 0;

	bool m_Enable=false;
	
	float m_X = 0;
	class ItemManager* m_ItemManager;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void Use(int count) { m_ItemCount -= count; }
	void SetEnable(bool enable) { m_Enable = enable; }
	int GetCount() { return m_ItemCount; }
};

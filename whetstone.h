#pragma once
#include"gameobject.h"

class	WheteStone :public GameObject
{
private:
	
	
	class Scene* m_Scene;
	class ItemCount* m_WheteStoneItemCount;

	int m_ItemCount = 0;

	bool m_Enable = false;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void Use(int count) { m_ItemCount -= count; }
	void SetEnable(bool enable) { m_Enable = enable; }
	int GetCount() { return m_ItemCount; }
};

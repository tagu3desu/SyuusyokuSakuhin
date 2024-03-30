#pragma once
#include"baseitem.h"

class	WheteStone :public BaseItem
{
private:
	class Scene* m_Scene;
	class ItemCount* m_WheteStoneItemCount;
	class ItemManager* m_ItemManager;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};

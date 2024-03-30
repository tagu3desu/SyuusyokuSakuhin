#pragma once
#include"baseitem.h"

class	Potion :public BaseItem
{
private:
	class Scene* m_Scene;
	class ItemCount* m_PotionItemCount;
	class ItemManager* m_ItemManager;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};

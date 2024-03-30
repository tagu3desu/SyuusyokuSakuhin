#pragma once
#include"gameobject.h"
class BaseItem :public GameObject
{
protected:
	int m_ItemCount = 0;

	bool m_Enable = false;
	float m_X=0;
public:
	void Use(int count) { m_ItemCount -= count; }
	void SetEnable(bool enable) { m_Enable = enable; }
	int GetCount() { return m_ItemCount; }
};

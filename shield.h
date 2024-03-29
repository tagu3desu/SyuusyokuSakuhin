#pragma once
#include"model.h"
#include"gameobject.h"

class Shield : public GameObject
{
private:
	Model* m_Model{};


	D3DXMATRIX  m_Parent{};
	
	bool m_ShieldHit{};


	class Scene* m_Scene{};
	class BoxCollider* m_ShieldCollider{};
	class RockEffect* m_RockEffect{};
	class Enemy* m_Enemy{};
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	bool GetShieldHit() { return m_ShieldHit;}
};



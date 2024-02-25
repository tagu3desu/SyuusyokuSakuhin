#pragma once
#include"model.h"
#include"gameobject.h"

class Shield : public GameObject
{
private:
	Model* m_Model{};

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	D3DXMATRIX  m_Parent{};
	
	bool m_ShieldHit{};


	class Scene* m_Scene{};
	class Collider* m_ShieldCollider{};
	class RockEffect* m_RockEffect{};
	class Enemy* m_Enemy{};
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	bool GetShieldHit() { return m_ShieldHit;}
};



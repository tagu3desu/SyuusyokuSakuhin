#pragma once
#include"model.h"
#include"gameobject.h"

class Sword : public GameObject
{
private:
	Model* m_Model{};

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	D3DXMATRIX  m_Parent{};
	D3DXMATRIX  m_ChildMatrix{};
	D3DXVECTOR3  m_BottomVertex;
	bool m_Swordhit;

	

	class Scene* m_Scene{};
	class Collider* m_SwordCollider{};
	class Trail* m_SwordTrail{};
	class SwordTopVertex* m_SwordTopVertex{};
public:
	
	D3DXVECTOR3 GetBottomVertexPostion() { return m_BottomVertex; }
	D3DXMATRIX GetChild() { return m_ChildMatrix;}

	bool GetSwordHit() { return m_Swordhit; }

	void Init();
	void Uninit();
	void Update();
	void Draw();
};

class SwordTopVertex :public GameObject
{
private:
	static ID3D11Buffer* m_VertexBuffer;
	D3DXMATRIX m_Parent{};
	D3DXVECTOR3 m_TopVertex;

	
	class Scene* m_Scene{};


public:
	D3DXVECTOR3 GetTopVertexPostion() { return m_TopVertex; }

	static void Load();
	static void Unload();

	void Init();
	void Uninit();
	void Update();
	void Draw();
};


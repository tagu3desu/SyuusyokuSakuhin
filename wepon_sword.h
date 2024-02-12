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
	
	// 先端と終わりの頂点を格納する変数を定義
	D3DXVECTOR3  m_BottomVertex;

	bool m_swordhit;

	VERTEX_3D bottom;

	class Scene* scene{};
	class Collider* m_SwordCollider{};
public:
	
	D3DXVECTOR3 GetBottomVertexPostion() { return m_BottomVertex; }
	D3DXMATRIX GetChild() { return m_ChildMatrix;}

	bool GetSwordHit() { return m_swordhit; }

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

	
	class Scene* scene{};


public:
	D3DXVECTOR3 GetTopVertexPostion() { return m_TopVertex; }

	static void Load();
	static void Unload();

	void Init();
	void Uninit();
	void Update();
	void Draw();
};


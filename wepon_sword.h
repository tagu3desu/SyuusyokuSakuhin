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
	

	
	

	// ��[�ƏI���̒��_���i�[����ϐ����`
	D3DXVECTOR3  m_BottomVertex;

	

	bool m_swordhit;

	VERTEX_3D bottom;
	


public:
	
	D3DXVECTOR3 GetBottomVertexPostion() { return m_BottomVertex; }
	D3DXMATRIX GetChild() { return m_ChildMatrix;}

	void Init();
	void Uninit();
	void Update();
	void Draw();

	
};



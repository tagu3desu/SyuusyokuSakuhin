#pragma once
#include"model.h"
#include"gameobject.h"

class Axe : public GameObject
{
private:
	Model* m_Model{};

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	D3DXMATRIX  m_Parent{};

	D3DXVECTOR3 m_TrailPosition;

	bool m_swordhit;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};



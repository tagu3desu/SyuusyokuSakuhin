#pragma once
#include"model.h"
#include"gameobject.h"

class Gun : public GameObject
{
private:
	Model* m_Model{};

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	D3DXMATRIX  m_Parent{};



public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};



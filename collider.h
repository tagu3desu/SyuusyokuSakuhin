#pragma once
#include"main.h"
#include"model.h"
#include"gameobject.h"

class Collider : public GameObject
{
private:
	Model* m_Model{};

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	D3DXMATRIX m_Parent{};

	D3DXCOLOR m_ColliderColor{0.0f,1.0f,0.0f,0.0f};

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};


#pragma once
#include "gameObject.h"

class WaterSurFace : public GameObject
{

private:
	ID3D11Buffer* m_VertexBuffer{};
	ID3D11Buffer* m_IndexBuffer{};
	ID3D11ShaderResourceView* m_Texture{};
	

	VERTEX_3D					m_Vertex[21][21]{};

	float m_U = 0.0f;
	float m_U2 = 0.0f;

public:
	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;


	float GetHeight(D3DXVECTOR3 Position);
};
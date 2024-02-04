#pragma once


#include "gameObject.h"

#define MESH_COUNT_X 10
#define MESH_COUNT_Z 10

class BaseCamp : public GameObject
{

private:
	static ID3D11Buffer*				m_VertexBuffer;
	static ID3D11Buffer*				m_IndexBuffer;
	static ID3D11ShaderResourceView*	m_Texture;

	static VERTEX_3D					m_Vertex[MESH_COUNT_X][MESH_COUNT_Z];

	ID3D11VertexShader*			m_VertexShader{};
	ID3D11PixelShader*			m_PixelShader{};
	ID3D11InputLayout*			m_VertexLayout{};
	

public:
	static void Load();
	static void Unload();

	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	float  GetHeight(D3DXVECTOR3 Position);
	D3DXVECTOR3 GetCenterPosition();
};
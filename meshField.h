#pragma once


#include "gameObject.h"

class MeshField : public GameObject
{

private:
	static ID3D11Buffer*				m_VertexBuffer;
	static ID3D11Buffer*				m_IndexBuffer;
	static ID3D11ShaderResourceView*	m_Texture;
	static ID3D11ShaderResourceView*	m_NormalTexture;

	static VERTEX_3D					m_Vertex[21][21];

	ID3D11VertexShader*			m_VertexShader{};
	ID3D11PixelShader*			m_PixelShader{};
	ID3D11InputLayout*			m_VertexLayout{};
	
	bool m_BattleMapFlag = false;
public:
	static void Load();
	static void Unload();

	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void SetMapActive(bool flag) { m_BattleMapFlag = flag; }
	bool GetMapActive() { return m_BattleMapFlag; }
	float  GetHeight(D3DXVECTOR3 Position);
	D3DXVECTOR3 GetCenterPosition();
};
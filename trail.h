#pragma once

#include "gameObject.h"
#include<queue>
#include<deque>

#define VERTEX_NUMBER			1000//18


class Trail : public GameObject
{

private:
	ID3D11Buffer* m_VertexBuffer{};
	ID3D11ShaderResourceView* m_Texture{};
	
	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	VERTEX_3D		m_Vertex[VERTEX_NUMBER * 4]{};

	
	std::queue<D3DXVECTOR3> m_TopVertexArray;
	std::queue<D3DXVECTOR3> m_BottomVertexArray;

	std::queue<D3DXVECTOR3> m_TopVertexArrayCopy;
	std::queue<D3DXVECTOR3> m_BottomVertexArrayCopy;

	D3DXVECTOR3 m_TopVertex;
	D3DXVECTOR3 m_BottomVertex;
	bool m_TrailDrawFlag = false;
	bool m_TrailEnable=true;

public:
	void Init() ;
	void Uninit() ;
	void Update() ;
	void Draw() ;
	void SetTrail(D3DXVECTOR3 top, D3DXVECTOR3 bottom, bool trailflag) { m_TopVertex = top; m_BottomVertex = bottom;  m_TrailDrawFlag = trailflag;}
	void SetTrailEnable(bool enable) { m_TrailEnable = enable;}
	bool GetTrailEnable() { return m_TrailEnable;}
};
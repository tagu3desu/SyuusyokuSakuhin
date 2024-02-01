#pragma once

#include "gameObject.h"
#include<queue>
#include<deque>

#define VERTEX_NUMBER			8
#define KEEP_VERTEX				8

class Trail : public GameObject
{

private:
	ID3D11Buffer* m_VertexBuffer{};
	ID3D11ShaderResourceView* m_Texture{};
	ID3D11ShaderResourceView* m_TextureNormal{};
	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	VERTEX_3D		m_Vertex[VERTEX_NUMBER * 4]{};

	
	//std::vector<D3DXVECTOR3> m_TopVertexArray;
	//std::vector<D3DXVECTOR3> m_BottomVertexArray;

	std::queue<D3DXVECTOR3> m_TopVertexArray;
	std::queue<D3DXVECTOR3> m_BottomVertexArray;

	std::queue<D3DXVECTOR3> m_TopVertexArrayCopy;
	std::queue<D3DXVECTOR3> m_BottomVertexArrayCopy;


	/*std::queue<D3DXVECTOR3> m_TopVertexArray;
	std::queue<D3DXVECTOR3> m_BottomVertexArray;

	std::queue<D3DXVECTOR3> m_TopVertexArrayCopy;
	std::queue<D3DXVECTOR3> m_BottomVertexArrayCopy;*/

	D3DXVECTOR3 befortopvertex;
	D3DXVECTOR3 beforbottomvertex;

	VERTEX_3D top;
	VERTEX_3D bottom;

public:
	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
};
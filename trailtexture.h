#pragma once
#include"gameobject.h"

class TrailTexture :public GameObject
{
private:


	static ID3D11Buffer* m_VertexBuffer;
	static ID3D11ShaderResourceView* m_Texture;

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	D3DXMATRIX m_Parent{};
	int m_Count{};

	

	D3DXVECTOR3 m_TopVertex;
	

public:
	D3DXVECTOR3 GetTopVertexPostion() { return m_TopVertex; }

	static void Load();
	static void Unload();

	void Init();
	void Uninit();
	void Update();
	void Draw();
};


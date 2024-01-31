#pragma once
#include"gameobject.h"

class Grass :public GameObject
{
private:


	ID3D11Buffer* m_VertexBuffer;
	ID3D11ShaderResourceView* m_Texture;

	ID3D11Buffer* m_PositionBuffer;
	ID3D11ShaderResourceView* m_PositionSRV;

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	int m_Count{};
public:
	static void Load();
	static void Unload();

	void Init();
	void Uninit();
	void Update();
	void Draw();
};


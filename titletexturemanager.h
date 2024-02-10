#pragma once
#include"gameobject.h"

class TitleTexture: public GameObject
{
private:
	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	float m_X;
	float m_Y;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};
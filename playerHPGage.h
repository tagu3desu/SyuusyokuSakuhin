#pragma once
#include"gameobject.h"

class	PlayerHPGage :public GameObject
{
private:
	ID3D11Buffer* m_VertexBuffer{};
	ID3D11ShaderResourceView* m_Texture{};
	ID3D11ShaderResourceView* m_TextureFPS{};

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};
	int x=5;
	int	y=696;
	int MaxGage = 340.0f;
	
	int sizeY = 20.0f;

	float m_Red = 1.0f;
	float m_Green = 1.0f;
	float m_Blue = 1.0f;

	class Player* m_Player{};
	
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	int sizeX = 340.0f;

};

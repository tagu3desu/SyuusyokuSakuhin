#pragma once
#include"gameobject.h"

class	Potion :public GameObject
{
private:
	ID3D11Buffer* m_VertexBuffer{};
	ID3D11ShaderResourceView* m_Texture{};
	ID3D11ShaderResourceView* m_TextureFPS{};

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};
	
	int x = SCREEN_WIDTH / 1.3;
	int y = SCREEN_HEIGHT / 1.3;
	int sizeX = 150.0f;
	int sizeY = 150.0f;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	
};

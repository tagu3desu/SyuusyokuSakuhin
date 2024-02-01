#pragma once
#include"gameobject.h"

class TextureLoad : public GameObject
{
private:
	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	ID3D11Buffer* m_VertexBuffer{};
	ID3D11ShaderResourceView* m_Texture{};

	D3DXCOLOR m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	bool shakeflag = false;

	float m_x=0;
	float m_y=0;
	bool m_up=false;
	bool m_down = false;

	D3DXVECTOR2 m_minpos{};
	D3DXVECTOR2 m_maxpos{};


	float Width=100;
	float Height=100;

public:
	void Init(const char* TextureName);
	void Uninit();
	void Update();
	void Draw(float m_x,float m_y);

	void SetColor(D3DXCOLOR Color) { m_Color = Color; }
	void SetTexturePostion(float X, float Y) { X = m_x; Y = m_y; }
	void UpDownTexture(bool shake) { shakeflag = shake; }

};
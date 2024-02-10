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

	float m_OffsetX{};
	float m_OffsetY{};

	D3DXVECTOR2 m_minpos{};
	D3DXVECTOR2 m_maxpos{};

	float m_AlfaColor = 1.0f;
	int m_Count = 0;

	float m_width=100;
	float m_height=100;

	int m_FlashInterval;


public:
	void Init(const char* TextureName);
	void Uninit();
	void Update();
	void Draw(float m_x,float m_y );

	void SetColor(D3DXCOLOR Color) { m_Color = Color; }
	void SetOffset(float offsetx, float offsety) { m_OffsetX = offsetx, m_OffsetY = offsety; }
	void SetTexturePostion(float X, float Y) { X = m_x; Y = m_y; }
	void SetTextureScale(float width, float height) { m_width = width; m_height = height; }
	void UpDownTexture(bool shake) { shakeflag = shake; }

	float GetMenuSelectPosition() { return m_x, m_y;}
	bool CheckMenuSelectPosition (float x,float y) 
	{  
		if (x == m_x && y == m_y)
		{
			return true;
		}
		else
		{
			return  false;
		}
		
	}

	void TextureFlashing(int interval)	//Šî–{90
	{
		m_Count++;
		if (m_Count < 90)
		{
			m_AlfaColor -= 0.01f;
		}
		else if (m_Count > interval && m_Count < (interval * 2))
		{
			m_AlfaColor +=0.01f;
		}
		else if (m_Count > (interval * 2))
		{
			m_Count = 0;
		}

		SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_AlfaColor));
	}
};
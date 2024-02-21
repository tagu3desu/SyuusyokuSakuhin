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

	bool m_Shakeflag{};

	float m_X=0;
	float m_Y=0;
	bool m_Up{};
	bool m_Down{};

	float m_OffsetX{};
	float m_OffsetY{};

	D3DXVECTOR2 m_Minpos{};
	D3DXVECTOR2 m_Maxpos{};

	float m_AlfaColor = 1.0f;
	int m_Count = 0;

	float m_Width=100;
	float m_Height=100;

	int m_FlashInterval;

	class Audio* m_UiSe{};

	float m_MoveHeight;
	int m_ShowTime{};
public:
	void Init(const char* TextureName);
	void Uninit();
	void Update();
	void Draw(float m_X,float m_Y );

	void SetColor(D3DXCOLOR Color) { m_Color = Color; }
	void SetOffset(float offsetx, float offsety) { m_OffsetX = offsetx, m_OffsetY = offsety; }
	void SetTexturePostion(float X, float Y) { X = m_X; Y = m_Y; }
	void SetTextureScale(float width, float height) { m_Width = width; m_Height = height; }
	void UpDownTexture(bool shake) { m_Shakeflag = shake; }

	float GetMenuSelectPosition() { return m_X, m_Y;}
	bool CheckMenuSelectPosition (float x,float y) 
	{  
		if (x == m_X && y == m_Y)
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


	float UiMove(int heightlimit, GameObject* object1 ,int showtime);
};
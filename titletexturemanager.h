#pragma once
#include"gameobject.h"


#define MAX_ThubPosition 145
#define MIN_ThubPosition 325

class TitleTexture: public GameObject
{
private:
	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	float m_X;
	float m_Y;

	float m_OldX;
	float m_NewX;
	float difference;

	D3DXVECTOR2 m_MenuSelectPosition{};

	D3DXVECTOR2 m_BGMThumbPosition{};
	D3DXVECTOR2 m_SEThumbPosition{};

	float m_BGM_Volume{};
	float m_SE_Volume{};

	float m_MouseposX;
	float m_MouseposY;

	bool m_GameButtonOverlap{};
	bool m_OptionButtonOverlap{};
	bool m_OptionFlag{};

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	bool GetGameButtonOverLap() { return m_GameButtonOverlap; }
};  
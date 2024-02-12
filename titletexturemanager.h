#pragma once
#include"gameobject.h"


#define MAX_ThubPosition 145
#define MIN_ThubPosition 325

class TitleTexture: public GameObject
{
private:

	class Scene* scene{};

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

	float m_BGM_Volume=8.0f;
	float m_SE_Volume=8.0f;

	float m_MouseposX;
	float m_MouseposY;

	bool m_GameButtonOverlap{};
	bool m_OptionButtonOverlap{};
	bool m_OptionFlag{};

	class Audio* m_DecisiveSE{};
	class Audio* m_SelectSE{};
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	bool GetGameButtonOverLap() { return m_GameButtonOverlap; }

	float GetBGMVolume() { return m_BGM_Volume/100; }
	float GetSEVolume() { return m_SE_Volume/100; }
};  


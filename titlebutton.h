#pragma once
#include"gameobject.h"

class TitleButton :public GameObject
{

private:
	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	class Sprite* m_Sprite{};
	float m_AlfaColor = 1.0f;
	bool m_FadeOut = false;
	bool m_FadeFinish = false;


	
	int m_Count = 0;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};

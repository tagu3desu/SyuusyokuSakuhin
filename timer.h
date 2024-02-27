#pragma once
#include"gameobject.h"

class ClockTimeHand :public GameObject
{
private:


	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};

class ClockTimeLimit :public GameObject
{
private:

	float m_LimitTime = 0;
	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

public:
	void SetLimitTime(float limit);

	void Init();
	void Uninit();
	void Update();
	void Draw();
};

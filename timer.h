#pragma once
#include"gameobject.h"

class ClockTimeHand :public GameObject
{
private:


	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	int m_TimeCount = 0;
	static float m_TimeSecond;
	static float m_TimeMilliSeconds;
	static float m_TimeMin;
	static int m_Rank;
	class Scene* m_Scene;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	
	float GetTimeMin() { return m_TimeMin; }
	float GetTimeSecond() { return m_TimeSecond; }
	float GetTimeMilliSecond() { return m_TimeMilliSeconds; }
	int GetRank() { return m_Rank; }
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

#pragma once
#include"gameobject.h"

class	ClearRank :public GameObject
{
private:
	ID3D11Buffer* m_VertexBuffer{};
	ID3D11ShaderResourceView* m_Texture{};

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	float m_X;
	float m_Y;
	float m_PosX;

	int m_Rank = 0;	//ƒ‰ƒ“ƒN 0=S, 1=A,
	int m_MaxItemCount = 0;
	D3DXCOLOR m_RankColor;
	int digits = 0;	//”š‚ÌŒ…”
	bool m_Enable = false; //•\¦”ñ•\¦

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void SetMaxCount(int count) { m_MaxItemCount = m_Rank = count; }
	void SetTexturePostion(float X, float Y) { m_X = X; m_Y = Y; }
	void AddCount(int Count) { m_Rank += Count; }
	void SubstractCount(int MainasuCount) { m_Rank -= MainasuCount; }
	void SetRank(int Count) { m_Rank = Count; }
	void SetEnable(bool enable) { m_Enable = enable; }
	int GetCount() { return m_Rank; }
};

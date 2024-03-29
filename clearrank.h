#pragma once
#include"gameobject.h"

class	ClearRank :public GameObject
{
private:
	ID3D11Buffer* m_VertexBuffer{};
	ID3D11ShaderResourceView* m_Texture{};

	

	float m_X = 0.0f;;
	float m_Y=0.0f;
	

	int m_Rank = 0;	
	D3DXCOLOR m_RankColor;
	int digits = 0;	//”š‚ÌŒ…”
	bool m_Enable = false; //•\¦”ñ•\¦

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	
	void SetTexturePostion(float X, float Y) { m_X = X; m_Y = Y; }
	void SetRank(int Count) { m_Rank = Count; }
};

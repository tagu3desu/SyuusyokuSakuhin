#pragma once
#include"gameobject.h"

class	TimeCount :public GameObject
{
private:
	ID3D11Buffer* m_VertexBuffer{};
	ID3D11ShaderResourceView* m_Texture{};


	float m_X;
	float m_Y;
	float m_PosX;

	int m_Time=0;	//アイテム数
	int m_MaxItemCount = 0;

	int digits = 0;	//数字の桁数
	bool m_Enable = false; //表示非表示

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void SetMaxCount(int count) { m_MaxItemCount = m_Time =count;}
	void SetTexturePostion(float X, float Y) { m_PosX =X; m_Y=Y; }
	void AddCount(int Count) { m_Time += Count;}
	void SubstractCount(int MainasuCount) { m_Time -= MainasuCount; }
	void SetCount(int Count) { m_Time = Count; }
	void SetEnable(bool enable) { m_Enable = enable; }
	int GetCount() { return m_Time; }
};

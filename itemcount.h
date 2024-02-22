#pragma once
#include"gameobject.h"

class	ItemCount :public GameObject
{
private:
	ID3D11Buffer* m_VertexBuffer{};
	ID3D11ShaderResourceView* m_Texture{};

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	float m_X;
	float m_Y;
	

	int m_ItemCount=0;
	int digits = 0;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void SetTexturePostion(float X, float Y) { m_X=X; m_Y=Y; }
	void AddCount(int Count) { m_ItemCount += Count;}
	void SubstractCount(int MainasuCount) { m_ItemCount -= MainasuCount; }
	void SetCount(int Count) { m_ItemCount = Count; }
	int GetCount() { return m_ItemCount; }
};

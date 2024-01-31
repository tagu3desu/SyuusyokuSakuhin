#pragma once
#include"gameobject.h"

class	PotionCount :public GameObject
{
private:
	ID3D11Buffer* m_VertexBuffer{};
	ID3D11ShaderResourceView* m_Texture{};

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};


	

	int m_potioncount=0;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void AddCount(int Count) { m_potioncount += Count;}
	void SubstractCount(int MainasuCount) { m_potioncount -= MainasuCount; }
	void SetCount(int Count) { m_potioncount = Count; }
	int GetCount() { return m_potioncount; }
};

#pragma once
#include"gameobject.h"

class HowlEffect :public GameObject
{
private:


	static ID3D11Buffer* m_VertexBuffer;
	static ID3D11ShaderResourceView* m_Texture;



	int m_Count{};
	D3DXMATRIX m_Parent{};
	
public:
	static void Load();
	static void Unload();


	void Init();
	void Uninit();
	void Update();
	void Draw();
};


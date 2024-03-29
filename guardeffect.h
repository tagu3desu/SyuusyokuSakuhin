#pragma once
#include"gameobject.h"

class GuardEffect :public GameObject
{
private:


	static ID3D11Buffer* m_VertexBuffer;
	static ID3D11ShaderResourceView* m_Texture;

	

	int m_Count{};
public:
	static void Load();
	static void Unload();

	void Init();
	void Uninit();
	void Update();
	void Draw();
};


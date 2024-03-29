#pragma once
#include"gameobject.h"

class Field:public GameObject
{
private:

	
	ID3D11Buffer* m_VertexBuffer{};
	ID3D11ShaderResourceView* m_Texture{};


	
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};

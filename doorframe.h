#pragma once
#include"model.h"
#include"gameobject.h"





class DoorFrame : public GameObject
{
private:

	float m_Threshold;

	Model* m_Model{};

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	
};


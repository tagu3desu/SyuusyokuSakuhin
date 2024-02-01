#pragma once
#include"gameobject.h"

class Staminagage :public GameObject
{
private:
	ID3D11Buffer* m_VertexBuffer = NULL;
	ID3D11ShaderResourceView* m_Texture = NULL;

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	float m_x = 230; //150
	float m_y = 40; //50
	float m_width = 690;
	float m_height = 8;

	int m_stamina;			//現在のスタミナポイント
	int m_staminaMax;		//最大スタミナポイント
	bool staminaheru=false;

public:
	int GetStamina() { return m_stamina;}
	void SetStaminaPoint(int stamina) { m_stamina += stamina; }

	void Init();
	void Uninit();
	void Update();
	void Draw();
};
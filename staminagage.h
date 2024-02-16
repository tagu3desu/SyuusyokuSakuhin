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

	float m_X = 230; //150
	float m_Y = 40; //50
	float m_Width = 690;
	float m_Height = 8;

	int m_Stamina;			//現在のスタミナポイント
	int m_StaminaMax;		//最大スタミナポイント
	bool m_StaminaDecrease =false;

public:
	int GetStamina() { return m_Stamina;}
	void SetStaminaPoint(int stamina) { m_Stamina += stamina; }

	void Init();
	void Uninit();
	void Update();
	void Draw();
};
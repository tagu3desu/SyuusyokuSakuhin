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

	int m_stamina;			//現在のヒットポイント
	int m_staminaMax;		//最大ヒットポイント
	bool staminaheru=false;

public:
	int GetStamina() { return m_stamina;}
	void SetStaminaPoint(int stamina) { m_stamina += stamina; }

	void Init();
	void Uninit();
	void Update();
	void Draw();
};
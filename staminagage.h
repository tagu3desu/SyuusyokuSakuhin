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

	float m_X = 250.0f;
	float m_Y = 40.0f;
	float m_Width = 1452.0f;
	float m_Height = 8.0f;

	int m_Stamina;			//現在のスタミナポイント
	int m_StaminaMax;		//最大スタミナポイント
	bool m_StaminaDecrease =false;

	bool m_ZeroStamina = false;

	class Scene* m_Scene;
	class Player* m_Player;
public:
	int GetStamina() { return m_Stamina;}
	void SetStaminaPoint(int stamina) { m_Stamina += stamina; }

	void SetStaminaGagePositoin(float x, float y) { m_X = x; m_Y = y; }
	void SetStaminaGageScale(float width,float height) { m_Width = width, m_Height = height;}

	void Init();
	void Uninit();
	void Update();
	void Draw();
};
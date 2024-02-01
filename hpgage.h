#pragma once
#include"gameobject.h"

class HPgage :public GameObject
{
private:
	ID3D11Buffer* m_VertexBuffer = NULL;
	ID3D11ShaderResourceView* m_Texture = NULL;

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	float m_x=230; //50
	float m_y=22; //25
	float m_width=690;
	float m_height=8;


	int m_hp;			//現在のヒットポイント
	int m_hpMax;		//最大ヒットポイント
	int m_befor_hp;		//前回のHP

public:
	int GetHp() { return m_hp; }
	void SetHealPoint(int Heal) { m_hp += Heal; m_befor_hp += Heal; }
	void SetDamage(int damage) { m_hp += damage;}
	void SetTexturePostion(float X, float Y) { X = m_x; Y = m_y; }
	void SetTextureScale(float width, float height) { m_width = width; m_height = height; }


	void Init();
	void Uninit();
	void Update();
	void Draw();
};
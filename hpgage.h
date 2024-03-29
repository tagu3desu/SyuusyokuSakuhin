#pragma once
#include"gameobject.h"

class HPgage :public GameObject
{
private:
	ID3D11Buffer* m_VertexBuffer = NULL;
	ID3D11ShaderResourceView* m_Texture = NULL;

	

	float m_X=250.0f; 
	float m_Y=22.0f;
	float m_Width=1452.0f;
	float m_Height=8.0f;


	int m_Hp;			//���݂̃q�b�g�|�C���g
	int m_HpMax;		//�ő�q�b�g�|�C���g
	int m_BeforHp;		//�O���HP

	class Scene* m_Scene;
	class Player* m_Player;
public:
	int GetHp() { return m_Hp; }
	void SetHealPoint(int Heal) { m_Hp += Heal; m_BeforHp += Heal; }
	void SetDamage(int damage) { m_Hp -= damage;}
	void SetHPGagePostion(float X, float Y) { m_X = X; m_Y = Y; }
	void SetHPGageScale(float width, float height) { m_Width = width; m_Height = height; }


	void Init();
	void Uninit();
	void Update();
	void Draw();
};
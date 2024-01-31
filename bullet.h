#pragma once
#include"gameobject.h"
#include"model.h"
enum BULLET_STATE
{
	BULLET_STATE_IDLE,
	BULLET_STATE_ATTACK
};


class Bullet :public GameObject
{
private:
	BULLET_STATE m_BulletState = BULLET_STATE_IDLE;


	static Model* m_Model;

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};
	
	
	float m_Idlecount{};
	

	D3DXVECTOR3 m_direction;
	float length;
	float m_FrameWait;
	float m_Period;
	float m_BulletLife;
	float m_MaxAccleration;
	bool hit;
public:
	static void Load();
	static void Unload();


	void Init();
	void Uninit();
	void Update();
	void Draw();

	void UpdateIdle();
	void UpdateAttack();
};
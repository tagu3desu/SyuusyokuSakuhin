#pragma once
#include"model.h"
#include"gameobject.h"
#include<string>
enum ENEMY2_STATE
{
	ENEMY2_STATE_GROUND,
	ENEMY2_STATE_ATTACK,
};

class Enemy2 : public GameObject
{
private:
	ENEMY2_STATE  m_EnemyState = ENEMY2_STATE_GROUND;

	static class AnimationModel* m_Model;
	

	//static Model* m_Model;
	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	float m_Threshold;

	D3DXVECTOR3 m_Velocity{};


	D3DXMATRIX m_Matrix{};
	float m_Time{};
	float m_BlendTime{};
	std::string m_AnimationName;
	std::string m_NextAnimationName;



	bool m_move = false;
	bool m_attack=false;
	bool m_guard=false;
	bool m_die = false;
public:
	static void Load();
	static void Unload();


	void Init();
	void Uninit();
	void Update();
	void Draw();

	void UpdateGround();
	void UpdateAttack();
};
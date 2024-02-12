#pragma once
#include"model.h"
#include"gameobject.h"
#include<string>
#include"animationModel.h"


enum ENEMY_STATE
{
	ENEMY_STATE_IDLE,
	ENEMY_STATE_MOVE,
	ENEMY_STATE_ATTACK,
	ENEMY_STATE_HOWL,
	ENAMY_STATE_DEAD
};


enum ENEMY_ATTACK_PATARN
{
	ENEMY_ATTACK_SLAP,
	ENEMY_ATTCK_ROCK
};
class Enemy : public GameObject
{
private:
	ENEMY_STATE  m_EnemyState = ENEMY_STATE_IDLE;
	ENEMY_ATTACK_PATARN m_EnemyAttackPatarn = ENEMY_ATTACK_SLAP;


	D3DXMATRIX m_ViewMatrix{};
	D3DXMATRIX m_ProjectionMatrix;

	

	//static Model* m_Model;
	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	float m_Threshold;


	D3DXVECTOR3 direction = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 sabun = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	class Audio* m_HowlSE{};

	//D3DXMATRIX m_Matrix{};
	float m_Time{};
	float m_BlendTime{};
	std::string m_AnimationName;
	std::string m_NextAnimationName;

	bool m_attack = false;
	bool m_howlfinish = false;
	bool m_howl = false;
	bool m_deadfinish = false;
	bool m_dead = false;
	bool m_find = false;
	bool m_move = false;
	bool m_shotflag = false;
	bool m_shotcount = 0;
	
	bool m_isdead = false;
	bool m_DeadmotionFinish=false;

	
	bool m_Attacking=false;

	bool m_RockAttackFlag=false;
	float m_Rockattacklimit{};

	int m_animationdelay = 0;
	int m_deadanimationdelay = 0;
	float groundHeight;
	float m_speed;

	int m_HP;

	int m_InvincibilityTime = 0;
	bool m_EnemyAttackHit = false;
	bool m_InvincibilityFlag=false;
	bool m_InviciblilityStartFlag = false;

	float length = 0;

	
	int m_randomNumber = 0;
	int m_attackdelay = 0;

	bool isAttack=false;

	D3DXMATRIX m_WorldMatrix{};
	D3DXVECTOR3 m_BonePos{};
	D3DXVECTOR3 m_BoneScale{};

	int hitcout;

	bool m_lastattackhit=false;
	int  m_lastattackcout;

	int  m_howlcount = 0;

	class Scene* scene{};
	class Collider* m_EnemyCollider{};
	class Collider* m_EnemyLightArmCollider{};

	bool m_EnemyAI = true;
	
public:
	static void Load();
	static void Unload();

	static class AnimationModel* m_Model;

	

	void Init();
	void Uninit();
	void Update();
	void Draw();
	//敵のステート
	void UpdateIdle();
	void UpdateMove();
	void UpdateAttack();
	void UpdateHowl();
	void UpdateDead();


	//敵の攻撃のパターン
	void UpdatePunchiAttack();
	void UpdateRockAttack();

	void SetDamage(int hp) { m_HP -= hp;}

	bool IsInFieldOfView(const D3DXVECTOR3& origin, D3DXVECTOR3& direction, float fieldOfViewRadians, float viewDistancee);
	bool GetEnemyHitPlayer() { return m_EnemyAttackHit;}
	

	void SetCollision(aiNode* node, aiMatrix4x4 matrix);

	AnimationModel* GetAnimationModel() { return m_Model; }
	//D3DXVECTOR3 GetForward() //前方面ベクトルを取得
	//{
	//	D3DXMATRIX rot;
	//	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);

	//	D3DXVECTOR3 forward;
	//	forward.x = rot._31;
	//	forward.y = rot._32;
	//	forward.z = rot._33;

	//	return forward;
	//}
};
#pragma once
#include"model.h"
#include"baseenemy.h"
#include<string>
#include"animationModel.h"


enum ENEMY_STATE
{
	ENEMY_STATE_IDLE,
	ENEMY_STATE_MOVE,
	ENEMY_STATE_ATTACK,
	ENEMY_STATE_HOWL,
	ENAMY_STATE_DEAD,
	ENEMY_STATE_LOITERING,
	ENEMY_STATE_REACTION
};


enum ENEMY_ATTACK_PATARN
{
	ENEMY_ATTACK_SLAP,
	ENEMY_ATTACK_PUNCH,
	ENEMY_ATTCK_JUMP
};
class Enemy : public BaseEnemy
{
private:
	ENEMY_STATE  m_EnemyState = ENEMY_STATE_IDLE;
	ENEMY_ATTACK_PATARN m_EnemyAttackPatarn = ENEMY_ATTACK_SLAP;


	D3DXMATRIX m_ViewMatrix{};
	D3DXMATRIX m_ProjectionMatrix;



	//ディゾルブ処理
	float m_Threshold;

	
	//アニメーション関連
	float m_Time=0.0f;
	float m_BlendTime=0.0f;
	std::string m_AnimationName;
	std::string m_NextAnimationName;
	int m_DeadAnimationdelay = 0;



	//アニメーション用フラグ
	bool m_IsAttack = false;
	bool m_HowlFinish = false;
	bool m_Howl = false;
	bool m_DeadFinish = false;
	bool m_Dead = false;
	bool m_Find = false;
	bool m_Walk = false;
	bool m_Run = false;
	float m_RockattackLimit{};
	int m_AnimationDelay = 0;
	bool m_HowlSEFlag=false;
	int m_DamageReactionDelay = 0;
	
	//移動関連
	D3DXVECTOR3 m_DirectionX = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 m_DirectionZ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//攻撃関連
	bool m_Attacking = false;
	bool m_Animating = false;
	bool m_PunchInvincibilityFlag = false;
	bool m_JumpInvincibilityFlag = false;
	bool m_PunchAttackFlag = false;
	bool m_JumpAttackFlag = false;
	int m_Attackdelay = 0;
	int m_HitCoolTime = 0;
	int m_AttackRandomNum = 0;

	//コライダー関連
	class BoxCollider* m_EnemyCollider{};
	class EnemyLeftArm* m_EnemyLeftArm;

	int m_InvincibilityTime = 0;
	bool m_JumpAttackHit = false;
	bool m_PunchAttackHit = false;
	bool m_InvincibilityFlag = false;
	bool m_InviciblilityStartFlag = false;

	//効果音
	class Audio* m_HowlSE{};
	class Audio* m_RockAttackSE{};
	class Audio* m_DeadSE{};
	bool m_DeadSEFlag = false;

	bool m_FootSoundFlag = false;
	int m_FootSoundInterval = 0;

	//ポインタ変数
	class Scene* m_Scene{};
	class EnemyAnimationCorrection* m_EnemyAnimationCorrection;
	
public:
	static void Load();
	static void Unload();

	
	static class AnimationModel* m_Model;

	bool GetDead() { return m_Dead;}

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
	void UpdateLoitering();
	void UpdateDamageReaction();

	//敵の攻撃のパターン
	void UpdateSlapAttack();
	void UpdatePunchAttack();
	void UpdateJumpAttack();

	bool GetEnemyHowlFinish() { return m_HowlFinish; };
	bool GetJumpAttackHit() { return m_JumpAttackHit; }
	bool GetPunchAttackHit() { return m_PunchAttackHit; }

	AnimationModel* GetAnimationModel() { return m_Model; }
	
};

class EnemyLeftArm : public GameObject
{
private:
	D3DXMATRIX m_Parent{};
	

	class Scene* m_Scene;
	class BoxCollider* m_LeftArmCollider;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};

class EnemyAnimationCorrection : public GameObject
{
private:
	D3DXMATRIX m_Parent{};
	D3DXVECTOR3 m_AnimationPosition;
	D3DXVECTOR3 m_DifferencePosition;
	D3DXVECTOR3 m_Oldposition;

	class Scene* m_Scene;
	class BoxCollider* test;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	D3DXVECTOR3 GetAnimationPosition() { return m_AnimationPosition; }
	D3DXVECTOR3 GetDifferencePosition() { return m_DifferencePosition; }
};
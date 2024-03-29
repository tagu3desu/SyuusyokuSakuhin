#pragma once
#include"model.h"
#include"gameobject.h"
#include<string>
#include"animationModel.h"
#include"baseenemy.h"


enum TUTORIAL_ENEMY_STATE
{
	TUTORIAL_ENEMY_STATE_IDLE,
	TUTORIAL_ENEMY_STATE_MOVE,
	TUTORIAL_ENEMY_STATE_ATTACK,
	TUTORIAL_ENEMY_STATE_HOWL,
	TUTORIAL_ENAMY_STATE_DEAD
};


enum TUTORIAL_ENEMY_ATTACK_PATARN
{
	TUTORIAL_ENEMY_ATTACK_PUNCH
};
class TutorialEnemy : public BaseEnemy
{
private:
	TUTORIAL_ENEMY_STATE  m_EnemyState = TUTORIAL_ENEMY_STATE_IDLE;
	TUTORIAL_ENEMY_ATTACK_PATARN m_EnemyAttackPatarn = TUTORIAL_ENEMY_ATTACK_PUNCH;


	D3DXMATRIX m_ViewMatrix{};
	D3DXMATRIX m_ProjectionMatrix;



	//�f�B�]���u����
	float m_Threshold;


	//�A�j���[�V�����֘A
	float m_Time=0.0f;
	float m_BlendTime=0.0f;
	std::string m_AnimationName;
	std::string m_NextAnimationName;
	int m_DeadAnimationdelay = 0;



	//�A�j���[�V�����p�t���O
	bool m_IsAttack = false;
	bool m_HowlFinish = false;
	bool m_Howl = false;
	bool m_DeadFinish = false;
	bool m_Dead = false;
	bool m_Find = false;
	bool m_Move = false;
	int m_AnimationDelay = 0;
	bool m_HowlSEFlag = false;


	//�U���֘A
	bool m_Attacking = false;
	bool m_Animating = false;
	int m_Attackdelay = 0;
	int m_HitCoolTime = 0;
	bool m_PunchInvincibilityFlag = false;
	bool m_PunchAttackFlag = false;

	//�R���C�_�[�֘A
	class BoxCollider* m_EnemyTutoriaCollider{};
	int m_InvincibilityTime = 0;
	bool m_PunchAttackHit = false;
	bool m_InvincibilityFlag = false;
	bool m_InviciblilityStartFlag = false;

	//���ʉ�
	class Audio* m_HowlSE{};
	class Audio* m_RockAttackSE{};
	class Audio* m_DeadSE{};
	bool m_DeadSEFlag = false;
	bool m_FootSoundFlag = false;
	int m_FootSoundInterval = 0;

	//�|�C���^�ϐ�
	class Scene* m_Scene{};
	class EnemyRightArm* m_EnemyRightArm;
public:
	static void Load();
	static void Unload();

	static class AnimationModel* m_Model;

	bool GetDead() { return m_Dead; }

	void Init();
	void Uninit();
	void Update();
	void Draw();
	//�G�̃X�e�[�g
	void UpdateIdle();
	void UpdateMove();
	void UpdateAttack();
	void UpdateHowl();
	void UpdateDead();


	//�G�̍U���̃p�^�[��
	void UpdatePunchAttack();
	
	bool GetEnemyHowlFinish() { return m_HowlFinish; };
	bool GetPunchAttackHit() { return m_PunchAttackHit; }

	AnimationModel* GetAnimationModel() { return m_Model; }

};

//�r�N���X
class EnemyRightArm : public GameObject
{
private:
	D3DXMATRIX m_Parent{};


	class Scene* m_Scene;
	class BoxCollider* m_RightArmCollider;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};


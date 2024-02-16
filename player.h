#pragma once

#include"model.h"
#include"gameobject.h"
#include<string>
#include"animationModel.h"


enum PLAYER_STATE
{
	PLAYER_STATE_GROUND,
	PLAYER_STATE_ATTACK,
	PLAYER_STATE_ATTACK2,
	PLAYER_STATE_ATTACK3,
	PLAYER_STATE_ROTATION_ATTACK,
	PLAYER_STATE_COUNTER_ATTACK,
	PLAYER_STATE_ROLL,
	PLAYER_STATE_DEAD,
	PLAYER_STATE_GUARD,
	PLAYER_STATE_TITLEIDLE,
};
class Player :public GameObject
{
private:
	PLAYER_STATE  m_PlayerState = PLAYER_STATE_GROUND;
	
	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	

	//ステータス
	int m_HP;
	int m_Stamina;
	int m_Potioncount;
	bool m_GameOver = false;

	//移動関連
	float m_Speed; 
	float m_GroundHeight = 0.0f;
	bool m_Move = false;
	bool m_IsGround{}; 
	bool m_Run = false;
	bool m_Walk = false;
	D3DXVECTOR3 m_DirectionX;
	D3DXVECTOR3 m_DirectionZ;
	D3DXVECTOR3 m_Velocity{};

	//アニメーション関連
	float m_Time{};
	float m_BlendTime{};
	std::string m_AnimationName;
	std::string m_NextAnimationName;
	float m_AnimationDelay;
	int m_HitInpactDelay;

	//アニメーション用フラグ
	bool m_Idle = false;
	bool m_Roll = false;
	bool m_StartGuard = false;
	bool m_IsGuard = false;
	bool m_EndGuard = false;
	bool m_InpactGuard = false;
	bool m_SuccessGuard = false;
	bool m_HitInpact = false;

	//攻撃関連
	bool m_Attack = false;
	int m_ComboCount{}; 
	bool m_Sworddrawn = false;
	bool m_OnSword = false;
	bool m_OffSword = false;
	//ヒットストップ関連
	bool m_HitStopFlag = false;
	float m_HitStopTime = false;
	//コンボ関連　
	bool m_AttackMotion1 = false;
	bool m_ConboflagisAttack2 = false;
	bool m_AttackMotion2 = false;
	bool m_ConboflagisAttack3 = false;

	//コライダー
	class Collider* m_PlayerCollider{};
	bool m_AttackCollisionFlag = false;
	
	//カメラ制御
	D3DXVECTOR3 m_CameraFoward;
	D3DXVECTOR3 m_CameraRight;

	//当たり判定用
	bool m_PlayerHitEnemy = false;
	bool m_Rockhit = false;
	bool m_DamageReaction = false;

	//サウンド処理
	class Audio* m_OnWeponSE{};
	class Audio* m_OffWeponSE{};
	class Audio* m_RunSoundBGM{};
	class Audio* m_WalkSoundBGM{};
	class Audio* m_AttackSE{};

	//ポインタ変数
	class Scene* m_Scene{};
	class AnimationModel* m_Model{};
	class Title* m_Title;
	class Camera* m_Camera;
	class Enemy* m_Enemy;
	class MeshField* m_MeshField;
	class RockEffect* m_RockEffect;
	class Bullet* m_Bullet;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void UpdateGround();
	void UpdateAttack();
	void UpdateAttack2();
	void UpdateAttack3();
	void UpdateRotationAttack();
	void UpdateCounterAttack();
	void UpdateRoll();
	void UpdateDead();
	void UpdateGuard();
	void UpdateTitleIdle();

	int GetPlayerAttackNumber() { return m_ComboCount; }
	bool GetOverFlag() { return m_GameOver; }
	bool GeiPlayerIdle() { return m_Idle; }
	bool GetSwordDrawn() { return m_Sworddrawn; }
	bool GetPlayerHitEnemy() { return m_PlayerHitEnemy; }
	bool GetPlayerAttack() { return m_Attack; }
	bool GetSuccessGuard() { return m_SuccessGuard; }
	bool GetPlayerRun() { return m_Run; }
	bool GetPlayerIdle(){return m_Idle;}
	bool GetPlayerAttackCollider() { return m_AttackCollisionFlag; }
	bool GetHitStopFlag() { return m_HitStopFlag; }

	void SetHitStop(bool hitstopflag){m_HitStopFlag = hitstopflag;}

	void SetHitStopTime(float hitstoptime)
	{
		m_HitStopTime++;
		if (hitstoptime <= m_HitStopTime)
		{
			m_HitStopTime = 0.0f;
			m_HitStopFlag = false;
		}
	}

	D3DXVECTOR3 GetForward()//前方面ベクトルを取得
	{
		D3DXMATRIX rot;
		D3DXMatrixRotationQuaternion(&rot, &m_Quaternion);

		D3DXVECTOR3 forward;
		forward.x = rot._31;
		forward.y = rot._32;
		forward.z = rot._33;

		return forward;
	}

	D3DXVECTOR3 GetRight() //右方面ベクトルを取得
	{
		D3DXMATRIX rot;
		D3DXMatrixRotationQuaternion(&rot, &m_Quaternion);

		D3DXVECTOR3 right;
		right.x = rot._11;
		right.y = rot._12;
		right.z = rot._13;

		return right;
	}

	D3DXVECTOR3 GetEulerForward() //右方面ベクトルを取得
	{
		D3DXMATRIX euler;
		D3DXMatrixRotationYawPitchRoll(&euler, m_Rotation.y, m_Rotation.x, m_Rotation.z);

		D3DXVECTOR3 forward;
		forward.x = euler._31;
		forward.y = euler._32;
		forward.z = euler._33;

		return forward;
	}


	D3DXVECTOR3 GetEulerRight() //右方面ベクトルを取得
	{
		D3DXMATRIX euler;
		D3DXMatrixRotationYawPitchRoll(&euler, m_Rotation.y, m_Rotation.x, m_Rotation.z);

		D3DXVECTOR3 right;
		right.x = euler._11;
		right.y = euler._12;
		right.z = euler._13;

		return right;
	}

	AnimationModel* GetAnimationModel() { return m_Model; }
	PLAYER_STATE GetPlayerState() { return m_PlayerState; }
};


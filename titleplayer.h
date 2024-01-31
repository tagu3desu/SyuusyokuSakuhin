#pragma once

#include"model.h"
#include"gameobject.h"
#include<string>
#include"animationModel.h"


enum TITLEPLAYER_STATE
{
	TITLEPLAYER_STATE_GROUND,	
};
class TitlePlayer :public GameObject
{
private:
	bool m_sworddrawn = false;


	TITLEPLAYER_STATE  m_PlayerState = TITLEPLAYER_STATE_GROUND;
	bool m_IsGround{};

	//Model* m_Model{};


	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	int m_comboCount{};


	float m_speed; //移動速度

	D3DXVECTOR3 m_Velocity{};


	class Shadow* m_Shadow{};


	float m_Time{};
	float m_BlendTime{};
	std::string m_AnimationName;
	std::string m_NextAnimationName;

	bool m_AttackMotion{};
	float m_AnimationDelay;

	bool m_attack = false;
	bool m_move = false;
	bool m_run = false;
	bool m_guard = false;
	bool m_isDead = false;
	bool m_roll = false;
	bool m_onSword = false;
	bool m_offSword = false;

	bool m_idle = false;
	



	D3DXVECTOR3 directionX;
	D3DXVECTOR3 directionZ;

	bool m_attackNow = false;

	//カメラ制御
	D3DXVECTOR3 cameraFoward;
	D3DXVECTOR3 cameraRight;


	D3DXVECTOR3 direction;
	float length = 0;

	D3DXMATRIX m_WorldMatrix{};
	D3DXVECTOR3 m_BonePos{};
	D3DXVECTOR3 m_BoneScale{};

	int  m_ConboNumber;
	bool m_fainalAttack = false;

	int m_HP;

	int m_potioncount;
	int m_Stamina;

	//当たり判定用
	int m_InvincibilityTime = 0;
	bool m_PlayerHitEnemy = false;
	bool m_InvincibilityFlag = false;
	bool m_InviciblilityStartFlag = false;

	int hitcount = 0;
	//サウンド処理
	class Audio* m_OnWeponSE{};
	class Audio* m_OffWeponSE{};
	class Audio* m_RunSoundBGM{};
	class Audio* m_WalkSoundBGM{};
	class Audio* m_AttackSE{};


	class AnimationModel* m_Model{};
public:



	void Init();
	void Uninit();
	void Update();
	void Draw();



	void UpdateGround();


	bool GeiPlayerIdle() { return m_idle; }
	bool GetSwordDrawn() { return m_sworddrawn; }
	bool GetPlayerAttack() { return m_attack; }
	bool GetPlayerRun() { return m_run; }
	bool GetPlayerIdle(){return m_idle;}


	//D3DXMATRIX GetMatrix() { return m_Matrix;}
	TITLEPLAYER_STATE GetPlayerState() { return m_PlayerState;}

	D3DXVECTOR3 GetBonePosition() { return m_BonePos;}
	D3DXVECTOR3 GetBoneScale() { return m_BoneScale; }


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

	

	void SetCollision(aiNode* node, aiMatrix4x4 matrix);

	//void SetCollision(aiNode* node, aiMatrix4x4 matrix, std::string RigName);


	AnimationModel* GetAnimationModel() { return m_Model; }
};


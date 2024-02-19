#pragma once

#include"gameobject.h"

class Camera :public GameObject
{
private:

		D3DXVECTOR3 m_CorrectTarget{};
		D3DXVECTOR3 m_CorrectPosition{};

		D3DXVECTOR3 m_Target{};
		D3DXMATRIX m_ViewMatrix{};
		D3DXMATRIX m_ProjectionMatrix;

		float m_RotationX{};
		float m_RotationY{};

		float m_EnemyCameraRotationY{};
		float m_EnemyCameraRotationX{};
		float m_DeathCamera{};

		float m_ShakeAmplitude{};
		int   m_ShakeTime{};
		float m_ShakeOffset{};


		float m_FogStart;
		float m_FogEnd;
		float m_FogHeight;

		class Scene* m_Scene;


public:
	void Init();
	void Update();
	void Draw();

	D3DXMATRIX GetViewMatrix() { return m_ViewMatrix; }
	bool CheckView(D3DXVECTOR3 Position);

	D3DXVECTOR3 GetForward() //前方面ベクトルを取得
	{
		D3DXMATRIX rot;
		D3DXMatrixInverse(&rot, nullptr, &m_ViewMatrix);



		D3DXVECTOR3 forward;
		forward.x = rot._31;
		forward.y = rot._32;
		forward.z = rot._33;

		return forward;
	}
	
	D3DXVECTOR3 GetRight() //前方面ベクトルを取得
	{
		D3DXMATRIX rot;
		D3DXMatrixInverse(&rot, nullptr, &m_ViewMatrix);

		D3DXVECTOR3 right;
		right.x = rot._11;
		right.y = rot._12;
		right.z = rot._13;

		return right;
	}

	void Shake(float Amplitude)
	{
		m_ShakeAmplitude = Amplitude;
	}
};
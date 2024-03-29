#include"gameobject.h"
class BaseEnemy : public GameObject
{
protected:
	//ステータス
	int m_HP;
	int m_DamageTakeCount;
	float m_GroundHeight = 0.0f;
	float m_Speed = 0.0f;

	//視野
	D3DXVECTOR3 m_Direction = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	float m_Length = 0;

	//敵AI
	bool m_EnemyAI = true;

public:

	void SetDamage(int hp) { m_HP -= hp; }
	void SetEnemyAI(bool ai) { m_EnemyAI = ai; }
	bool GetEnemyAI() { return m_EnemyAI; }

	int GetHP() { return m_HP; }


	//視野に入ってるか判別
	bool IsInFieldOfView(const D3DXVECTOR3& origin, D3DXVECTOR3& direction, float fieldOfViewRadians, float viewDistancee,GameObject* target ){
		// 視野範囲内かどうかの判定
		D3DXVECTOR3 normalizedDirection;
		D3DXVec3Normalize(&normalizedDirection, &direction);
		D3DXVECTOR3 houkou = GetForward();
		float dotProduct = D3DXVec3Dot(&houkou, &normalizedDirection);
		float angle = acos(dotProduct);
		fieldOfViewRadians = D3DXToRadian(fieldOfViewRadians);
		bool isInFieldOfView = angle <= fieldOfViewRadians / 2.0f;

		// 視野距離内かどうかの判定
		D3DXVECTOR3 dice = origin - target->GetPosition();
		float distance = D3DXVec3Length(&dice);
		bool isInViewDistance = distance <= viewDistancee;

		return isInFieldOfView && isInViewDistance;
	};

};
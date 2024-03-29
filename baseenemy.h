#include"gameobject.h"
class BaseEnemy : public GameObject
{
protected:
	//�X�e�[�^�X
	int m_HP;
	int m_DamageTakeCount;
	float m_GroundHeight = 0.0f;
	float m_Speed = 0.0f;

	//����
	D3DXVECTOR3 m_Direction = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	float m_Length = 0;

	//�GAI
	bool m_EnemyAI = true;

public:

	void SetDamage(int hp) { m_HP -= hp; }
	void SetEnemyAI(bool ai) { m_EnemyAI = ai; }
	bool GetEnemyAI() { return m_EnemyAI; }

	int GetHP() { return m_HP; }


	//����ɓ����Ă邩����
	bool IsInFieldOfView(const D3DXVECTOR3& origin, D3DXVECTOR3& direction, float fieldOfViewRadians, float viewDistancee,GameObject* target ){
		// ����͈͓����ǂ����̔���
		D3DXVECTOR3 normalizedDirection;
		D3DXVec3Normalize(&normalizedDirection, &direction);
		D3DXVECTOR3 houkou = GetForward();
		float dotProduct = D3DXVec3Dot(&houkou, &normalizedDirection);
		float angle = acos(dotProduct);
		fieldOfViewRadians = D3DXToRadian(fieldOfViewRadians);
		bool isInFieldOfView = angle <= fieldOfViewRadians / 2.0f;

		// ���싗�������ǂ����̔���
		D3DXVECTOR3 dice = origin - target->GetPosition();
		float distance = D3DXVec3Length(&dice);
		bool isInViewDistance = distance <= viewDistancee;

		return isInFieldOfView && isInViewDistance;
	};

};
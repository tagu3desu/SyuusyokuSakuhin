#pragma once
#include"main.h"
#include"model.h"
#include"gameobject.h"

enum Tag
{
	PLAYER_TAG,
	ENEMY_TAG,
	ITEM_TAG,
	BGOBJ_TAG
};


class Collider : public GameObject
{
private:
	static Model* m_Model;

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	D3DXMATRIX m_Parent{};

	D3DXCOLOR m_ColliderColor{ 0.0f, 1.0f, 0.0f, 1.0f };

	//D3DXVECTOR3 m_ColliderScale{};
	//D3DXVECTOR3 m_ColliderPosition{};
	
	Tag m_Tag = BGOBJ_TAG;

	/*D3DXVECTOR3 m_ColliderScale{};
	D3DXVECTOR3 m_ColliderPosition{};
	D3DXVECTOR3 m_ColiiderRight{};
	D3DXVECTOR3 m_ColiiderForward{};
	D3DXVECTOR3 m_ColiiderUp{};*/

public:
	D3DXVECTOR3 MatrixtoPosition(D3DXMATRIX matrix) {
		D3DXVECTOR3 pos;
		pos.x = matrix._41;
		pos.y = matrix._42;
		pos.z = matrix._43;
		return pos;
	}

	D3DXVECTOR3 MatrixtoScale(D3DXMATRIX matrix) {
		D3DXVECTOR3 scale;
		scale.x = matrix._11;
		scale.y = matrix._22;
		scale.z = matrix._33;
		return scale;
	}

	//D3DXVECTOR3 GetCForward() //前方面ベクトルを取得
	//{
	//	D3DXMATRIX rot;
	//	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);

	//	D3DXVECTOR3 forward;
	//	forward.x = rot._31;
	//	forward.y = rot._32;
	//	forward.z = rot._33;

	//	return forward;
	//}

	D3DXVECTOR3 MatrixtoForward(D3DXMATRIX matrix) //前方面ベクトルを取得
	{
		D3DXVECTOR3 forward;
		forward.x = matrix._31;
		forward.y = matrix._32;
		forward.z = matrix._33;

		return forward;
	}


	//D3DXVECTOR3 GetCRight() //右方面ベクトルを取得
	//{
	//	D3DXMATRIX rot;
	//	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);

	//	D3DXVECTOR3 right;
	//	right.x = rot._11;
	//	right.y = rot._12;
	//	right.z = rot._13;

	//	return right;
	//}

	D3DXVECTOR3 MatrixtoRight(D3DXMATRIX matrix) //右方面ベクトルを取得
	{
		
		D3DXVECTOR3 right;
		right.x = matrix._11;
		right.y = matrix._12;
		right.z = matrix._13;

		return right;
	}

	//D3DXVECTOR3 GetCUp() //上方面ベクトル
	//{
	//	D3DXMATRIX rot;
	//	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);

	//	D3DXVECTOR3 up;
	//	up.x = rot._21;
	//	up.y = rot._22;
	//	up.z = rot._23;

	//	return up;
	//}

	D3DXVECTOR3 MatrixtoUp(D3DXMATRIX matrix) //上方面ベクトル
	{
		
		D3DXVECTOR3 up;
		up.x = matrix._21;
		up.y = matrix._22;
		up.z = matrix._23;

		return up;
	}

	static void Load();
	static void Unload();

	void Init();
	void Uninit();
	void Update();
	void Draw();
	void SetMatrix(D3DXMATRIX matrix) { m_Parent = matrix; }
	void SetColliderColor(D3DXCOLOR color) { m_ColliderColor = color; }

	void SetTag(Tag tag) { m_Tag = tag;}
	Tag GetTag() { return m_Tag; }


	/*D3DXVECTOR3 GetColliderScale() { return  m_ColliderScale; }
	D3DXVECTOR3 GetColliderPosition() { return m_ColliderPosition; }
	D3DXVECTOR3 GetColliderUp() { return m_ColiiderUp; }
	D3DXVECTOR3 GetColliderRight() { return m_ColiiderRight; }
	D3DXVECTOR3 GetColliderForward() { return m_ColiiderForward; }*/

	//template<typename C1,typename C2>
	//C1* CheckCollidionHit(LAYER layer1 = COLLIDER_LAYER, LAYER layer2 = COLLIDER_LAYER)
	//{
	//	C1* gameObject1;
	//	C2* gameObject2;
	//	m_ColliderObject[layer1].push_back(gameObject1);
	//	m_ColliderObject[layer2].push_back(gameObject2);
	//	
	//	D3DXVECTOR3 objectposition1 = gameObject1->GetGameObject();
	//	D3DXVECTOR3 objectposition2 = gameObject2->GetGameObject();
	//}

	//template<typename C1, typename C2>
	//bool CheckCollisionHit(LAYER layer1 = COLLIDER_LAYER, LAYER layer2 = COLLIDER_LAYER) {
	//	std::vector<C1*> colliderObjects1 = m_ColliderObject[layer1];
	//	std::vector<C2*> colliderObjects2 = m_ColliderObject[layer2];
	//	bool hitflag;
	//	for (C1* gameObject1 : colliderObjects1) {
	//		for (C2* gameObject2 : colliderObjects2) {
	//			// 衝突をチェックする処理を実装
	//			D3DXVECTOR3 objectPosition1 = gameObject1->GetPosition();
	//			D3DXVECTOR3 objectPosition2 = gameObject2->GetPosition();

	//			D3DXVECTOR3 scale1 = gameObject1->GetScale();
	//			D3DXVECTOR3 scale2 = gameObject2->GetScale();

	//			D3DXVECTOR3 right1 = gameObject1->GetRight();
	//			D3DXVECTOR3 right2 = gameObject2->GetRight();

	//			D3DXVECTOR3 forward1 = gameObject1->GetForward();
	//			D3DXVECTOR3 forward2 = gameObject2->GetForward();

	//			D3DXVECTOR3 up1 = gameObject1->GetUp();
	//			D3DXVECTOR3 up2 = gameObject2->GetUp();

	//			D3DXVECTOR3 direction = objectPosition1 - objectPosition2;

	//			float obbx1 = D3DXVec3Dot(&direction, &right1);
	//			float obbx2 = D3DXVec3Dot(&direction, &right2);

	//			float obbz1 = D3DXVec3Dot(&direction, &forward1);
	//			float obbz2 = D3DXVec3Dot(&direction, &forward2);

	//			
	//			if (fabs(obbx2) < fabs(obbx1) && fabs(obbz2) < fabs(obbz2))
	//			{
	//				/*if (objectPosition1.y < objectPosition2.y + scale2.y * 2.0f)
	//				{


	//				}*/
	//				hitflag = true;
	//			}
	//			else
	//			{
	//				hitflag = false;
	//			}


	//			// ここに衝突をチェックする処理を実装
	//		}
	//	}
	//	return hitflag;
	//}

};


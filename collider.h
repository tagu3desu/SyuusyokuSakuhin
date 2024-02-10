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

	D3DXVECTOR3 m_ScaleOffset{};
	D3DXMATRIX m_Parent{};

	D3DXMATRIX m_BoneMatrix{};

	D3DXCOLOR m_ColliderColor{ 0.0f, 1.0f, 0.0f, 1.0f };
	
	Tag m_Tag = BGOBJ_TAG;


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


	D3DXVECTOR3 MatrixtoForward(D3DXMATRIX matrix) //前方面ベクトルを取得
	{
		D3DXVECTOR3 forward;
		forward.x = matrix._31;
		forward.y = matrix._32;
		forward.z = matrix._33;

		return forward;
	}

	D3DXVECTOR3 MatrixtoRight(D3DXMATRIX matrix) //右方面ベクトルを取得
	{
		
		D3DXVECTOR3 right;
		right.x = matrix._11;
		right.y = matrix._12;
		right.z = matrix._13;

		return right;
	}


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
	void SetBoneMatrix(D3DXMATRIX bonematrix) { m_BoneMatrix = bonematrix;}
	void SetColliderColor(D3DXCOLOR color) { m_ColliderColor = color; }

	void SetTag(Tag tag) { m_Tag = tag;}
	Tag GetTag() { return m_Tag; }


	bool CollisionChecker(GameObject* obb1, GameObject* obb2 , float offsetscale);
	float LenSegOnSeparateAxis(D3DXVECTOR3* Sep, D3DXVECTOR3* e1, D3DXVECTOR3* e2, D3DXVECTOR3* e3);

};


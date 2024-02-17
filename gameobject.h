#pragma once
#include <list>
#include"main.h"
#include"renderer.h"
#include"compornent.h"
class GameObject
{
protected:
	bool m_Destroy = false;

	D3DXVECTOR3 m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	D3DXVECTOR3 m_MoveSpeed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 m_MoveVector = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 m_Velocity = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	D3DXQUATERNION m_Quaternion = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);

	std::list<Component*> m_Component;	//STLのリスト構造

	D3DXMATRIX m_Matrix{};

	ID3D11ShaderResourceView* m_TextureEnv = NULL;
	ID3D11ShaderResourceView* m_TextureEnvCube = NULL;
	ID3D11ShaderResourceView* m_DisolveTexture = NULL;

	float m_Threshold; //ディゾルブ処理

	bool m_DepthEnable=false;
	bool m_ReflectEnable = false;
	bool m_DissolveEnable=false;

	D3DXCOLOR m_ModelRimColor{ 0.0f, 0.0f, 0.0f, 1.0f };

	D3DXVECTOR3 m_ColliderScale{};
	D3DXVECTOR3 m_ColliderPosition{};
	D3DXVECTOR3 m_ColiiderRight{};
	D3DXVECTOR3 m_ColiiderForward{};
	D3DXVECTOR3 m_ColiiderUp{};

	bool m_BoneEnable{};

	int m_InvincibilityTime = 0;
	bool m_InvincibilityFlag = false;
	bool m_InviciblilityStartFlag = false;

	float m_FrameWait{};

	bool m_Hit{};
public:
	bool GetReflectEnable() { return m_ReflectEnable; }
	bool GetDepthEnable() { return m_DepthEnable; }
	void SetDestroy() { m_Destroy = true; }
	void SetPosition(D3DXVECTOR3 Position) { m_Position = Position; }
	void SetRotation(D3DXVECTOR3 Rotation) { m_Rotation = Rotation; }
	void SetScale(D3DXVECTOR3 Scale) { m_Scale = Scale; };
	void SetScalePosition(D3DXVECTOR3  Scale, D3DXVECTOR3 Position) { m_Scale = Scale; m_Position = Position;}
	void SetVelocity(D3DXVECTOR3 velocity) { m_Velocity = velocity; }
	void SetQuaternion(D3DXQUATERNION quaternion) { m_Quaternion = quaternion; }

	D3DXVECTOR3 GetColliderScale() { return m_ColliderScale; }
	D3DXVECTOR3 GetColliderPosition() { return m_ColliderPosition; }
	D3DXVECTOR3 GetColliderRight() { return m_ColiiderRight; }
	D3DXVECTOR3 GetColliderForward() { return m_ColiiderForward; }
	D3DXVECTOR3 GetColliderUp() { return m_ColiiderUp; }

	GameObject* ParentMatrix;
	D3DXMATRIX GetMatrix() { return m_Matrix; }

	bool GetHit() { return m_Hit; }

	bool Destroy()
	{
		if (m_Destroy)
		{
			Uninit();
			delete this;
			return true;
		}
		else
		{
			return false;
		}
	}
			
	void SetColliderInfo(D3DXMATRIX matrix , bool boneEnable)
	{
		m_BoneEnable = boneEnable;
		m_ColliderScale = MatrixtoScale(matrix) ;
		m_ColliderPosition = MatrixtoPosition(matrix);
		m_ColiiderRight = MatrixtoRight(matrix);
		m_ColiiderForward = MatrixtoForward(matrix);
		m_ColiiderUp = MatrixtoUp(matrix);
	}
		
	D3DXVECTOR3 GetPosition()
	{
		return   m_Position;
	}

	D3DXVECTOR3 GetScale()
	{
		return m_Scale;
	}

	D3DXVECTOR3 GetForward() //前方面ベクトルを取得
	{
		D3DXMATRIX rot;
		D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);

		D3DXVECTOR3 forward;
		forward.x = rot._31;
		forward.y = rot._32;
		forward.z = rot._33;

		return forward;
	}

	D3DXVECTOR3 GetRight() //右方面ベクトルを取得
	{
		D3DXMATRIX rot;
		D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);

		D3DXVECTOR3 right;
		right.x = rot._11;
		right.y = rot._12;
		right.z = rot._13;

		return right;
	}

	D3DXVECTOR3 GetUp()
	{
		D3DXMATRIX rot;
		D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);

		D3DXVECTOR3 up;
		up.x = rot._21;
		up.y = rot._22;
		up.z = rot._23;

		return up;
	}

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



	VERTEX_3D ConvertD3DXVECTOR3ToVERTEX3D(const D3DXVECTOR3& vector3) {
		VERTEX_3D result;
		result.Position = vector3;
		return result;
	}

	virtual void Init() {
		// テクスチャ読み込み
		D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
			"asset/texture/dissolve.png",
			NULL,
			NULL,
			&m_DisolveTexture,
			NULL);
		assert(m_DisolveTexture);
	};
	virtual void Uninit() 
	{
		for (Component* component : m_Component)
		{
			component->Uninit();
			delete component;
		}
		
		m_Component.clear();
	};
	virtual void Update() 
	{
		for (Component* component : m_Component)
		{

			if (component != nullptr)
			{
				component->Update();
			}
		}
	};
	virtual void Draw() 
	{
		if (m_DepthEnable)
		{
			// テクスチャ設定
			ID3D11ShaderResourceView* depthShadowTexture = Renderer::GetDepthShadowTexture();
			Renderer::GetDeviceContext()->PSSetShaderResources(1, 1, &depthShadowTexture);
		}
		
		if (m_DissolveEnable)
		{
			// テクスチャ設定
			Renderer::GetDeviceContext()->PSSetShaderResources(1, 1, &m_DisolveTexture);
		}
		
		if(m_ReflectEnable)
		{
			Renderer::GetDeviceContext()->PSSetShaderResources(2, 1, Renderer::GetCubeReflectShaderResourceView());
		}

		for (Component* component : m_Component)
		{
			if (component != nullptr)
			{
				component->Draw();
			}
			
		}
	};

	template <typename T>	//テンプレート関数
	T* AddComponent()
	{
		Component* component = new T();
		m_Component.push_back(component);	//リスト構造に追加
		component->Init();

		return (T*)component;
	}


};


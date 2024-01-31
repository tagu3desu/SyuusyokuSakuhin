
#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include "component.h"
#include <list>
#include "main.h"
class GameObject
{
protected:
	bool		m_Destroy = false;

	D3DXVECTOR3 m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXMATRIX world;
	D3DXVECTOR3 m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	std::list<Component*> m_Component;//STLのリスト構造

public:

	GameObject* ParentMatrix;
	D3DXMATRIX GetMatrix() { return world; }
	void SetDestroy() { m_Destroy = true; }

	bool Destroy()
	{
		if (m_Destroy)
		{
			Uninit();
			delete this;
			return this;
		}
		else
		{
			return false;
		}
	}

	void SetPosition(D3DXVECTOR3 position) { m_Position = position; }
	void SetScale(D3DXVECTOR3 scale) { m_Scale = scale; }
	D3DXVECTOR3 GetPosition() { return m_Position; }
	D3DXVECTOR3 GetScale() { return m_Scale; }

	D3DXVECTOR3 GetForward() //前方向のベクトル取得
	{
		D3DXMATRIX rot;
		D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);

		D3DXVECTOR3 forward;
		forward.x = rot._31;
		forward.y = rot._32;
		forward.z = rot._33;

		return forward;
	}
	D3DXVECTOR3 GetRight()//右方向のベクトル取得
	{
		D3DXMATRIX rot;
		D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);

		D3DXVECTOR3 forward;
		forward.x = rot._11;
		forward.y = rot._12;
		forward.z = rot._13;

		return forward;

	}


	virtual void Init()
	{

	}
	virtual void Uninit()
	{
		for (Component* component : m_Component)
		{
			component->Uninit();
			delete component;
		}
	}
	virtual void Update()
 	{
		for (Component* component : m_Component)
		{
			component->Update();
		}

	}
	virtual void Draw()
	{
		for (Component* component : m_Component)
		{
			component->Draw();
		}

	}

	template <typename T>
	T* AddComponent()
	{
		Component* component = new T();
		m_Component.push_back(component);
		component->Init();

		return (T*)component;
	}

	template <typename T>//テンプレート関数
	T* GetComponent()
	{
			for (Component* gameObject : m_Component)
			{
				if (typeid(*gameObject) == typeid(T))//型を調べる(RTTI動的型情報)
				{
					return (T*)gameObject;
				}
			}
		return nullptr;
	}

};

#endif // !_GameObject_H_
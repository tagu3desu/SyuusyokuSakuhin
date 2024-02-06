#pragma once
#include"main.h"
#include"model.h"
#include"gameobject.h"




class Collider : public GameObject
{
private:
	static Model* m_Model;

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	D3DXMATRIX m_Parent{};

	D3DXCOLOR m_ColliderColor{0.0f,1.0f,0.0f,0.0f};

	
	
	

	
public:
	D3DXVECTOR3 ExtractTranslationFromMatrix(D3DXMATRIX matrix) {
		D3DXVECTOR3 pos;
		pos.x = matrix._41;
		pos.y = matrix._42;
		pos.z = matrix._43;
		return pos;
	}

	static void Load();
	static void Unload();

	void Init();
	void Uninit();
	void Update();
	void Draw();
	void SetMatrix(D3DXMATRIX matrix) { m_Parent = matrix; }
	void SetColliderColor(D3DXCOLOR color) { m_ColliderColor = color; }
};


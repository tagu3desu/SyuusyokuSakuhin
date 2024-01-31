#pragma once
#include"compornent.h"
#include "gameObject.h"
#include "main.h"
#include "assimp/matrix4x4.h"

class BoxCollider : public GameObject
{
private:
	class Model* m_Model;	//1ŒÂ‚Ì‚Ý

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};


	
public:
	D3DXMATRIX boneMatrix{};
	bool boneEnable = false;
	D3DXVECTOR3 GlobalPosition{};

	float m_collisionSize;

	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

};

class BoxComponent :public Component
{
private:
	float size;
public:
	BoxCollider* collider;

	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
};

//class MATH
//{
//public:
//	static D3DXMATRIX MatrixConvert(aiMatrix4x4 aiMatrix)
//	{
//		D3DXMATRIX fuse;
//
//		fuse._11 = aiMatrix.a1;
//		fuse._12 = aiMatrix.b1;
//		fuse._13 = aiMatrix.c1;
//		fuse._14 = aiMatrix.d1;
//
//		fuse._21 = aiMatrix.a2;
//		fuse._22 = aiMatrix.b2;
//		fuse._23 = aiMatrix.c2;
//		fuse._24 = aiMatrix.d2;
//
//		fuse._31 = aiMatrix.a3;
//		fuse._32 = aiMatrix.b3;
//		fuse._33 = aiMatrix.c3;
//		fuse._34 = aiMatrix.d3;
//
//		fuse._41 = aiMatrix.a4;
//		fuse._42 = aiMatrix.b4;
//		fuse._43 = aiMatrix.c4;
//		fuse._44 = aiMatrix.d4;
//
//
//		return fuse;
//	}
//};
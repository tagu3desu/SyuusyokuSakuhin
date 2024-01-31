#pragma once

#include <unordered_map>

#include "assimp/cimport.h"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "assimp/matrix4x4.h"
#pragma comment (lib, "assimp-vc143-mt.lib")


//変形後頂点構造体
struct DEFORM_VERTEX
{
	aiVector3D Position;
	aiVector3D Normal;
	int				BoneNum;
	std::string		BoneName[4];//本来はボーンインデックスで管理するべき
	float			BoneWeight[4];
};

//ボーン構造体
struct BONE
{
	aiMatrix4x4 Matrix;
	aiMatrix4x4 AnimationMatrix;
	aiMatrix4x4 CollitionMatrix;
	aiMatrix4x4 OffsetMatrix;
	aiMatrix4x4 WorldMatrix;
};

class AnimationModel
{
private:
	const aiScene* m_AiScene = nullptr;
	std::unordered_map<std::string, const aiScene*> m_Animation;

	ID3D11Buffer**	m_VertexBuffer;
	ID3D11Buffer**	m_IndexBuffer;

	std::unordered_map<std::string, ID3D11ShaderResourceView*> m_Texture;

	std::vector<DEFORM_VERTEX>* m_DeformVertex;//変形後頂点データ
	std::unordered_map<std::string, BONE> m_Bone;//ボーンデータ（名前で参照）

	void CreateBone(aiNode* Node);
	void UpdateBoneMatrix(aiNode* Node, aiMatrix4x4 Matrix);

	bool m_EnemyFlg = false;
	bool m_PlayerFlg = false;

	
	
	aiMatrix4x4 m_WorldMatrix;

	std::string m_FileName;
public:
	void Load( const char *FileName );
	void LoadAnimation( const char *FileName, const char *Name );
	void Unload();

	void Update(const char *AnimationName1, int Frame1, const char* AnimationName2,int Frame2,float BlendRate);
	void Draw();

	bool over;
	
	aiMatrix4x4 GetMatrix() { return m_WorldMatrix; }

	BONE* GetBone(const char* bone) { return &m_Bone[bone];}

	D3DXMATRIX  ConvertMatrix(aiMatrix4x4 aiMatrix)
	{
		D3DXMATRIX convermatrix;
		convermatrix._11 = aiMatrix.a1;
		convermatrix._12 = aiMatrix.b1;
		convermatrix._13 = aiMatrix.c1;
		convermatrix._14 = aiMatrix.d1;

		convermatrix._21 = aiMatrix.a2;
		convermatrix._22 = aiMatrix.b2;
		convermatrix._23 = aiMatrix.c2;
		convermatrix._24 = aiMatrix.d2;

		convermatrix._31 = aiMatrix.a3;
		convermatrix._32 = aiMatrix.b3;
		convermatrix._33 = aiMatrix.c3;
		convermatrix._34 = aiMatrix.d3;

		convermatrix._41 = aiMatrix.a4;
		convermatrix._42 = aiMatrix.b4;
		convermatrix._43 = aiMatrix.c4;
		convermatrix._44 = aiMatrix.d4;

		return convermatrix;
	}




	aiMatrix4x4* GetBoneMatrix(const char* bone) { return &m_Bone[bone].Matrix;}
};
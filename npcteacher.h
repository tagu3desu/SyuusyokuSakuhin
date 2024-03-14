#pragma once
#include"gameobject.h"
class NpcTeacher : public GameObject
{
private:
	D3DXMATRIX m_ViewMatrix{};
	D3DXMATRIX m_ProjectionMatrix;



	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};


	float m_GroundHeight=0.0f;

	//コライダー関連
	class BoxCollider* m_NpcCollider{};

	//アニメーション用
	float m_Time=0.0f;
	float m_BlendTime=0.0f;
	std::string m_AnimationName;
	std::string m_NextAnimationName;

	//ポインタ変数
	class Scene* m_Scene{};
	class Player* m_Player{};

public:
	static class AnimationModel* m_Model;

	static void Load();
	static void Unload();

	void Init();
	void Uninit();
	void Update();
	void Draw();

	AnimationModel* GetAnimationModel() { return m_Model; }
};
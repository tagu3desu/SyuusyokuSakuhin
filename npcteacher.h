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


	float m_GroundHeight;

	//�R���C�_�[�֘A
	class Collider* m_NpcCollider{};

	//�A�j���[�V�����p
	float m_Time{};
	float m_BlendTime{};
	std::string m_AnimationName;
	std::string m_NextAnimationName;

	//�|�C���^�ϐ�
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
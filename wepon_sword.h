#pragma once
#include"model.h"
#include"gameobject.h"

#define MAX_DURABILITY 100.0f //����̍ő�ϋv�l

enum WEPON_SHARPNES
{
	SHARPNES_RED,
	SHARPNES_YELLOW,
	SHARPNES_GREEN,
	SHARPNES_BLUE
};

class Sword : public GameObject
{
private:
	Model* m_Model{};

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	D3DXMATRIX  m_Parent{};
	D3DXMATRIX  m_ChildMatrix{};
	D3DXVECTOR3  m_BottomVertex;
	bool m_Swordhit{};

	//�|�C���^�ϐ�
	class Scene* m_Scene{};
	class Camera* m_Camera{};
	class BoxCollider* m_SwordCollider{};
	class Trail* m_SwordTrail{};
	class SwordTopVertex* m_SwordTopVertex{};

	//�T�E���h�֘A
	class Audio* m_SmallAttackHitSE{}; //1�R���{��
	class Audio* m_NormalAttackHitSE{};	//2�R���{��
	class Audio* m_BigAttackHitSE{};	//3�R���{��
	
	
	//�؂ꖡ�֘A
	WEPON_SHARPNES m_WeponSharpnes;
	float m_Durability{};	//�ϋv�l
	float m_WeponDamage{};	//�؂ꖡ�ł̃_���[�W�p�����[�^
	float m_HitStopTime{};	//�q�b�g�X�g�b�v�̎���
	float m_ResultDamege{}; //�U���Z�̔{���~�؂ꖡ�̍ŏI�I�ȃ_���[�W
	bool m_DownSharpnessFlag = false;

	
public:
	
	D3DXVECTOR3 GetBottomVertexPostion() { return m_BottomVertex; }
	D3DXMATRIX GetChild() { return m_ChildMatrix;}
	WEPON_SHARPNES GetWeponSharpnes() { return m_WeponSharpnes; }
	bool GetSwordHit() { return m_Swordhit; }
	bool GetSharpnessUIFlag() {return m_DownSharpnessFlag;}
	void SetDurability(float durability) { m_Durability -= durability; }

	void Init();
	void Uninit();
	void Update();
	void Draw();
};

class SwordTopVertex :public GameObject
{
private:
	static ID3D11Buffer* m_VertexBuffer;
	D3DXMATRIX m_Parent{};
	D3DXVECTOR3 m_TopVertex;

	
	class Scene* m_Scene{};


public:
	D3DXVECTOR3 GetTopVertexPostion() { return m_TopVertex; }

	

	static void Load();
	static void Unload();

	void Init();
	void Uninit();
	void Update();
	void Draw();
};


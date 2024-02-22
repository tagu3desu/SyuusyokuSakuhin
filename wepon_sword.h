#pragma once
#include"model.h"
#include"gameobject.h"

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

	//ポインタ変数
	class Scene* m_Scene{};
	class Camera* m_Camera{};
	class Collider* m_SwordCollider{};
	class Trail* m_SwordTrail{};
	class SwordTopVertex* m_SwordTopVertex{};

	//サウンド関連
	class Audio* m_SmallAttackHitSE{}; //1コンボ目
	class Audio* m_NormalAttackHitSE{};	//2コンボ目
	class Audio* m_BigAttackHitSE{};	//3コンボ目
	
	
	//切れ味関連
	WEPON_SHARPNES m_WeponSharpnes = SHARPNES_BLUE;
	float m_Durability{};	//耐久値
	float m_Damage{};		//ダメージ
	float m_HitStopTime{};	//ヒットストップの時間

	
public:
	
	D3DXVECTOR3 GetBottomVertexPostion() { return m_BottomVertex; }
	D3DXMATRIX GetChild() { return m_ChildMatrix;}

	WEPON_SHARPNES GetWeponSharpnes() { return m_WeponSharpnes; }

	bool GetSwordHit() { return m_Swordhit; }

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


#pragma once
#include"gameobject.h"

class GameTexture: public GameObject
{
private:
	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};


	float m_TimeLimitPosY =0;
	float m_WinLogoPosY =0;
	float m_WinLogo2PosY=0;
	float m_ReturnCampCount=0;
	float m_ChangeIconCount=0;
	float m_y;

	bool m_ClearLogoCountFlag = {};
	bool m_ClearLogoFlag = {};
	bool m_ChangeSceneFlag = {};
	

	class Scene* m_Scene;
	class Enemy* m_Enemy;
	class Sword* m_Sword;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	bool GetGameClear() { return m_ClearLogoFlag; }
	bool GetChangeSceneFlag() { return m_ChangeSceneFlag; }
};
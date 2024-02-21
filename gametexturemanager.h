#pragma once
#include"gameobject.h"

class GameTexture: public GameObject
{
private:
	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};


	float m_TimeLimitPosY;
	float m_WinLogoPosY;
	float m_WinLogo2PosY;
	float m_ReturnCampCount;

	float m_ChangeIconCount=0;

	bool m_ClearLogoCountFlag = {};
	bool m_ClearLogoFlag = {};
	bool m_ChangeSceneFlag = {};

	class Scene* m_Scene;
	class Enemy* m_Enemy;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	bool GetGameClear() { return m_ClearLogoFlag; }
	bool GetChangeSceneFlag() { return m_ChangeSceneFlag; }
};
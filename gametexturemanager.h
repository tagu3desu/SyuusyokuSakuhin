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
	bool m_GameStart{};
	bool m_WinLogoFlag = false;

	class Scene* m_Scene;
	class Enemy* m_Enemy;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	bool GetGameStart() { return m_GameStart; }
};
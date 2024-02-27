#pragma once
#include"gameobject.h"

class GameTexture: public GameObject
{
private:
	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};


	float m_TimeLimitPosY =0.0f;
	float m_WinLogoPosY =0.0f;
	float m_WinLogo2PosY=0.0f;
	float m_ReturnCampCount=0.0f;
	float m_ChangeIconCount=0.0f;
	float m_SharpnessDownY=0.0f;
	float m_SharpnessUpY=0.0f;
	float m_DeadUIY = 0.0f;
	float m_LimitUICount = 0.0f;



	bool m_GameStasrtFlag = {};
	bool m_ClearLogoCountFlag = {};
	bool m_ClearLogoFlag = {};
	bool m_FaliedLogoCountFlag = {};
	bool m_ChangeSceneFlag = {};
	
	
	class Scene* m_Scene;
	class Enemy* m_Enemy;
	class Sword* m_Sword;
	class Player* m_Player;
	class Camera* m_Camera;
	class ItemManager* m_ItemManager;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	bool GetGameClear() { return m_ClearLogoFlag; }
	bool GetChangeSceneFlag() { return m_ChangeSceneFlag; }
};
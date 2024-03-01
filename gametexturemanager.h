#pragma once
#include"gameobject.h"

enum GameSceneAll
{
	TUTORIAL_SCENE,
	QUEST1_SCENE
};


class GameTexture: public GameObject
{
private:
	GameSceneAll m_GameScene/*= QUEST1_SCENE*/;

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
	class TutorialEnemy* m_TutorialEnemy;
	class Sword* m_Sword;
	class Player* m_Player;
	class Camera* m_Camera;
	class ItemManager* m_ItemManager;
	class ClockTimeLimit* m_Clocklimit;
	class ClockTimeHand* m_Clockhand;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();


	void TutorialUpdate();
	void TutorialDraw();
	void QuestUpdate();
	void QuestDraw();

	void SetGameScene(GameSceneAll scene) { m_GameScene = scene; }
	bool GetGameClear() { return m_ClearLogoFlag; }
	bool GetChangeSceneFlag() { return m_ChangeSceneFlag; }
};
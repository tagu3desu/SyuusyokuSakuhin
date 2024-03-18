#pragma once
#include"gameobject.h"

enum GAME_SCENEAll
{
	TUTORIAL_SCENE,
	QUEST1_SCENE
};

enum TUTORIAL_NUMBER
{
	TUTORIAL_MOVE,
	TUTORIAL_RUN,
	TUTORIAL_MOVECAMERA,
	TUTORIAL_ITEM,
	TUTORIAL_ONWEPON,
	TUTORIAL_ATTACK,
	
};

enum TUTORIAL_STORY
{
	TUTORIAL_STORY1,
	TUTORIAL_STORY2,
	TUTORIAL_STORY3,
	TUTORIAL_STORY4,
	TUTORIAL_STORY5,
	TUTORIAL_STORY6,
	TUTORIAL_STORY7,
	TUTORIAL_STORY8,
	TUTORIAL_STORY9
};

class GameTexture: public GameObject
{
private:
	GAME_SCENEAll m_GameScene/*= QUEST1_SCENE*/; //シーンセレクト

	TUTORIAL_NUMBER m_TutorialNumber = TUTORIAL_MOVE;
	TUTORIAL_STORY m_TutorialStory = TUTORIAL_STORY1;


	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};


	//チュートリアル
	//移動
	bool m_TutoriaruMoveFlag = false;
	//ダッシュ
	bool m_TutoriaruRunFlag = false;
	//抜刀
	bool m_TutoriaruOnWeponFlag = false;
	//攻撃
	bool m_TutoriaruAttackFlag = false;
	int m_AttackCount = 0;
	//納刀
	bool m_TutoriaruOffWeponFlag = false;
	//ガード
	bool m_TutoriaruGuardFlag = false;
	//アイテムスロット展開
	bool m_DeploymentItemFlag = false;
	//アイテム変更
	bool m_ItemChangeFlag = false;
	int m_ItemSelectCount = 0;
	//アイテム使用
	bool m_TutoriaruItemUseFlag = false;
	//敵の制御
	bool m_EnemyCallCountFlag = false;
	bool m_EnemyCallFlag = false;

	bool m_EnemyHowlFlag = false;

	//UI上げ下げ用の変数
	float m_TimeLimitPosY =0.0f;
	float m_WinLogoPosY =0.0f;
	float m_WinLogo2PosY=0.0f;
	float m_ReturnCampCount=0.0f;
	float m_ChangeIconCount=0.0f;
	float m_SharpnessDownY=0.0f;
	float m_SharpnessUpY=0.0f;
	float m_DeadUIY = 0.0f;
	float m_LimitUICount = 0.0f;


	//ゲーム終了関係のフラグ
    static bool m_ClearLogoFlag;
	bool m_GameStasrtFlag = {};
	bool m_ClearLogoCountFlag = {};
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
	class NpcTeacher* m_NPC;

	//音源
	class Audio* m_DecideSE{};
	class Audio* m_FallSE{};
	bool m_FallSEFlag = false;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();


	void TutorialUpdate();
	void TutorialDraw();
	void QuestUpdate();
	void QuestDraw();

	void SetGameScene(GAME_SCENEAll scene) { m_GameScene = scene; }
	bool GetGameClear() { return m_ClearLogoFlag; }
	bool GetChangeSceneFlag() { return m_ChangeSceneFlag; }
	//敵の制御用
	bool GetEnemyCallFlag() { return m_EnemyCallFlag; }
	bool GetEnemyHowlFlag() { return m_EnemyHowlFlag; }
};
#pragma once
#include"gameobject.h"


#define MAX_ThubPosition 145
#define MIN_ThubPosition 325

class TitleTexture: public GameObject
{
private:

	class Scene* scene{};

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	float m_X;
	float m_Y;

	float m_OldX;
	float m_NewX;
	float difference;

	D3DXVECTOR2 m_MenuSelectPosition{};

	D3DXVECTOR2 m_BGMThumbPosition{};
	D3DXVECTOR2 m_SEThumbPosition{};

	//音量調節用のつまみの初期座標
	float m_BGM_Volume=8.0f;
	float m_SE_Volume=8.0f;

	//マウスの座標
	float m_MouseposX;
	float m_MouseposY;

	//音量用のセレクトUI
	float m_SelectUIPosY;
	bool m_BackButton = false;
	bool m_SEFlag=false;
	bool m_BGMFlag=true;

	//クエストセレクト画面
	bool m_QuestSelect = false;
	bool m_TutorialFlag = true;
	bool m_QuestFlag = false;
	bool m_DecidedTutorial = false;
	bool m_DecidedQuest = false;

	bool m_GameButtonOverlap=true;
	bool m_OptionButtonOverlap{};
	bool m_OptionFlag{};

	class Audio* m_DecisiveSE{};
	class Audio* m_SelectSE{};
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();


	bool GetTutorialFlag() { return m_DecidedTutorial; }
	bool GetQuestFlag() { return m_DecidedQuest; }

	bool GetGameButtonOverLap() { return m_GameButtonOverlap; }

	float GetBGMVolume() { return m_BGM_Volume/100; }
	float GetSEVolume() { return m_SE_Volume/100; }
};  


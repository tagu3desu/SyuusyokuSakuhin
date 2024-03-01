#pragma once
#include"scene.h"
#include"polygon2D.h"
#include"sprite.h"

class Title:public Scene
{
private:
	class Fade* m_Fade{};



	class  TitleButton* m_StartButton{};
	

	static bool m_TitleCheck;
	
	float m_FloarPosition;


	static bool m_Menucontrol;
	static bool m_QuestSelect;

	class Scene* scene{};

	class Audio* m_TitleBGM{};
	class Audio* m_DecisiveSE{};
public:
	static bool GetCheckTitle() { return m_TitleCheck; }


	void Init() override;
	void Update() override;
	void Uninit() override;
	void Draw() override;

	static bool GetMenuControl() { return m_Menucontrol; }
	static void SetMenuControl(bool flag) { m_QuestSelect = flag; }
	static bool GetQuestSelect() { return m_QuestSelect; }
	static void SetQuestSelect(bool flag) {m_QuestSelect = flag;}
};
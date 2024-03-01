#pragma once
#include"scene.h"
class Loading :public Scene
{
private:
	

	static bool m_GameLoad;
	static bool m_TutorialLoad;
	
public:
	static void SetGameLoad(bool load) { m_GameLoad = load;}
	static void SetTutorial(bool load) { m_TutorialLoad = load; }

	void Init() override;
	void Update() override;
};
#pragma once
#include"gameobject.h"

class Fade :public GameObject
{

private:
	

	class Sprite* m_Sprite{};
	float m_AlfaColor = 1.0f;
	bool m_FadeOut = false;
	bool m_FadeIn = false;
	bool m_FadeFinish = false;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void FadeOut() { m_FadeOut = true;}
	bool GetFadeFinish() { return m_FadeFinish;}

};


#pragma once
#include"scene.h"

#include"sprite.h"
class Loading :public Scene
{
private:
	

	float m_MouseposX;
	float m_MouseposY;

	bool m_LoadingCheck;

	class  TitleButton* m_StartButton{};
	

public:
	bool GetCheckLoad() { return m_LoadingCheck;}

	bool setloadflag(bool flag) { m_LoadingCheck = flag; }

	void Init() override;
	void Update() override;
};
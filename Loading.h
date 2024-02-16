#pragma once
#include"scene.h"
class Loading :public Scene
{
private:
	

	float m_MouseposX;
	float m_MouseposY;

	bool m_LoadingCheck;

public:
	bool GetCheckLoad() { return m_LoadingCheck;}
	void Init() override;
	void Update() override;
};
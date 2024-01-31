#pragma once
#include"scene.h"

#include"sprite.h"
class Loading :public Scene
{
private:
	

	float m_MouseposX;
	float m_MouseposY;

	class  TitleButton* m_StartButton{};
	
public:
	void Init() override;
	void Update() override;
};
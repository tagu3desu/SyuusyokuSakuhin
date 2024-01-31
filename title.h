#pragma once
#include"scene.h"
#include"polygon2D.h"
#include"sprite.h"
class Title:public Scene
{
private:
	class Fade* m_Fade{};

	float m_MouseposX;
	float m_MouseposY;

	class  TitleButton* m_StartButton{};
	bool  buttonOverLapping;

	static bool m_TitleCheck;
	int m_framecount;
	float m_FloarPosition;

	D3DXVECTOR3 m_SponePosition;
public:
	static bool GetCheckTitle() { return m_TitleCheck; }

	

	

	void Init() override;
	void Update() override;
	void Uninit() override;
	void Draw() override;

};
#pragma once
#include"scene.h"
#include"polygon2D.h"
#include"sprite.h"
class Result :public Scene
{
private:
	/*TimeCount* m_MinTime;
	TimeCount* m_SecondTime;
	TimeCount* m_MilliSecondTime;*/

public:
	void Init() override;
	void Update() override;
};

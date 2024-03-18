#pragma once
#include"gameobject.h"

class ResultTexture : public GameObject
{
private:

	class Scene* m_Scene{};
	

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

};
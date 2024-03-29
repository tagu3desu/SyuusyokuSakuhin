#pragma once
#include"gameobject.h"

class LoadingTexture: public GameObject
{
private:
	
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};
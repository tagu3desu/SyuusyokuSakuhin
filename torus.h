#pragma once
#include"model.h"
#include"gameobject.h"

class Torus : public GameObject
{
private:
	Model* m_Model{};


public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
}; 

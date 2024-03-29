#pragma once
#include"model.h"
#include"gameobject.h"

class TreasureBox : public GameObject
{
private:
	static Model* m_Model;

	
	class Scene* m_Scene{};
	
	
public:
	static void Load();
	static void Unload();

	void Init();
	void Uninit();
	void Update();
	void Draw();
};


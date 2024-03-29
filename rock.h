#pragma once
#include"model.h"
#include"gameobject.h"

class Rock : public GameObject
{
private:
	static Model* m_Model;

	

	class Scene* m_Scene{};
	class BoxCollider* m_RockCollider{};
public:
	static void Load();
	static void Unload();


	void Init();
	void Uninit();
	void Update();
	void Draw();
};
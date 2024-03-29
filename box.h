#pragma once
#include"model.h"
#include"gameobject.h"

class Box : public GameObject
{
private:
	static Model* m_Model;

	
	class Scene* scene{};
	class BoxCollider* m_BoxCollider{};
	
public:
	static void Load();
	static void Unload();

	void Init();
	void Uninit();
	void Update();
	void Draw();
};


#pragma once
#include"model.h"
#include"gameobject.h"

class BaceCampTent : public GameObject
{
private:
	static Model* m_Model;

	

	class Scene* scene{};
	
	
public:
	static void Load();
	static void Unload();

	void Init();
	void Uninit();
	void Update();
	void Draw();
};


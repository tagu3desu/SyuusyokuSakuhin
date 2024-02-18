#pragma once
#include <list>
#include"gameobject.h"
class DebugSystem :public GameObject
{
private:
	static int m_FPS;



	bool m_ColliderEnable;
	bool m_DebugWindowEnable;

	class Scene* m_Scene;
	class Collider* m_Collider;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	bool GetDebugWindowEnable() { return m_DebugWindowEnable; }
};
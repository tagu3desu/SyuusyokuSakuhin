#pragma once
#include"scene.h"


class Game : public Scene
{
private:
	class Audio* m_BGM{};

	class Fade* m_Fade{};

	static bool m_LoadFinish;

	LIGHT m_Light;
	float m_X = 1.0f;
	float m_Y = -1.0f;
	float m_Z = 1.0f;
	float m_A = 0.0f;


	class Scene* m_Scene{};
public:


	static void Load();
	static void Unload();
	static bool GetLoadFinish() { return m_LoadFinish; }


	void Init() override;
	void Update() override;
	void Uninit() override;
	void Draw() override;



};
#pragma once
#include"scene.h"


class Game : public Scene
{
private:
	class Audio* m_BGM{};

	class Fade* m_Fade{};

	static bool m_LoadFinish;

	LIGHT light;
	float x = 1.0f;
	float y = -1.0f;
	float z = 1.0f;
	float a = 0.0f;

	class Scene* scene{};
public:
	static void Load();
	static void Unload();
	static bool GetLoadFinish() { return m_LoadFinish; }


	void Init() override;
	void Update() override;
	void Uninit() override;
	void Draw() override;



};
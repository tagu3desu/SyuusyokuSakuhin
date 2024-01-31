#pragma once
#include"scene.h"


class Game : public Scene
{
private:
	class Audio* m_BGM{};

	class Fade* m_Fade{};

	static bool m_LoadFinish;

	bool getvertex{};
public:
	static void Load();
	static void Unload();
	static bool GetLoadFinish() { return m_LoadFinish; }


	void Init() override;
	void Update() override;
	void Uninit() override;
	void Draw() override;



};
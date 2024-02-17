#include "debug.h"
#include"main.h"
#include"manager.h"
#include"scene.h"
#include"collider.h"
#include"input.h"

int DebugSystem::m_FPS = 60;
void DebugSystem::Init()
{
	m_Scene = Manager::GetScene();
}

void DebugSystem::Uninit()
{
}

void DebugSystem::Update()
{
	if (Input::GetKeyPress('O'))
	{
		m_FrameWait++;
		if (m_FrameWait > 90)
		{
			if (m_DebugWindowEnable)
			{
				m_DebugWindowEnable = false;
				m_FrameWait =0;
			}
			else
			{
				m_DebugWindowEnable = true;
				m_FrameWait = 0;
			}
		}
	}

	if (m_DebugWindowEnable)
	{
		// Start the Dear ImGui frame
		ImGui::Begin("DEBUG");
		ImGui::SliderInt("FPS", &m_FPS, 10.0f, 60.0f);
		ImGui::Text("%.3f  ms/frame(%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		static float value[180];
		for (int i = 0; i < 179; i++)
			value[i] = value[i + 1];
		value[179] = ImGui::GetIO().DeltaTime * 1000.0f;
		//第2引数は表示したいデータ,第3引数は要素数
		ImGui::PlotLines("", value, sizeof(value) / sizeof(float), 0, NULL, 0.0f, 100.0f, ImVec2(0, 50));
		ImGui::Checkbox("Colldier", &m_ColliderEnable);
		std::vector<Collider*> colliders = m_Scene->GetGameObjects<Collider>();
		for (Collider* collider : colliders)
		{
			collider->SetColliderEnable(m_ColliderEnable);
		}
		ImGui::End();
		SetFPS(m_FPS);
	}
	
}

void DebugSystem::Draw()
{
}

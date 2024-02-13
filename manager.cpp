#include "main.h"
#include "manager.h"
#include "renderer.h"
#include"scene.h"
#include"input.h"
#include"game.h"
#include"title.h"
#include"audio.h"

Scene* Manager::m_Scene{};	//静的メンバ変数は再宣言が必要
Scene* Manager::m_NextScene{}; 
void Manager::Init()
{
	Renderer::Init();

	Input::Init();
	Audio::InitMaster();

	//ImGUI初期化
	{
		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsLight();

		// Setup Platform/Renderer backends
		ImGui_ImplWin32_Init(GetWindow());
		ImGui_ImplDX11_Init(Renderer::GetDevice(), Renderer::GetDeviceContext());

	
		io.Fonts->AddFontDefault();
		
	}


	
	SetScene<Title>();
	//SetScene<Game>();
	
}

void Manager::Uninit()
{

	m_Scene->Uninit();
	delete m_Scene;

	//ImGUI終了処理
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	Audio::UninitMaster();
	Input::Uninit();
	Renderer::Uninit();
}

void Manager::Update()
{
	Input::Update();
	if (m_NextScene)
	{
		if (m_Scene)
		{
			m_Scene->Uninit();
			delete m_Scene;
		}
		m_Scene = m_NextScene;
		m_Scene->Init();

		m_NextScene = nullptr;
	}
	

	// Start the Dear ImGui frame
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGui::SetNextWindowPos(ImVec2(100, 100));
	ImGui::SetNextWindowSize(ImVec2(400,100));
	ImGui::Begin("Renderer");
	ImGui::Text("%.3f  ms/frame(%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	
	static float value[180];
	for (int i = 0; i < 179; i++)
		value[i] = value[i + 1];

	//value[179] = 1000.0f / ImGui::GetIO().Framerate;
	value[179] = ImGui::GetIO().DeltaTime *1000.0f;


	//第2引数は表示したいデータ,第3引数は要素数
	ImGui::PlotLines("", value, sizeof(value) / sizeof(float), 0, NULL, 0.0f, 100.0f, ImVec2(0, 50));

	ImGui::End();

	m_Scene->Update();
	
	
}

void Manager::Draw()
{ 
	Renderer::Begin();

	m_Scene->Draw();
	
	//ImGUIの描画処理
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	Renderer::End();
}

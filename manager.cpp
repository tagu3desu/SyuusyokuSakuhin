#include "main.h"
#include "manager.h"
#include "renderer.h"
#include"scene.h"
#include"input.h"
#include"game.h"
#include"title.h"
#include"audio.h"
#include"collider.h"

Scene* Manager::m_Scene{};	//�ÓI�����o�ϐ��͍Đ錾���K�v
Scene* Manager::m_NextScene{}; 


void Manager::Init()
{
	Renderer::Init();

	Input::Init();
	Audio::InitMaster();

	
	//ImGUI������
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

	//ImGUI�I������
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
	
	
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	
	

	m_Scene->Update();
}

void Manager::Draw()
{ 
	Renderer::Begin();

	
	m_Scene->Draw();
	
	//ImGUI�̕`�揈��
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	Renderer::End();
}

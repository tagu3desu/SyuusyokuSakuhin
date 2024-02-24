#if 1
//デバック用環境
#include "main.h"
#include "manager.h"
#include"game.h"
#include"debug.h"
#include <thread>


const char* CLASS_NAME = "AppClass";
const char* WINDOW_NAME = "就活作品";


LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
POINT g_LastmousePos;
POINT g_CursorPos;
POINT g_CursorPosinWnd;

HWND g_Window;


float rot;
float hweel;
int g_FPS = 60;
bool g_Pause = false;
bool g_ShowCursor = true;
bool g_RockCursor=false;

HWND GetWindow()
{
	return g_Window;
}


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{


	WNDCLASSEX wcex;
	{
		wcex.cbSize = sizeof(WNDCLASSEX);
		wcex.style = 0;
		wcex.lpfnWndProc = WndProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = hInstance;
		wcex.hIcon = nullptr;
		wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wcex.hbrBackground = nullptr;
		wcex.lpszMenuName = nullptr;
		wcex.lpszClassName = CLASS_NAME;
		wcex.hIconSm = nullptr;

		RegisterClassEx(&wcex);


		RECT rc = { 0, 0, (LONG)SCREEN_WIDTH, (LONG)SCREEN_HEIGHT };
		//AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

		g_Window = CreateWindowEx(0, CLASS_NAME, WINDOW_NAME, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
			rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, hInstance, nullptr);
	}



	Manager::Init();

	
	ShowCursor(g_ShowCursor);
	GetCursorPos(&g_LastmousePos);
	ShowWindow(g_Window, nCmdShow);
	UpdateWindow(g_Window);



	ShowCursor(true);
	DWORD dwExecLastTime;
	DWORD dwCurrentTime;
	timeBeginPeriod(1);
	dwExecLastTime = timeGetTime();
	dwCurrentTime = 0;



	MSG msg;
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{


			dwCurrentTime = timeGetTime();

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / g_FPS))
			{
				dwExecLastTime = dwCurrentTime;
				GetCursorPos(&g_CursorPos);
				
				Manager::Update();
				Manager::Draw();
									
			}
		}
	}

	timeEndPeriod(1);

	UnregisterClass(CLASS_NAME, wcex.hInstance);

	Manager::Uninit();
	return (int)msg.wParam;
}

//ImGUIのウィンドウ処理をプロシージャに追加
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);



LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//ImGUIのウィンドウ処理をプロシージャに追加
	if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		}
		break;
	case WM_MOUSEWHEEL:
		rot = GET_WHEEL_DELTA_WPARAM(wParam) /120;
		hweel += -rot;
		/*if (hweel < 0)
		{
			hweel =0;
		}*/
		/*else if (hweel > 50.0f * 100)
		{
			hweel = 50.0f * 100;
		}*/
		break;
		
	default:
		break;
	}

	GetCursorPos(&g_CursorPosinWnd);
	ScreenToClient(hWnd, &g_CursorPosinWnd);

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
float GetMouseCursorPosX() { return g_CursorPos.x - g_LastmousePos.x; }
float GetMouseCursorPosY() { return g_CursorPos.y - g_LastmousePos.y; }

float GetMouseCursorPosXinWnd() { return g_CursorPosinWnd.x; }
float GetMouseCursorPosYinWnd() { return g_CursorPosinWnd.y; }

void SetShowCursor(bool flag) { g_ShowCursor = flag;}



void SetFPS(int fps) { g_FPS = fps; }

//カメラで100はいらない
float GetHweel() { return hweel;}
//float GetHweel() { return rot;}





#else	//本番用実行環境
#include "main.h"
#include "manager.h"
#include"debug.h"
#include"title.h"
#include <thread>


const char* CLASS_NAME = "AppClass";
const char* WINDOW_NAME = "就活作品";


LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
POINT lastmousePos;
POINT cursorPos;
POINT cursorPosinWnd;
HWND g_Window;
int g_FPS = 60;
bool g_ShowCursor = true;

int mouseX;
int mouseY;

HWND GetWindow()
{
	return g_Window;
}


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{


	WNDCLASSEX wcex;
	{
		wcex.cbSize = sizeof(WNDCLASSEX);
		wcex.style = 0;
		wcex.lpfnWndProc = WndProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = hInstance;
		wcex.hIcon = nullptr;
		wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wcex.hbrBackground = nullptr;
		wcex.lpszMenuName = nullptr;
		wcex.lpszClassName = CLASS_NAME;
		wcex.hIconSm = nullptr;

		RegisterClassEx(&wcex);


		RECT rc = { 0, 0, (LONG)SCREEN_WIDTH, (LONG)SCREEN_HEIGHT };
		AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

		g_Window = CreateWindowEx(0, CLASS_NAME, WINDOW_NAME, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
			rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, hInstance, nullptr);
	}



	Manager::Init();
	
	GetCursorPos(&lastmousePos);
	ShowWindow(g_Window, nCmdShow);
	UpdateWindow(g_Window);




	DWORD dwExecLastTime;
	DWORD dwCurrentTime;
	timeBeginPeriod(1);
	dwExecLastTime = timeGetTime();
	dwCurrentTime = 0;



	MSG msg;
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / g_FPS))
			{
				dwExecLastTime = dwCurrentTime;
				GetCursorPos(&cursorPos);
				

				if (!g_ShowCursor/* || !Title::GetCheckTitle() */)
				{
					SetCursorPos(lastmousePos.x, lastmousePos.y);
				}
				else if (!g_ShowCursor && Title::GetCheckTitle())
				{
					SetCursorPos(lastmousePos.x, lastmousePos.y);
				}
				

				
				
				//ポーズ処理
				Manager::Update();
				Manager::Draw();
			}
		}
	}

	timeEndPeriod(1);

	UnregisterClass(CLASS_NAME, wcex.hInstance);

	Manager::Uninit();

	return (int)msg.wParam;
}

//ImGUIのウィンドウ処理をプロシージャに追加
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);



LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//ImGUIのウィンドウ処理をプロシージャに追加
	if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case 'O':
			if (g_ShowCursor)
			{
				SetShowCursor(false);
			}
			else if(!g_ShowCursor)
			{
				SetShowCursor(true);
			}
			ShowCursor(g_ShowCursor);
		break;
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		}
		break;

	default:
		if (!Title::GetCheckTitle)
		{
			SetShowCursor(false);
		}
		break;
	}

	
	
	GetCursorPos(&cursorPosinWnd);
	ScreenToClient(hWnd, &cursorPosinWnd);

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
float GetMouseCursorPosX() { return cursorPos.x - lastmousePos.x; }
float GetMouseCursorPosY() { return cursorPos.y - lastmousePos.y; }

float GetMouseCursorPosXinWnd() { return cursorPosinWnd.x; }
float GetMouseCursorPosYinWnd() { return cursorPosinWnd.y; }

void SetFPS(int fps) { g_FPS = fps; }

void SetShowCursor(bool flag) { g_ShowCursor = flag; }

bool GetShowCursor() { return g_ShowCursor; }

#endif // 0


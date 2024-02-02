#if 0
//デバック用環境
#include "main.h"
#include "manager.h"
#include <thread>


const char* CLASS_NAME = "AppClass";
const char* WINDOW_NAME = "就活作品";


LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
POINT lastmousePos;
POINT cursorPos;
POINT cursorPosinWnd;
HWND g_Window;

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
	ShowCursor(true);
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

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{
				dwExecLastTime = dwCurrentTime;
				GetCursorPos(&cursorPos);



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
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		}
		break;

	default:
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

#else	//本番用実行環境
#include "main.h"
#include "manager.h"
#include <thread>


const char* CLASS_NAME = "AppClass";
const char* WINDOW_NAME = "就活作品";


LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
POINT lastmousePos;
POINT cursorPos;
POINT cursorPosinWnd;
HWND g_Window;



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
	ShowCursor(false);
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

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{
				dwExecLastTime = dwCurrentTime;
				GetCursorPos(&cursorPos);
				SetCursorPos(lastmousePos.x, lastmousePos.y);
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
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		}
		break;

	default:
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

#endif // 0

#
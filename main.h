#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define NOMINMAX	//asinmpを使用する場合はこれが必要
#include <windows.h>
#include <assert.h>
#include <functional>

#include<DirectXMath.h>
using namespace DirectX;

#pragma warning(push)
#pragma warning(disable:4005)

#include <d3d11.h>
#include <d3dx9.h>
#include <d3dx11.h>

//ImGUI
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"

#pragma warning(pop)



#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "d3dx11.lib")


#define SCREEN_WIDTH	(1920)//1280
#define SCREEN_HEIGHT	(1080)//720


#define	DEPTH_PIXEL (4096)

HWND GetWindow();
float GetMouseCursorPosX();
float GetMouseCursorPosY();


float GetMouseCursorPosXinWnd();
float GetMouseCursorPosYinWnd();

/*void GetMouseCursorPositionInWindow(HWND hWnd, int& mouseX, int& mouseY)
{
    POINT cursorScreenPos;
    GetCursorPos(&cursorScreenPos);

    // スクリーン座標からクライアント座標に変換
    ScreenToClient(hWnd, &cursorScreenPos);

    mouseX = cursorScreenPos.x;
    mouseY = cursorScreenPos.y;
}*/


//=============================================================================
//
// ���͏��� [input.h]
// Author : 
//
//=============================================================================
#pragma once

#include <XInput.h>
#pragma comment(lib,"Xinput.lib")

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//�{�^���ꗗ

// XINPUT_GAMEPAD_DPAD_UP			�\���L�[��
// XINPUT_GAMEPAD_DPAD_DOWN			�\���L�[��
// XINPUT_GAMEPAD_DPAD_LEFT			�\���L�[��
// XINPUT_GAMEPAD_DPAD_RIGHT		�\���L�[�E
// XINPUT_GAMEPAD_START
// XINPUT_GAMEPAD_BACK
// XINPUT_GAMEPAD_LEFT_THUMB		L�X�e�B�b�N��������
// XINPUT_GAMEPAD_RIGHT_THUMB		R�X�e�B�b�N��������
// XINPUT_GAMEPAD_LEFT_SHOULDER		L�{�^��
// XINPUT_GAMEPAD_RIGHT_SHOULDER	R�{�^��
// XINPUT_GAMEPAD_A
// XINPUT_GAMEPAD_B
// XINPUT_GAMEPAD_X
// XINPUT_GAMEPAD_Y

//�X�e�B�b�N�͈̔�
// X�� ��-1.0�@�E 1.0
// Y�� �� 1.0�@��-1.0

//�g���K�[�͈̔�
// 0 �` 255

// �o�C�u���[�V�����͈̔�
// 0 �` 255

#define DEADZONE			8800	// �e����25%�𖳌��]�[���Ƃ���
#define MAX_CONTROLLERS     4

struct CONTROLER_STATE
{
	XINPUT_STATE		lastState;
	XINPUT_STATE		state;
	XINPUT_STATE		trigger;
	XINPUT_VIBRATION	vibration;
};

class InputX
{
private:
	static CONTROLER_STATE m_Controllers[MAX_CONTROLLERS];
	static float	m_LeftStickX[MAX_CONTROLLERS];
	static float	m_LeftStickY[MAX_CONTROLLERS];
	static float	m_RightStickX[MAX_CONTROLLERS];
	static float	m_RightStickY[MAX_CONTROLLERS];

public:
	static void Init();
	static void Uninit();
	static void Update();

	//�X�e�B�b�N
	static float GetThumbLeftX(int padNo);
	static float GetThumbLeftY(int padNo);
	static float GetThumbRightX(int padNo);
	static float GetThumbRightY(int padNo);

	//�U��
	static void SetLeftVibration(int padNo, int speed);
	static void SetRightVibration(int padNo, int speed);
	static void SetVibration(int padNo, int speed);
	static void StopVibration(int padNo);

	//�g���K�[
	static int GetLeftTrigger(int padNo); //LT
	static int GetRightTrigger(int padNo); //RT

	//�{�^��
	static BOOL IsButtonPressed(int padNo, DWORD button);
	static BOOL IsButtonTriggered(int padNo, DWORD button);
};


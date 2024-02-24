//=============================================================================
//
// ���͏��� [input.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "inputx.h"

CONTROLER_STATE InputX::m_Controllers[MAX_CONTROLLERS];
float InputX::m_LeftStickX[MAX_CONTROLLERS];
float InputX::m_LeftStickY[MAX_CONTROLLERS];
float InputX::m_RightStickX[MAX_CONTROLLERS];
float InputX::m_RightStickY[MAX_CONTROLLERS];

//=============================================================================
// ���͏����̏�����
//=============================================================================
void InputX::Init()
{
	//������
	ZeroMemory(m_Controllers, sizeof(CONTROLER_STATE) * MAX_CONTROLLERS);
	XInputEnable(true);
}

//=============================================================================
// ���͏����̏I������
//=============================================================================
void InputX::Uninit()
{
	//�p�����[�^�̃��Z�b�g
	ZeroMemory(m_Controllers, sizeof(CONTROLER_STATE) * MAX_CONTROLLERS);

	//�o�C�u���[�V������~
	for (DWORD i = 0; i < MAX_CONTROLLERS; i++)
		XInputSetState(i, &m_Controllers[i].vibration);

	XInputEnable(false);
}

//=============================================================================
// ���͏����̍X�V����
//=============================================================================
void InputX::Update()
{
	for (DWORD i = 0; i < MAX_CONTROLLERS; i++)
	{
		XInputSetState(i, &m_Controllers[i].vibration);

		m_Controllers[i].lastState = m_Controllers[i].state;

		//����FERROR_SUCCESS�@0
		//�ڑ������FERROR_DEVICE_NOT_CONNECTED 1167
		DWORD result;
		result = XInputGetState(i, &m_Controllers[i].state);

		//�g���K�[�쐬
		m_Controllers[i].trigger.Gamepad.wButtons = ((m_Controllers[i].lastState.Gamepad.wButtons ^ m_Controllers[i].state.Gamepad.wButtons) & m_Controllers[i].state.Gamepad.wButtons);

		//���X�e�B�b�N���̍쐬
		float LX = m_Controllers[i].state.Gamepad.sThumbLX;
		float LY = m_Controllers[i].state.Gamepad.sThumbLY;

		float magnitude = sqrtf((LX * LX) + (LY * LY));

		if (magnitude > 32767)
			magnitude = 32767;

		magnitude -= DEADZONE;

		if (magnitude <= 0)
		{
			m_Controllers[i].state.Gamepad.sThumbLX = 0;
			m_Controllers[i].state.Gamepad.sThumbLY = 0;
		}

		if (m_Controllers[i].state.Gamepad.sThumbLX >= 0)
			m_LeftStickX[i] = (float)m_Controllers[i].state.Gamepad.sThumbLX / 32767;
		else
			m_LeftStickX[i] = (float)m_Controllers[i].state.Gamepad.sThumbLX / 32768;

		if (m_Controllers[i].state.Gamepad.sThumbLY >= 0)
			m_LeftStickY[i] = (float)m_Controllers[i].state.Gamepad.sThumbLY / 32767;
		else
			m_LeftStickY[i] = (float)m_Controllers[i].state.Gamepad.sThumbLY / 32768;

		//�E�X�e�B�b�N���̍쐬
		float RX = m_Controllers[i].state.Gamepad.sThumbRX;
		float RY = m_Controllers[i].state.Gamepad.sThumbRY;

		magnitude = sqrtf((RX * RX) + (RY * RY));

		if (magnitude > 32767)
			magnitude = 32767;

		magnitude -= DEADZONE;

		if (magnitude <= 0)
		{
			m_Controllers[i].state.Gamepad.sThumbRX = 0;
			m_Controllers[i].state.Gamepad.sThumbRY = 0;
		}

		if (m_Controllers[i].state.Gamepad.sThumbRX >= 0)
			m_RightStickX[i] = (float)m_Controllers[i].state.Gamepad.sThumbRX / 32767;
		else
			m_RightStickX[i] = (float)m_Controllers[i].state.Gamepad.sThumbRX / 32768;

		if (m_Controllers[i].state.Gamepad.sThumbLY >= 0)
			m_RightStickY[i] = (float)m_Controllers[i].state.Gamepad.sThumbRY / 32767;
		else
			m_RightStickY[i] = (float)m_Controllers[i].state.Gamepad.sThumbRY / 32768;
	}
}

//�X�e�B�b�N�͈̔�
// X ��-1.0�@�E 1.0
// Y �� 1.0�@��-1.0
float InputX::GetThumbLeftX(int padNo)
{
	return m_LeftStickX[padNo];
}

float InputX::GetThumbLeftY(int padNo)
{
	return m_LeftStickY[padNo];
}

float InputX::GetThumbRightX(int padNo)
{
	return m_RightStickX[padNo];
}

float InputX::GetThumbRightY(int padNo)
{
	return m_RightStickY[padNo];
}

//�g���K�[�͈̔�
// 0 �` 255
int InputX::GetLeftTrigger(int padNo)
{
	return m_Controllers[padNo].state.Gamepad.bLeftTrigger;
}

int InputX::GetRightTrigger(int padNo)
{
	return m_Controllers[padNo].state.Gamepad.bRightTrigger;
}

// �o�C�u���[�V�����͈̔�
// 0 �` 255
void InputX::SetLeftVibration(int padNo, int speed)
{
	speed %= 256;
	m_Controllers[padNo].vibration.wLeftMotorSpeed = ((speed + 1) * 256) - 1;
}

void InputX::SetRightVibration(int padNo, int speed)
{
	speed %= 256;
	m_Controllers[padNo].vibration.wRightMotorSpeed = ((speed + 1) * 256) - 1;
}

void InputX::SetVibration(int padNo, int speed)
{
	speed %= 256;
	m_Controllers[padNo].vibration.wLeftMotorSpeed = ((speed + 1) * 256) - 1;
	m_Controllers[padNo].vibration.wRightMotorSpeed = ((speed + 1) * 256) - 1;
}

void InputX::StopVibration(int padNo)
{
	m_Controllers[padNo].vibration.wLeftMotorSpeed = 0;
	m_Controllers[padNo].vibration.wRightMotorSpeed = 0;
}

//�{�^��������Ԃ̎擾
BOOL InputX::IsButtonPressed(int padNo, DWORD button)
{
	return (button & m_Controllers[padNo].state.Gamepad.wButtons);
}

//�{�^���p���X��Ԃ̎擾
BOOL InputX::IsButtonTriggered(int padNo, DWORD button)
{
	return (button & m_Controllers[padNo].trigger.Gamepad.wButtons);
}

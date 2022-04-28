//=============================================================================
//
// �Q�[���p�b�h���͏��� [gamepad.h]
// Author : �O���B
//
//=============================================================================
#ifndef _GAMEPAD_H_
#define _GAMEPAD_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "input.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CGamePad : CInput
{
public:
	enum PadButton
	{
		DIP_X = 0,
		DIP_Y,
		DIP_A,
		DIP_B,
		DIP_L1,
		DIP_R1,
		DIP_L2,
		DIP_R2,
		DIP_LS,
		DIP_RS,
		DIP_BACK,
		DIP_START,
		DIP_GUIDE,
		DIP_MAX
	};

	CGamePad();
	~CGamePad();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit();
	void Update();

	int GetPress(PadButton Button) const	{ return m_aPadState.rgbButtons[Button] & 0x80; }
	int GetTrigger(PadButton Button) const	{ return m_aPadStateTrigger.rgbButtons[Button] & 0x80; }
	int GetRelease(PadButton Button) const	{ return m_aPadStateRelease.rgbButtons[Button] & 0x80; }

	bool GetAnyButton() const;
	bool GetButton(PadButton Button) const;

	float PressCrossKey() const;
	float TriggerCrossKey() const;

	float LeftStickX();
	float LeftStickY();

	float RightStickX();
	float RightStickY();

	static bool GetGamePad() 				{ return m_bGamePad; }

private:
	static bool m_bGamePad;

	DIJOYSTATE m_aPadState;				// �Q�[���p�b�h�̓��͏��(�v���X���)
	DIJOYSTATE m_aPadStateTrigger;		// �Q�[���p�b�h�̓��͏��(�g���K�[���)
	DIJOYSTATE m_aPadStateRelease;		// �Q�[���p�b�h�̓��͏��(�����[�X���)
};
#endif
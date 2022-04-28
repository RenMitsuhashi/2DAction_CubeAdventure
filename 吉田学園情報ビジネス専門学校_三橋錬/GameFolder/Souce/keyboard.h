//=============================================================================
//
// ���͏��� [keyboard.h]
// Author : �O���B
//
//=============================================================================
#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "input.h"

// �}�N����`
#define NUM_KEY_MAX (256) // �L�[�̍ő吔

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CKeyboard : CInput
{
public:
	CKeyboard();
	~CKeyboard();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit();
	void Update();

	int GetPress(int nKey) const	{ return m_aKeyState[nKey] & 0x80; }

	int GetTrigger(int nKey) const
	{
		if ((m_aKeyStateTrigger[nKey] & 0x80) != 0 &&
			(m_aKeyStateRelease[nKey] & 0x80) == 0)
		{
			return true;
		}
		return false;
	}

	int GetRelease(int nKey) const
	{
		if ((m_aKeyStateRelease[nKey] & 0x80) != 0 &&
			(m_aKeyStateTrigger[nKey] & 0x80) == 0)
		{
			return true;
		}
		return false;
	}

	int GetAnyKey() const;
	int GetKey(int nKey) const;

	static bool GetKeyboard() { return m_bKeyboard; }

private:
	static bool m_bKeyboard ;

	BYTE m_aKeyState[NUM_KEY_MAX];				// �Q�[���p�b�h�̓��͏��(�v���X���)
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX];		// �Q�[���p�b�h�̓��͏��(�g���K�[���)
	BYTE m_aKeyStateRelease[NUM_KEY_MAX];		// �Q�[���p�b�h�̓��͏��(�����[�X���)
};
#endif
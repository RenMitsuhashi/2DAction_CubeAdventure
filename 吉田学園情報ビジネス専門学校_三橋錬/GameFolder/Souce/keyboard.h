//=============================================================================
//
// 入力処理 [keyboard.h]
// Author : 三橋錬
//
//=============================================================================
#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "input.h"

// マクロ定義
#define NUM_KEY_MAX (256) // キーの最大数

//*****************************************************************************
// クラス定義
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

	BYTE m_aKeyState[NUM_KEY_MAX];				// ゲームパッドの入力情報(プレス情報)
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX];		// ゲームパッドの入力情報(トリガー情報)
	BYTE m_aKeyStateRelease[NUM_KEY_MAX];		// ゲームパッドの入力情報(リリース情報)
};
#endif
//=============================================================================
//
// ゲームパッド入力処理 [gamepad.h]
// Author : 三橋錬
//
//=============================================================================
#ifndef _GAMEPAD_H_
#define _GAMEPAD_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "input.h"

//*****************************************************************************
// クラス定義
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

	DIJOYSTATE m_aPadState;				// ゲームパッドの入力情報(プレス情報)
	DIJOYSTATE m_aPadStateTrigger;		// ゲームパッドの入力情報(トリガー情報)
	DIJOYSTATE m_aPadStateRelease;		// ゲームパッドの入力情報(リリース情報)
};
#endif
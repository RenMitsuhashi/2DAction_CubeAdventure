//=============================================================================
//
// マウス入力処理 [gamepad.h]
// Author : 三橋錬
//
//=============================================================================
#ifndef _MOUSE_H_
#define _MOUSE_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "input.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CMouse : CInput
{
public:
	enum MouseButton
	{
		DIM_L = 0,	// 左クリック
		DIM_R,		// 右クリック
		DIM_W,		// ホイールクリック
		DIM_MAX
	};

	CMouse();
	~CMouse();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit();
	void Update();

	int GetPress(MouseButton Button) const;
	int GetTrigger(MouseButton Button) const;
	int GetRelease(MouseButton Button) const;


	const LONG MouseX() const	{ return m_MouseState.lX; }
	const LONG MouseY() const	{ return m_MouseState.lY; }
	const LONG MouseZ() const	{ return m_MouseState.lZ; }

	bool Mouse() const			{ return m_bMouse; }

private:
	DIMOUSESTATE m_MouseState;              //マウスの入力情報(プレス情報)
	DIMOUSESTATE m_MouseStateTrigger;
	DIMOUSESTATE m_MouseStateRelease;
	bool m_bMouse;
};
#endif
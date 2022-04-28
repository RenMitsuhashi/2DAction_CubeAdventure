//=============================================================================
//
// �}�E�X���͏��� [gamepad.h]
// Author : �O���B
//
//=============================================================================
#ifndef _MOUSE_H_
#define _MOUSE_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "input.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CMouse : CInput
{
public:
	enum MouseButton
	{
		DIM_L = 0,	// ���N���b�N
		DIM_R,		// �E�N���b�N
		DIM_W,		// �z�C�[���N���b�N
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
	DIMOUSESTATE m_MouseState;              //�}�E�X�̓��͏��(�v���X���)
	DIMOUSESTATE m_MouseStateTrigger;
	DIMOUSESTATE m_MouseStateRelease;
	bool m_bMouse;
};
#endif
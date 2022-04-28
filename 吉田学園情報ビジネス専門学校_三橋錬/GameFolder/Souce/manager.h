//=============================================================================
//
// �}�l�[�W�� [manager.h]
// Author : �O���B
//
//=============================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

// �O���錾
class CKeyboard;
class CMouse;
class CGamePad;

class CTitle;
class CGame;
class CStageBuild;
class CResult;

class CFade;
class CSound;
class CData;
class CTexture;

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CManager
{
public:
	enum MODE
	{
		MODE_TITLE = 0,
		MODE_BUILD,
		MODE_GAME,
		MODE_RESULT,
		MODE_MAX
	};

	CManager();
	~CManager();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static void SetMode(MODE mode);
	static MODE GetMode(void) { return m_mode; }

	static CRenderer			*GetRenderer()		{ return m_pRenderer; }
	static CKeyboard			*GetKeyboard()		{ return m_pKeyboard; }
	static CMouse				*GetMouse()			{ return m_pMouse; }
	static CGamePad				*GetGamepad();
	static CFade				*GetFade()			{ return m_pFade; }
	static CSound				*GetSound()			{ return m_pSound; }

	static CTitle				*GetTitle()			{ return m_pTitle; }
	static CGame				*GetGame()			{ return m_pGame; }
	static CStageBuild			*GetStageBuild()	{ return m_pStageBuild; }
	static CResult				*GetResult()		{ return m_pResult; }

	static CData				*GetData()			{ return m_pData; }
	static CTexture				*GetTexture()		{ return m_pTexture; }

private:
	static CRenderer			*m_pRenderer;		// �����_���[�̃N���X
	static CKeyboard			*m_pKeyboard;
	static CMouse				*m_pMouse;
	static CGamePad				*m_pGamepad;

	static CTitle				*m_pTitle;			// �^�C�g���̃N���X
	static CGame				*m_pGame;			// �Q�[���̃N���X
	static CStageBuild			*m_pStageBuild;		// �X�e�[�W�r���_�[�̃N���X
	static CResult				*m_pResult;			// ���U���g�̃N���X

	static CData				*m_pData;			// �f�[�^�̃N���X
	static CFade				*m_pFade;			// �t�F�[�h�̃N���X
	static CSound				*m_pSound;			// �T�E���h�̃N���X
	static MODE					m_mode;				// ��ʂ̃��[�h

	static CTexture				*m_pTexture;		// �e�N�X�`���̃N���X
};

#endif
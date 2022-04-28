//=============================================================================
//
// �^�C�g���V�[�� [title.h]
// Author : �O���B
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CScreenBg;
class CModeSelect;

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "manager.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CTitle : public CManager
{
public:
	enum TITLEOBJ
	{
		Title_Bg = 0,
		Title_Game,
		Title_Build,
		Title_Quit,
		Title_Max
	};

	CTitle();
	~CTitle();

	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CScreenBg		*GetScreenBg(int num)	{ return m_pScreenBg[num]; }
	static CModeSelect		*GetModeSelect()		{ return m_pModeSelect; }

private:
	static CScreenBg		*m_pScreenBg[Title_Max];
	static CModeSelect		*m_pModeSelect;
};

#endif
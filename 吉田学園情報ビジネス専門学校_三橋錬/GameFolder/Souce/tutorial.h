//=============================================================================
//
// �`���[�g���A���V�[�� [tutorial.h]
// Author : �O���B
//
//=============================================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CTutorialBg;
class CCursor;
class CPlayer;
class CNormalBlock;

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "scene.h"
#include "manager.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CTutorial : public CManager
{
public:
	CTutorial();
	~CTutorial();

	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CTutorialBg			*GetBg() { return m_pBg; }
	static CCursor				*GetCursor() { return m_pCursor; }
	static CPlayer				*GetPlayer() { return m_pPlayer; }
	static CNormalBlock			*GetNormalBlock() { return m_pNormalBlock; }

private:
	static CTutorialBg			*m_pBg;						// �w�i�̃N���X
	static CCursor				*m_pCursor;					// �J�[�\���ɒǏ]����|���S���̃N���X
	static CPlayer				*m_pPlayer;					// �v���C���[�̃N���X
	static CNormalBlock			*m_pNormalBlock;			// �u���b�N�̃N���X
};

#endif
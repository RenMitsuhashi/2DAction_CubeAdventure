//=============================================================================
//
// ���S�� [deathcount.h]
// Author : �O���B
//
//=============================================================================
#ifndef _DEATHCOUNT_H_
#define _DEATHCOUNT_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define DEATH_DIGITS (3)

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CUIBg;

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "number.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CDeathCount : public CScene2D
{
public:
	CDeathCount(CScene::PRIORITY nPriority = PRIORITY_UI);
	~CDeathCount();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CDeathCount *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	static CUIBg		*GetUIBg(int num)	{ return m_pUIBg[num]; }

private:
	CNumber *m_apNumber[DEATH_DIGITS];
	static CUIBg *m_pUIBg[DEATH_DIGITS];
};

#endif
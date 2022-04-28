//=============================================================================
//
// ���U���g�V�[�� [result.h]
// Author : �O���B
//
//=============================================================================
#ifndef _RESULT_H_
#define _RESULT_H_

#define DEATHCOUNT_DIGITS (2)

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CScreenBg;

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "manager.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CResult : public CManager
{
public:
	enum RESULTOBJ
	{
		Result_Bg = 0,
		Result_Max
	};

	CResult();
	~CResult();

	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CScreenBg		*GetScreenBg(int num) { return m_pScreenBg[num]; }

private:
	static CScreenBg		*m_pScreenBg[Result_Max];
};

#endif
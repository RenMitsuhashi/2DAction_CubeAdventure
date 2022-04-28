//=============================================================================
//
// �X�e�[�W���� [stageLoad.h]
// Author : �O���B
//
//=============================================================================
#ifndef _STAGELOAD_H_
#define _STAGELOAD_H_

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CPlayer;
class CNormalBlock;
class CTargetBlock;
class CSaverObj;
class CGoal;
class CGravityReverse;
class CSpiny;
class CPause;

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CStageLoad
{
public:
	enum OBJTYPE
	{
		OBJ_NULL = 0,
		OBJ_NormalBlock,
		OBJ_Player,
		OBJ_Reverse,
		OBJ_Goal,
		OBJ_Spiny,

		OBJ_TargetBlock,
		OBJ_MAX
	};

	CStageLoad();
	~CStageLoad();

	HRESULT Init(void);

	static HRESULT LoadFile(const char *FileName);
	static HRESULT SaveFile();

	static void StageCreate(int type, D3DXVECTOR3 pos, D3DXVECTOR3 move , D3DXVECTOR3 targetpos, int stoptime, int ptn, D3DCOLORVALUE col);

	static CPlayer				*GetPlayer()		{ return m_pPlayer; }
	static CNormalBlock			*GetNormalBlock()	{ return m_pNormalBlock; }
	static CTargetBlock			*GetTargetBlock()	{ return m_pTargetBlock; }
	static CGoal				*GetGoal()			{ return m_pGoal; }
	static CGravityReverse		*GetReverse()		{ return m_pReverse; }
	static CSpiny				*GetSpiny()			{ return m_pSpiny; }
	static CPause				*GetPause()			{ return m_pPause; }

	static D3DXVECTOR3			GetGrid()  			{ return m_Grid; }

	static void					plusQuantity(const int type)	{ objQuantity[type]++; }
	static void					minusQuantity(const int type)	{ objQuantity[type]--; }
	static int					GetQuantity(const int type)		{ return objQuantity[type]; }

	static D3DXVECTOR3			GetMaxStage()					{ return m_MaxStage; }
	static void					SetMaxStageX(const float posx)	{ m_MaxStage.x = posx; }
	static void					SetMaxStageY(const float posy)	{ m_MaxStage.y = posy; }

private:
	static const D3DXVECTOR3	m_Grid;					// 1�}�X�̑傫��

	static CPlayer				*m_pPlayer;				// �v���C���[�̃N���X
	static CNormalBlock			*m_pNormalBlock;		// �u���b�N�̃N���X
	static CTargetBlock			*m_pTargetBlock;		// �u���b�N�̃^�[�Q�b�g�̃N���X
	static CGoal				*m_pGoal;				// �S�[���̃N���X
	static CGravityReverse		*m_pReverse;			// �d�͔��]�̃N���X
	static CSpiny				*m_pSpiny;				// �Ƃ��̃N���X
	static CPause				*m_pPause;				// �|�[�Y��ʂ̃N���X

	static int					objQuantity[OBJ_MAX];	// �I�u�W�F�N�g�̎c��

	static D3DXVECTOR3			m_MaxStage;				// �X�e�[�W�̍ő�l
};

#endif
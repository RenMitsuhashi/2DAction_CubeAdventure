//=============================================================================
//
// �X�e�[�W [stage.h]
// Author : �O���B
//
//=============================================================================
#ifndef _STAGE_H_
#define _STAGE_H_

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CPlayer;
class CNormalBlock;

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
class CStage
{
public:
	enum OBJTYPE
	{
		OBJ_NULL = 0,
		OBJ_NormalBlock,
		OBJ_Player,
		OBJ_MAX
	};

	CStage();
	~CStage();

	static HRESULT LoadFile(const char *FileName);

	static CPlayer				*GetPlayer() { return m_pPlayer; }
	static CNormalBlock			*GetNormalBlock() { return m_pNormalBlock; }

private:
	static void StageCreate(int x, int y);

	static void UnloadTexture();

	static const D3DXVECTOR3 m_Grid;	// 1�}�X�̑傫��

	static int m_nMaxGridX;				// �X�e�[�W�̑傫��X(1�}�X����)
	static int m_nMaxGridY;				// �X�e�[�W�̑傫��Y(1�}�X����)

	static std::vector<vector<string>> m_GridData;

	static bool m_isLoad[OBJ_MAX];		// �e�N�X�`�������[�h������true��

	static CPlayer				*m_pPlayer;					// �v���C���[�̃N���X
	static CNormalBlock			*m_pNormalBlock;			// �u���b�N�̃N���X
};

#endif
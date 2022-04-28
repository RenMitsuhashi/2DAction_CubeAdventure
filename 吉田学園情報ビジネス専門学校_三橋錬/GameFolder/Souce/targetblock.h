//=============================================================================
//
// �ʏ�u���b�N�̈ړ��� [targetblock.h]
// Author : �O���B
//
//=============================================================================
#ifndef _TARGETBLOCK_H_
#define _TARGETBLOCK_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "block.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CTargetBlock : public CBlock
{
public:
	CTargetBlock(CScene::PRIORITY nPriority = PRIORITY_TARGETBLOCK);
	~CTargetBlock();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXVECTOR3 targetpos, int stoptime, LPDIRECT3DTEXTURE9 tex);
	void Uninit();
	void Update();
	void Draw();

	static CTargetBlock *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXVECTOR3 targetpos, int stoptime, LPDIRECT3DTEXTURE9 tex);

private:
};

#endif
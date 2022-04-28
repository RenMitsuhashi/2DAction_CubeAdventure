//=============================================================================
//
// �ʏ�u���b�N [normalblock.h]
// Author : �O���B
//
//=============================================================================
#ifndef _NORMALBLOCK_H_
#define _NORMALBLOCK_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "block.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CNormalBlock : public CBlock
{
public:
	CNormalBlock(CScene::PRIORITY nPriority = PRIORITY_BLOCK);
	~CNormalBlock();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXVECTOR3 targetpos, int stoptime, LPDIRECT3DTEXTURE9 tex);
	void Uninit();
	void Update();
	void Draw();

	static CNormalBlock *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXVECTOR3 targetpos, int stoptime, LPDIRECT3DTEXTURE9 tex);

private:
	int m_fTime;	// �o�ߎ���
	bool m_bGo;		// true�ňړ���
	bool m_bGoing;	// �s����true�A�A���false

	D3DXVECTOR3 m_targetpos;
	D3DXVECTOR3 m_move;
};

#endif
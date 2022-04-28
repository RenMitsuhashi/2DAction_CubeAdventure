//=============================================================================
//
// 通常ブロック [normalblock.h]
// Author : 三橋錬
//
//=============================================================================
#ifndef _NORMALBLOCK_H_
#define _NORMALBLOCK_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "block.h"

//*****************************************************************************
// クラス定義
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
	int m_fTime;	// 経過時間
	bool m_bGo;		// trueで移動中
	bool m_bGoing;	// 行きはtrue、帰りはfalse

	D3DXVECTOR3 m_targetpos;
	D3DXVECTOR3 m_move;
};

#endif
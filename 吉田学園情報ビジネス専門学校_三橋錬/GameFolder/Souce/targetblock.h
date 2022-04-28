//=============================================================================
//
// 通常ブロックの移動先 [targetblock.h]
// Author : 三橋錬
//
//=============================================================================
#ifndef _TARGETBLOCK_H_
#define _TARGETBLOCK_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "block.h"

//*****************************************************************************
// クラス定義
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
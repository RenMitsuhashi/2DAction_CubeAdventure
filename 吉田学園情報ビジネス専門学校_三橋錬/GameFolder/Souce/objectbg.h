//=============================================================================
//
// 板ポリゴン [objectbg.h]
// Author : 三橋錬
//
//=============================================================================
#ifndef _OBJECTBG_H_
#define _OBJECTBG_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "bg.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CObjectBg : public CBg
{
public:
	CObjectBg(CScene::PRIORITY nPriority = CScene::PRIORITY_BGOBJECT);
	~CObjectBg();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, LPDIRECT3DTEXTURE9 tex);
	void Uninit();
	void Update();
	void Draw();

	static CObjectBg *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, LPDIRECT3DTEXTURE9 tex);

private:

};

#endif
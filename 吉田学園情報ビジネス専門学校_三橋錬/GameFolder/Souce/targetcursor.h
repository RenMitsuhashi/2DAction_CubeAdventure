//=============================================================================
//
// カーソル [targetcursor.h]
// Author : 三橋錬
//
//=============================================================================
#ifndef _TARGETCURSOR_H_
#define _TARGETCURSOR_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "scene2D.h"
#include "Stageload.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CTargetCursor : public CScene2D, public CStageLoad
{
public:
	CTargetCursor(CScene::PRIORITY nPriority = PRIORITY_CURSOR);
	~CTargetCursor();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, LPDIRECT3DTEXTURE9 tex);
	void Uninit();
	void Update();
	void Draw();

	static CTargetCursor *Create(D3DXVECTOR3 move, D3DXVECTOR3 size, LPDIRECT3DTEXTURE9 tex);

private:
};

#endif
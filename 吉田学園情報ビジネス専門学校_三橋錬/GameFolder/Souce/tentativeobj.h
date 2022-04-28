//=============================================================================
//
// 仮オブジェクト [tentativeobj.h]
// Author : 三橋錬
//
//=============================================================================
#ifndef _TENTATIVEOBJ_H_
#define _TENTATIVEOBJ_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "scene2D.h"
#include "Stageload.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CTentativeObj : public CScene2D, public CStageLoad
{
public:
	CTentativeObj(CScene::PRIORITY nPriority = PRIORITY_NONE);
	~CTentativeObj();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size);
	void Uninit();

	static CTentativeObj *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size);

private:
	int m_nType;	// 設置してあるオブジェクトのタイプ
};

#endif
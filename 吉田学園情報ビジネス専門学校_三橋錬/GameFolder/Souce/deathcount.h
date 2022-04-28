//=============================================================================
//
// 死亡回数 [deathcount.h]
// Author : 三橋錬
//
//=============================================================================
#ifndef _DEATHCOUNT_H_
#define _DEATHCOUNT_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define DEATH_DIGITS (3)

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CUIBg;

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "number.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CDeathCount : public CScene2D
{
public:
	CDeathCount(CScene::PRIORITY nPriority = PRIORITY_UI);
	~CDeathCount();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CDeathCount *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	static CUIBg		*GetUIBg(int num)	{ return m_pUIBg[num]; }

private:
	CNumber *m_apNumber[DEATH_DIGITS];
	static CUIBg *m_pUIBg[DEATH_DIGITS];
};

#endif
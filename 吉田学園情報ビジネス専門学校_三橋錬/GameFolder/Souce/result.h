//=============================================================================
//
// リザルトシーン [result.h]
// Author : 三橋錬
//
//=============================================================================
#ifndef _RESULT_H_
#define _RESULT_H_

#define DEATHCOUNT_DIGITS (2)

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CScreenBg;

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "manager.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CResult : public CManager
{
public:
	enum RESULTOBJ
	{
		Result_Bg = 0,
		Result_Max
	};

	CResult();
	~CResult();

	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CScreenBg		*GetScreenBg(int num) { return m_pScreenBg[num]; }

private:
	static CScreenBg		*m_pScreenBg[Result_Max];
};

#endif
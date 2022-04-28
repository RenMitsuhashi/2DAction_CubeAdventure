//=============================================================================
//
// タイトルシーン [title.h]
// Author : 三橋錬
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CScreenBg;
class CModeSelect;

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "manager.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CTitle : public CManager
{
public:
	enum TITLEOBJ
	{
		Title_Bg = 0,
		Title_Game,
		Title_Build,
		Title_Quit,
		Title_Max
	};

	CTitle();
	~CTitle();

	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CScreenBg		*GetScreenBg(int num)	{ return m_pScreenBg[num]; }
	static CModeSelect		*GetModeSelect()		{ return m_pModeSelect; }

private:
	static CScreenBg		*m_pScreenBg[Title_Max];
	static CModeSelect		*m_pModeSelect;
};

#endif
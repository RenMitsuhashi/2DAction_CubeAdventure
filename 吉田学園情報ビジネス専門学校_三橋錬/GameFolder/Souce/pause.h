//=============================================================================
//
// ポーズ [pause.h]
// Author : 三橋錬
//
//=============================================================================
#ifndef _PAUSE_H_
#define _PAUSE_H_

class CUIBg;

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "scene2D.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CPause : public CScene2D
{
public:
	enum Select
	{
		Select_Resume_Save = 1,
		Select_Title,
		Select_Max
	};

	enum PauseBg
	{
		Pause_Bg,
		Pause_Resume_Save,
		Pause_Title,
		Pause_Max
	};

	CPause::CPause(CScene::PRIORITY nPriority = PRIORITY_PAUSE);
	CPause::~CPause();

	HRESULT Init(LPDIRECT3DTEXTURE9 tex);
	void Uninit();
	void Update();
	void Draw();

	static CPause *Create(LPDIRECT3DTEXTURE9 tex);

	static void SetNowSave(bool tf) { m_bNowSave = tf; }
	static bool GetNowSave() { return m_bNowSave; }

	static CUIBg *GetUIBg(int num) { return m_pUIBg[num]; }

private:
	static int m_nSelect;
	static bool m_bNowSave;

	static CUIBg *m_pUIBg[Pause_Max];
};

#endif
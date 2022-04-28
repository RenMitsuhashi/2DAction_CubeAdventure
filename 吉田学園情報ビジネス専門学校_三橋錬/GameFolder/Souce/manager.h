//=============================================================================
//
// マネージャ [manager.h]
// Author : 三橋錬
//
//=============================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

// 前方宣言
class CKeyboard;
class CMouse;
class CGamePad;

class CTitle;
class CGame;
class CStageBuild;
class CResult;

class CFade;
class CSound;
class CData;
class CTexture;

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CManager
{
public:
	enum MODE
	{
		MODE_TITLE = 0,
		MODE_BUILD,
		MODE_GAME,
		MODE_RESULT,
		MODE_MAX
	};

	CManager();
	~CManager();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static void SetMode(MODE mode);
	static MODE GetMode(void) { return m_mode; }

	static CRenderer			*GetRenderer()		{ return m_pRenderer; }
	static CKeyboard			*GetKeyboard()		{ return m_pKeyboard; }
	static CMouse				*GetMouse()			{ return m_pMouse; }
	static CGamePad				*GetGamepad();
	static CFade				*GetFade()			{ return m_pFade; }
	static CSound				*GetSound()			{ return m_pSound; }

	static CTitle				*GetTitle()			{ return m_pTitle; }
	static CGame				*GetGame()			{ return m_pGame; }
	static CStageBuild			*GetStageBuild()	{ return m_pStageBuild; }
	static CResult				*GetResult()		{ return m_pResult; }

	static CData				*GetData()			{ return m_pData; }
	static CTexture				*GetTexture()		{ return m_pTexture; }

private:
	static CRenderer			*m_pRenderer;		// レンダラーのクラス
	static CKeyboard			*m_pKeyboard;
	static CMouse				*m_pMouse;
	static CGamePad				*m_pGamepad;

	static CTitle				*m_pTitle;			// タイトルのクラス
	static CGame				*m_pGame;			// ゲームのクラス
	static CStageBuild			*m_pStageBuild;		// ステージビルダーのクラス
	static CResult				*m_pResult;			// リザルトのクラス

	static CData				*m_pData;			// データのクラス
	static CFade				*m_pFade;			// フェードのクラス
	static CSound				*m_pSound;			// サウンドのクラス
	static MODE					m_mode;				// 画面のモード

	static CTexture				*m_pTexture;		// テクスチャのクラス
};

#endif
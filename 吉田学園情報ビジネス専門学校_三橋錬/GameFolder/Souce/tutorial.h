//=============================================================================
//
// チュートリアルシーン [tutorial.h]
// Author : 三橋錬
//
//=============================================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CTutorialBg;
class CCursor;
class CPlayer;
class CNormalBlock;

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "scene.h"
#include "manager.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CTutorial : public CManager
{
public:
	CTutorial();
	~CTutorial();

	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CTutorialBg			*GetBg() { return m_pBg; }
	static CCursor				*GetCursor() { return m_pCursor; }
	static CPlayer				*GetPlayer() { return m_pPlayer; }
	static CNormalBlock			*GetNormalBlock() { return m_pNormalBlock; }

private:
	static CTutorialBg			*m_pBg;						// 背景のクラス
	static CCursor				*m_pCursor;					// カーソルに追従するポリゴンのクラス
	static CPlayer				*m_pPlayer;					// プレイヤーのクラス
	static CNormalBlock			*m_pNormalBlock;			// ブロックのクラス
};

#endif
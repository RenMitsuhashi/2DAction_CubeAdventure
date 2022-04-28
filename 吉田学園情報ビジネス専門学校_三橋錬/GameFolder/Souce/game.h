//=============================================================================
//
// ゲームシーン [game.h]
// Author : 三橋錬
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CGravity;
class CLight;
class CPlanet;
class CGameBg;

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "manager.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CGame : public CManager
{
public:
	CGame();
	~CGame();

	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CLight				*GetLight()		{ return m_pLight; }
	static CPlanet				*GetPlanet()	{ return m_pPlanet; }
	static CGameBg				*GetGameBg()	{ return m_pGameBg; }

private:
	static CLight				*m_pLight;		// ライトのクラス
	static CPlanet				*m_pPlanet;		// 惑星のクラス
	static CGameBg				*m_pGameBg;		// 背景のクラス
};

#endif
//=============================================================================
//
// ステージ生成 [stageLoad.h]
// Author : 三橋錬
//
//=============================================================================
#ifndef _STAGELOAD_H_
#define _STAGELOAD_H_

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CPlayer;
class CNormalBlock;
class CTargetBlock;
class CSaverObj;
class CGoal;
class CGravityReverse;
class CSpiny;
class CPause;

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CStageLoad
{
public:
	enum OBJTYPE
	{
		OBJ_NULL = 0,
		OBJ_NormalBlock,
		OBJ_Player,
		OBJ_Reverse,
		OBJ_Goal,
		OBJ_Spiny,

		OBJ_TargetBlock,
		OBJ_MAX
	};

	CStageLoad();
	~CStageLoad();

	HRESULT Init(void);

	static HRESULT LoadFile(const char *FileName);
	static HRESULT SaveFile();

	static void StageCreate(int type, D3DXVECTOR3 pos, D3DXVECTOR3 move , D3DXVECTOR3 targetpos, int stoptime, int ptn, D3DCOLORVALUE col);

	static CPlayer				*GetPlayer()		{ return m_pPlayer; }
	static CNormalBlock			*GetNormalBlock()	{ return m_pNormalBlock; }
	static CTargetBlock			*GetTargetBlock()	{ return m_pTargetBlock; }
	static CGoal				*GetGoal()			{ return m_pGoal; }
	static CGravityReverse		*GetReverse()		{ return m_pReverse; }
	static CSpiny				*GetSpiny()			{ return m_pSpiny; }
	static CPause				*GetPause()			{ return m_pPause; }

	static D3DXVECTOR3			GetGrid()  			{ return m_Grid; }

	static void					plusQuantity(const int type)	{ objQuantity[type]++; }
	static void					minusQuantity(const int type)	{ objQuantity[type]--; }
	static int					GetQuantity(const int type)		{ return objQuantity[type]; }

	static D3DXVECTOR3			GetMaxStage()					{ return m_MaxStage; }
	static void					SetMaxStageX(const float posx)	{ m_MaxStage.x = posx; }
	static void					SetMaxStageY(const float posy)	{ m_MaxStage.y = posy; }

private:
	static const D3DXVECTOR3	m_Grid;					// 1マスの大きさ

	static CPlayer				*m_pPlayer;				// プレイヤーのクラス
	static CNormalBlock			*m_pNormalBlock;		// ブロックのクラス
	static CTargetBlock			*m_pTargetBlock;		// ブロックのターゲットのクラス
	static CGoal				*m_pGoal;				// ゴールのクラス
	static CGravityReverse		*m_pReverse;			// 重力反転のクラス
	static CSpiny				*m_pSpiny;				// とげのクラス
	static CPause				*m_pPause;				// ポーズ画面のクラス

	static int					objQuantity[OBJ_MAX];	// オブジェクトの残量

	static D3DXVECTOR3			m_MaxStage;				// ステージの最大値
};

#endif
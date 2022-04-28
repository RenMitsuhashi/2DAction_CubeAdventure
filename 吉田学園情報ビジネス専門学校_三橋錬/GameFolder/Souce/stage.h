//=============================================================================
//
// ステージ [stage.h]
// Author : 三橋錬
//
//=============================================================================
#ifndef _STAGE_H_
#define _STAGE_H_

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CPlayer;
class CNormalBlock;

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
class CStage
{
public:
	enum OBJTYPE
	{
		OBJ_NULL = 0,
		OBJ_NormalBlock,
		OBJ_Player,
		OBJ_MAX
	};

	CStage();
	~CStage();

	static HRESULT LoadFile(const char *FileName);

	static CPlayer				*GetPlayer() { return m_pPlayer; }
	static CNormalBlock			*GetNormalBlock() { return m_pNormalBlock; }

private:
	static void StageCreate(int x, int y);

	static void UnloadTexture();

	static const D3DXVECTOR3 m_Grid;	// 1マスの大きさ

	static int m_nMaxGridX;				// ステージの大きさX(1マスごと)
	static int m_nMaxGridY;				// ステージの大きさY(1マスごと)

	static std::vector<vector<string>> m_GridData;

	static bool m_isLoad[OBJ_MAX];		// テクスチャをロードしたらtrueに

	static CPlayer				*m_pPlayer;					// プレイヤーのクラス
	static CNormalBlock			*m_pNormalBlock;			// ブロックのクラス
};

#endif
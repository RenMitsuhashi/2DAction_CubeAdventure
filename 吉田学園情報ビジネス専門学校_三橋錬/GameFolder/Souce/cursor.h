//=============================================================================
//
// カーソル [cursor.h]
// Author : 三橋錬
//
//=============================================================================
#ifndef _CURSOR_H_
#define _CURSOR_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "scene2D.h"
#include "Stageload.h"
#include "targetcursor.h"

class CUIBg;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CCursor : public CScene2D, public CStageLoad
{
public:
	CCursor(CScene::PRIORITY nPriority = PRIORITY_CURSOR);
	~CCursor();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, LPDIRECT3DTEXTURE9 tex);
	void Uninit();
	void Update();
	void Draw();
	void DrawObjInfo();

	static CCursor *Create(D3DXVECTOR3 move, D3DXVECTOR3 size, LPDIRECT3DTEXTURE9 tex);

	D3DXVECTOR3 GetTargetPos() { return TargetPos; }
	int GetStopTime() { return m_stoptime; }

	int GetType() { return m_nType; }

private:
	int	m_nType;					// 設置するオブジェクトのタイプ
	D3DXVECTOR3 TargetPos;			// 設置するオブジェクトの移動目標地点

	float m_move;					// 設置するオブジェクトの1fあたりの移動量
	const float m_moveMax = 10.0f;	// ↑の最大値(10.0f)

	int m_stoptime;					// 設置するオブジェクトの静止時間
	const int m_stopMax = 180;		// ↑の最大値(3秒)

	int	m_nColisionType;			// 触れているオブジェクトのタイプ
	float m_Colisionmove;			// 触れているオブジェクトの1fあたりの移動量
	int m_Colisionstoptime;			// 触れているオブジェクトの静止時間
	D3DCOLORVALUE m_Colisioncol;	// 触れているオブジェクトの色

	int m_nSpinyDirection = 0;		// 棘の方向

	int m_nNowSave = 0;				// セーブ中か判断

	static CTargetCursor *m_pTargetCursor;
	D3DCOLORVALUE m_col;			// ブロックの色
};

#endif
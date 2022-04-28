//=============================================================================
//
// ゴール [goal.h]
// Author : 三橋錬
//
//=============================================================================
#ifndef _GOAL_H_
#define _GOAL_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "scene2D.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CGoal : public CScene2D
{
public:
	CGoal(CScene::PRIORITY nPriority = PRIORITY_GOAL);
	~CGoal();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, LPDIRECT3DTEXTURE9 tex);
	void Uninit();
	void Update();
	void Draw();

	static CGoal *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, LPDIRECT3DTEXTURE9 tex);

private:
	int m_nTime;	// テクスチャ座標更新までのフレーム数
	int m_nTexNum;	// 現在のテクスチャX座標
	const int m_nTimeMax = 4;	// テクスチャ座標更新までのフレーム数
	const int m_nTexMax = 4;	// テクスチャの分割数
};

#endif
//=============================================================================
//
// 重力反転 [gravityreverse.h]
// Author : 三橋錬
//
//=============================================================================
#ifndef _GRAVITYREVERSE_H_
#define _GRAVITYREVERSE_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "scene2D.h"

class CObjectBg;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CGravityReverse : public CScene2D
{
public:
	CGravityReverse(CScene::PRIORITY nPriority = PRIORITY_REVERSE);
	~CGravityReverse();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, LPDIRECT3DTEXTURE9 tex);
	void Uninit();
	void Update();
	void Draw();

	static CGravityReverse *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, LPDIRECT3DTEXTURE9 tex);

	CObjectBg *GetBg() { return m_pBg; }

private:
	bool m_bUseCool;			// クールタイム中か
	int m_nTime;				// 再度使用可能になるまでのフレーム数
	const int m_nTimeMax = 255;	// 再度使用可能になるまでのフレーム数

	CObjectBg *m_pBg = NULL;
};

#endif
//=============================================================================
//
// 弾発射ポリゴン [firingpolygon.h]
// Author : 三橋錬
//
//=============================================================================
#ifndef _FIRINGPOLYGON_H_
#define _FIRINGPOLYGON_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "scene.h"
#include "scene2D.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CFiringPolygon : public CScene2D
{
public:
	CFiringPolygon(CScene::PRIORITY nPriority = PRIORITY_UI);
	~CFiringPolygon();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CFiringPolygon *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size);
	static HRESULT Load();
	static void Unload();

private:
	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size);

	static LPDIRECT3DTEXTURE9		m_pTexture;		// テクスチャへのポインタ
	int								nTime;			// 軌跡クールタイム
	const int						nTimeMax = 16;	// 軌跡クールタイムの上限値
};

#endif
//=============================================================================
//
// シーン2D処理 [scene2D.h]
// Author : 三橋錬
//
//=============================================================================
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "scene.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)	// 頂点フォーマット

//*****************************************************************************
// 構造体定義
//*****************************************************************************
struct VERTEX_2D
{
	D3DXVECTOR3 pos;	// 頂点座標
	float rhw;			// 1.0f固定
	D3DCOLOR col;		// 頂点カラー
	D3DXVECTOR2 tex;	// テクスチャ座標
};

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CScene2D : public CScene
{
public:
	enum Direction
	{
		DIRECTION_NONE,
		DIRECTION_UP,
		DIRECTION_LEFT,
		DIRECTION_DOWN,
		DIRECTION_RIGHT,
		DIRECTION_MAX
	};

	CScene2D(PRIORITY nPriority = PRIORITY_NONE);
	virtual ~CScene2D();

	virtual HRESULT Init(LPDIRECT3DTEXTURE9 tex);
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();

	HRESULT Load(const char *aTextureName);

	void SetPositionDefault(D3DXVECTOR3 pos, D3DXVECTOR3 size);		// 位置更新
	void SetPositionCenter(D3DXVECTOR3 pos, D3DXVECTOR3 size);		// 位置更新

	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);					// テクスチャ割り当て

	void SetTexture(int ptnAnim, D3DXVECTOR2 split);				// テクスチャ分割
	void ScrollTexture(D3DXVECTOR3 move);							// テクスチャスクロール

	void SetColor(D3DCOLORVALUE col);

	void ColisionBlock();

	CScene *CoverBlock(CScene2D *scene);
	CScene *CoverMoveBlock(CScene2D *scene);

	void PlayerReCreate();

private:
	D3DXVECTOR3	m_pos;		// ポリゴンの位置
	D3DXVECTOR3	m_move;		// ポリゴンの移動量
	D3DXVECTOR3	m_size;		// ポリゴンのサイズ

	bool Colision(CScene *sceneA, CScene *sceneB);

protected:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;		// 頂点バッファへのポインタ
	LPDIRECT3DTEXTURE9		m_pTexture = NULL;		// テクスチャへのポインタ
};

#endif
//=============================================================================
//
// エフェクト [effect.h]
// Author : 三橋錬
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "Scene2D.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CEffect : public CScene2D
{
public:
	CEffect(CScene::PRIORITY nPriority = PRIORITY_EFFECT);
	~CEffect();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DCOLORVALUE color, D3DCOLORVALUE mincolor, D3DXVECTOR3 size, D3DXVECTOR3 minsize, int life, LPDIRECT3DTEXTURE9 tex);
	void Uninit();
	void Update();
	void Draw();

	static CEffect *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DCOLORVALUE color, D3DCOLORVALUE mincolor, D3DXVECTOR3 size, D3DXVECTOR3 minsize, int life, LPDIRECT3DTEXTURE9 tex);

protected:
	int m_nLife;

private:
	D3DCOLORVALUE m_Color;		// カラー値
	D3DCOLORVALUE m_MinColor;	// 減らすカラー値
	D3DXVECTOR3 m_MinSize;		// 減らすサイズ値
};

#endif

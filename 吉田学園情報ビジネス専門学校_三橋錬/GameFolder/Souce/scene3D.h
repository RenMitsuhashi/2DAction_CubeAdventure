//=============================================================================
//
// シーン3D処理 [scene3D.h]
// Author : 三橋錬
//
//=============================================================================
#ifndef _SCENE3D_H_
#define _SCENE3D_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "scene.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)	//頂点フォーマット

//*****************************************************************************
// 構造体定義
//*****************************************************************************
struct VERTEX_3D
{
	D3DXVECTOR3 pos;	// 頂点座標
	D3DXVECTOR3 nor;	// 法線ベクトル
	D3DCOLOR col;		// 頂点カラー
	D3DXVECTOR2 tex;	// テクスチャ座標
};

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CScene3D : public CScene
{
public:
	CScene3D(PRIORITY nPriority = PRIORITY_NONE);
	~CScene3D();

	HRESULT Init(LPDIRECT3DTEXTURE9 tex);
	void Uninit();
	void Update();
	void Draw();

	HRESULT Load(const char *aModelName);

	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);	// テクスチャ割り当て

	D3DXMATRIX GetMatrix() const			{ return m_mtxWorld; }
	void SetMatrix(const D3DXMATRIX& mtx)	{ m_mtxWorld = mtx; }

	D3DXVECTOR3 GetRot() const				{ return m_rot; }
	void SetRot(const D3DXVECTOR3& rot)		{ m_rot = rot; }
	void SetRotOld(const D3DXVECTOR3& rot)	{ m_rotold = rot; }

private:
	D3DXVECTOR3			m_pos;					// ポリゴンの位置
	D3DXVECTOR3			m_rot;					// 向き
	D3DXVECTOR3			m_rotold;				// 向き

	D3DXMATRIX			m_mtxWorld;				// ワールドマトリックス
	LPD3DXMESH			m_pMesh;				// メッシュ(頂点情報)へのポインタ
	LPD3DXBUFFER		m_pBuffMat;				// マテリアル（材質情報）へのポインタ
	DWORD				m_nNumMat;				// マテリアルの数
	LPDIRECT3DTEXTURE9	m_aTexture[4] = {};		// テクスチャ
};

#endif
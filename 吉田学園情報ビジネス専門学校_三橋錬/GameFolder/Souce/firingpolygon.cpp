//=============================================================================
//
// 弾発射ポリゴン [firingpolygon.cpp]
// Author : 三橋錬
//
//=============================================================================
#include "firingpolygon.h"
#include "manager.h"
#include "renderer.h"

#include "input.h"

#include "sound.h"
#include "mouse.h"

#include <assert.h>

LPDIRECT3DTEXTURE9	CFiringPolygon::m_pTexture = {};

//=============================================================================
// コンストラクタ
//=============================================================================
CFiringPolygon::CFiringPolygon(CScene::PRIORITY nPriority) : CScene2D(nPriority)
{
	
}

//=============================================================================
// デストラクタ
//=============================================================================
CFiringPolygon::~CFiringPolygon()
{

}

//=============================================================================
// テクスチャのロード
//=============================================================================
HRESULT CFiringPolygon::Load()
{
	LPDIRECT3DDEVICE9 pDevice;						//デバイスのポインタ
	pDevice = CManager::GetRenderer()->GetDevice();	//デバイスを取得

	D3DXCreateTextureFromFile(
		pDevice,
		"",
		&m_pTexture);

	return S_OK;
}

//=============================================================================
// テクスチャの破棄
//=============================================================================
void CFiringPolygon::Unload()
{
	//テクスチャ破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// ポリゴンの初期化処理
//=============================================================================
HRESULT CFiringPolygon::Init(void)
{
	CScene2D::Init();
	SetObjType(CScene::TYPE_NULL);

	return S_OK;
}

//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CFiringPolygon::Uninit(void)
{
	Release();
}

//=============================================================================
// ポリゴンの更新処理
//=============================================================================
void CFiringPolygon::Update(void)
{
	nTime--;

	if (nTime <= 0) { nTime = nTimeMax; }
}

//=============================================================================
// ポリゴンの描画処理
//=============================================================================
void CFiringPolygon::Draw(void)
{
	CScene2D::Draw();
}

CFiringPolygon *CFiringPolygon::Create(D3DXVECTOR3 pos, D3DXVECTOR3 speed, D3DXVECTOR3 size)
{
	CFiringPolygon* pCursor = new CFiringPolygon;

	if (pCursor != NULL)
	{
		pCursor->Init();
		pCursor->Set(pos, speed, size);
	}
	return pCursor;
}

void CFiringPolygon::Set(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size)
{
	SetPos(pos);
	SetMove(move);
	SetSize(size);
	SetDeath(false);

	nTime = nTimeMax;

	CScene2D::BindTexture(m_pTexture);
	CScene2D::SetPositionCenter(GetPos(), GetSize());
}
//=============================================================================
//
// 仮オブジェクト [tentativeobj.cpp]
// Author : 三橋錬
//
//=============================================================================
#include "tentativeobj.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CTentativeObj::CTentativeObj(CScene::PRIORITY nPriority) : CScene2D(nPriority)
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CTentativeObj::~CTentativeObj()
{

}

//=============================================================================
// ポリゴンの初期化処理
//=============================================================================
HRESULT CTentativeObj::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size)
{
	SetPos(pos);
	SetMove(move);
	SetSize(size);
	SetDeath(false);

	CScene2D::Init(NULL);

	return S_OK;
}

//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CTentativeObj::Uninit()
{
	Release(GetPriority());
}

CTentativeObj *CTentativeObj::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size)
{
	CTentativeObj* pTentativeObj = new CTentativeObj;

	if (pTentativeObj != NULL)
	{
		pTentativeObj->Init(pos + GetGrid() / 2, move, size);
	}
	return pTentativeObj;
}
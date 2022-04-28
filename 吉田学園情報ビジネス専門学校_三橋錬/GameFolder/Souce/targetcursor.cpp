//=============================================================================
//
// カーソル [cursor.cpp]
// Author : 三橋錬
//
//=============================================================================
#include "targetcursor.h"
#include "manager.h"
#include "renderer.h"

#include "input.h"
#include "keyboard.h"
#include "gamepad.h"
#include "mouse.h"
#include "stagebuild.h"
#include "cursor.h"

#include "sound.h"
#include "data.h"

#include <assert.h>

//=============================================================================
// コンストラクタ
//=============================================================================
CTargetCursor::CTargetCursor(CScene::PRIORITY nPriority) : CScene2D(nPriority)
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CTargetCursor::~CTargetCursor()
{

}

//=============================================================================
// ポリゴンの初期化処理
//=============================================================================
HRESULT CTargetCursor::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, LPDIRECT3DTEXTURE9 tex)
{
	SetPos(pos + GetGrid() / 2);
	SetMove(move);
	SetSize(size);
	SetDeath(false);
	SetobjType(OBJ_NULL);

	CScene2D::Init(tex);

	return S_OK;
}

//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CTargetCursor::Uninit()
{
	Release(GetPriority());
}

//=============================================================================
// ポリゴンの更新処理
//=============================================================================
void CTargetCursor::Update()
{
	D3DXVECTOR3 mouse = CStageBuild::GetCursor()->GetPos();
	D3DXVECTOR3 cursor = CStageBuild::GetCursor()->GetTargetPos();

	D3DXVECTOR3 pos = D3DXVECTOR3(floorf(mouse.x / GetSize().x) * GetSize().x + (cursor.x * GetGrid().x) - CData::GetMoveQuantity(), floorf(mouse.y / GetSize().y) * GetSize().y + (cursor.y * GetGrid().y), 0.0f);

	SetPositionCenter(pos + GetGrid() / 2, GetSize());

	SetPos(pos + GetGrid() / 2);
	SetPosX(pos.x + CData::GetMoveQuantity() + GetGrid().x / 2);

	if (!CData::GetNowGame())
	{
		D3DCOLORVALUE col;
		col.r = 255.0f;
		col.g = 255.0f;
		col.b = 255.0f;
		col.a = 128.0f;
		
		if (cursor.x == 0.0f && cursor.y == 0.0f || CStageBuild::GetCursor()->GetType() != OBJ_NormalBlock)
		{
			col.a = 0.0f;
		}

		SetColor(col);
	}
}

//=============================================================================
// ポリゴンの描画処理
//=============================================================================
void CTargetCursor::Draw()
{
	if (!CData::GetNowGame())
	{
		CScene2D::Draw();
	}
}

CTargetCursor *CTargetCursor::Create(D3DXVECTOR3 speed, D3DXVECTOR3 size, LPDIRECT3DTEXTURE9 tex)
{
	CTargetCursor* pTargetCursor = new CTargetCursor;

	if (pTargetCursor != NULL)
	{
		pTargetCursor->Init(CManager::GetRenderer()->GetMousePos(), speed, size, tex);
	}
	return pTargetCursor;
}
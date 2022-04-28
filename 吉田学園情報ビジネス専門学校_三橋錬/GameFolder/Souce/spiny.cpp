//=============================================================================
//
// とげ [spiny.cpp]
// Author : 三橋錬
//
//=============================================================================
#include "spiny.h"
#include "manager.h"
#include "renderer.h"
#include "Stageload.h"
#include "data.h"
#include "player.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CSpiny::CSpiny(CScene::PRIORITY nPriority) : CScene2D(nPriority)
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CSpiny::~CSpiny()
{

}

//=============================================================================
// ポリゴンの初期化処理
//=============================================================================
HRESULT CSpiny::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, int ptn, LPDIRECT3DTEXTURE9 tex)
{
	SetPos(pos);
	SetMove(move);
	SetSize(size);
	SetDeath(false);

	CScene2D::Init(tex);

	SetTexture(ptn, D3DXVECTOR2(2, 1));

	return S_OK;
}

//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CSpiny::Uninit()
{
	CScene2D::Uninit();
}

//=============================================================================
// ポリゴンの更新処理
//=============================================================================
void CSpiny::Update()
{
	if (CData::GetNowGame())
	{
		if (GetPtn() == 0)
		{
			if (GetColision(DIRECTION_UP) != NULL)
			{
				if (GetColision(DIRECTION_UP)->GetPriority() == PRIORITY_PLAYER)
				{
					if (CStageLoad::GetPlayer())
					{
						CStageLoad::GetPlayer()->SetDeath(true);
					}
				}
			}

			if (GetColision(DIRECTION_LEFT) != NULL)
			{
				if (GetColision(DIRECTION_LEFT)->GetPriority() == PRIORITY_PLAYER)
				{
					if (CStageLoad::GetPlayer())
					{
						CStageLoad::GetPlayer()->SetDeath(true);
					}
				}
			}

			if (GetColision(DIRECTION_RIGHT) != NULL)
			{
				if (GetColision(DIRECTION_RIGHT)->GetPriority() == PRIORITY_PLAYER)
				{
					if (CStageLoad::GetPlayer())
					{
						CStageLoad::GetPlayer()->SetDeath(true);
					}
				}
			}
		}

		else
		{
			if (GetColision(DIRECTION_DOWN) != NULL)
			{
				if (GetColision(DIRECTION_DOWN)->GetPriority() == PRIORITY_PLAYER)
				{
					if (CStageLoad::GetPlayer())
					{
						CStageLoad::GetPlayer()->SetDeath(true);
					}
				}
			}

			if (GetColision(DIRECTION_LEFT) != NULL)
			{
				if (GetColision(DIRECTION_LEFT)->GetPriority() == PRIORITY_PLAYER)
				{
					if (CStageLoad::GetPlayer())
					{
						CStageLoad::GetPlayer()->SetDeath(true);
					}
				}
			}

			if (GetColision(DIRECTION_RIGHT) != NULL)
			{
				if (GetColision(DIRECTION_RIGHT)->GetPriority() == PRIORITY_PLAYER)
				{
					if (CStageLoad::GetPlayer())
					{
						CStageLoad::GetPlayer()->SetDeath(true);
					}
				}
			}
		}
	}

	SetPositionCenter(GetPos(), GetSize());
	SetTexture(GetPtn(), D3DXVECTOR2(2, 1));
}

//=============================================================================
// ポリゴンの描画処理
//=============================================================================
void CSpiny::Draw()
{
	CScene2D::Draw();
}

CSpiny *CSpiny::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, int ptn, LPDIRECT3DTEXTURE9 tex)
{
	CSpiny* pSpiny = new CSpiny;

	if (pSpiny != NULL)
	{
		pSpiny->Init(pos, move, size, ptn, tex);
	}

	return pSpiny;
}
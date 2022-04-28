//=============================================================================
//
// 通常ブロック [normalblock.cpp]
// Author : 三橋錬
//
//=============================================================================
#include "normalblock.h"
#include "manager.h"
#include "renderer.h"
#include "Stageload.h"
#include "data.h"
#include "targetblock.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CNormalBlock::CNormalBlock(CScene::PRIORITY nPriority) : CScene2D(nPriority)
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CNormalBlock::~CNormalBlock()
{

}

//=============================================================================
// ポリゴンの初期化処理
//=============================================================================
HRESULT CNormalBlock::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXVECTOR3 targetpos, int stoptime, LPDIRECT3DTEXTURE9 tex)
{
	SetPos(pos);
	SetMove(move);
	SetSize(size);
	SetDeath(false);

	CScene2D::Init(tex);

	SetTargetPos(targetpos);
	SetStopTime(stoptime);
	m_targetpos = GetstartPos() + GetTargetPos();
	m_move = GetMove();
	m_bGoing = true;

	return S_OK;
}

//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CNormalBlock::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// ポリゴンの更新処理
//=============================================================================
void CNormalBlock::Update(void)
{
	if (CData::GetPause() &&
		CData::GetNowGame())
	{
		if ((GetMove().x > 0.0f && GetPos().x > m_targetpos.x) ||
			(GetMove().y > 0.0f && GetPos().y > m_targetpos.y))
		{
			SetPos(m_targetpos);

			SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

			m_bGo = !m_bGo;
		}

		else if ((GetMove().x < 0.0f && GetPos().x < m_targetpos.x) ||
				 (GetMove().y < 0.0f && GetPos().y < m_targetpos.y))
		{
			SetPos(m_targetpos);
			
			SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

			m_bGo = !m_bGo;
		}

		else if (GetMove() == D3DXVECTOR3(0.0f, 0.0f, 0.0f))
		{
			m_fTime++;

			if (m_fTime > GetStopTime())
			{
				m_fTime = 0;

				if (m_bGoing)
				{
					if (m_targetpos.x - GetstartPos().x > 0.0f)
					{
						m_targetpos.x -= GetTargetPos().x;
						SetMoveX(fabs(m_move.x) * -1.0f);
					}

					else
					{
						m_targetpos.x -= GetTargetPos().x;
						SetMoveX(fabs(m_move.x));
					}

					if (m_targetpos.y - GetstartPos().y > 0.0f)
					{
						m_targetpos.y -= GetTargetPos().y;
						SetMoveY(fabs(m_move.y) * -1.0f);
					}

					else
					{
						m_targetpos.y -= GetTargetPos().y;
						SetMoveY(fabs(m_move.y));
					}
				}

				else
				{
					m_targetpos = GetstartPos() + GetTargetPos();
					SetMoveX(m_move.x);
					SetMoveY(m_move.y);
				}

				m_bGo = !m_bGo;
				m_bGoing = !m_bGoing;
			}
		}
	}

	else
	{
		m_fTime = 0;
		m_bGo = true;
		m_bGoing = true;

		m_targetpos = GetstartPos() + GetTargetPos();
		SetMove(GetstartMove());
	}

	SetPositionCenter(GetPos(), GetSize());
}

//=============================================================================
// ポリゴンの描画処理
//=============================================================================
void CNormalBlock::Draw(void)
{
	CScene2D::Draw();
}

CNormalBlock *CNormalBlock::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXVECTOR3 targetpos, int stoptime, LPDIRECT3DTEXTURE9 tex)
{
	CNormalBlock* pNormalBlock = new CNormalBlock;

	if (pNormalBlock != NULL)
	{
		pNormalBlock->Init(pos, move, size, targetpos, stoptime, tex);

		pNormalBlock->m_fTime = 0;
		pNormalBlock->m_bGo = true;

		pNormalBlock->SetTargetPos(targetpos);
		pNormalBlock->SetStopTime(stoptime);
	}

	return pNormalBlock;
}
//=============================================================================
//
// ゴール [goal.cpp]
// Author : 三橋錬
//
//=============================================================================
#include "goal.h"
#include "manager.h"
#include "renderer.h"
#include "Stageload.h"
#include "data.h"
#include "targetblock.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CGoal::CGoal(CScene::PRIORITY nPriority) : CScene2D(nPriority)
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CGoal::~CGoal()
{

}

//=============================================================================
// ポリゴンの初期化処理
//=============================================================================
HRESULT CGoal::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, LPDIRECT3DTEXTURE9 tex)
{
	SetPos(pos);
	SetMove(move);
	SetSize(size);
	SetDeath(false);

	CScene2D::Init(tex);

	m_nTime = 0;
	m_nTexNum = 0;

	return S_OK;
}

//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CGoal::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// ポリゴンの更新処理
//=============================================================================
void CGoal::Update(void)
{
	if (CData::GetPause() &&
		CData::GetNowGame())
	{
		m_nTime++;

		if (m_nTime >= m_nTimeMax)
		{
			m_nTime = 0;
			m_nTexNum++;

			if (m_nTexNum >= m_nTexMax)
			{
				m_nTexNum = 0;
			}

			SetTexture(m_nTexNum, D3DXVECTOR2((float)m_nTexMax, 1.0f));
		}
	}

	else
	{
		SetTexture(0, D3DXVECTOR2((float)m_nTexMax, 1.0f));
	}

	SetPositionCenter(GetPos(), GetSize());
}

//=============================================================================
// ポリゴンの描画処理
//=============================================================================
void CGoal::Draw(void)
{
	CScene2D::Draw();
}

CGoal *CGoal::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, LPDIRECT3DTEXTURE9 tex)
{
	CGoal* pGoal = new CGoal;

	if (pGoal != NULL)
	{
		pGoal->Init(pos, move, size, tex);
	}

	return pGoal;
}
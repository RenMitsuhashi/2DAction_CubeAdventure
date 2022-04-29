//=============================================================================
//
// 重力反転 [gravityreverse.cpp]
// Author : 三橋錬
//
//=============================================================================
#include "gravityreverse.h"
#include "manager.h"
#include "renderer.h"
#include "Stageload.h"
#include "data.h"
#include "targetblock.h"
#include "objectbg.h"
#include "texture.h"
#include "player.h"
#include "sound.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CGravityReverse::CGravityReverse(CScene::PRIORITY nPriority) : CScene2D(nPriority)
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CGravityReverse::~CGravityReverse()
{

}

//=============================================================================
// ポリゴンの初期化処理
//=============================================================================
HRESULT CGravityReverse::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, LPDIRECT3DTEXTURE9 tex)
{
	SetPos(pos);
	SetMove(move);
	SetSize(size);
	SetDeath(false);

	CScene2D::Init(tex);

	m_pBg = CObjectBg::Create(pos, move, size, CTexture::GetTexture(CTexture::Tex_BgReverse));

	m_nTime = 0;

	return S_OK;
}

//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CGravityReverse::Uninit(void)
{
	m_pBg->SetDeath(true);
	CScene2D::Uninit();
}

//=============================================================================
// ポリゴンの更新処理
//=============================================================================
void CGravityReverse::Update(void)
{
	D3DCOLORVALUE col;
	col.r = 255.0f;
	col.g = 255.0f;
	col.b = 255.0f;
	col.a = 255.0f;

	D3DCOLORVALUE bgcol = col;

	if (CData::GetNowGame())
	{
		//=============================================================================
		// 使用後クールタイム
		//=============================================================================
		if (m_bUseCool)
		{
			m_nTime++;

			// 時間になったr再使用可
			if (m_nTime >= m_nTimeMax)
			{
				m_nTime = m_nTimeMax;
				m_bUseCool = false;
			}

			col.a = (float)m_nTime;
		}

		//=============================================================================
		// 使用可能
		//=============================================================================
		else
		{
			// プレイヤーに当たったら
			if (CoverBlock(this) != NULL)
			{
				if (CoverBlock(this)->GetPriority() == PRIORITY_PLAYER)
				{
					CManager::GetSound()->Play(CSound::SOUND_LABEL_SE_REVERSE);
					CManager::GetSound()->ControllVoice(CSound::SOUND_LABEL_SE_REVERSE, 0.5f);
					CManager::GetSound()->ControllPitch(CSound::SOUND_LABEL_SE_REVERSE, 10.0f, 5.0f);

					m_nTime = 0;
					m_bUseCool = true;

					// 重力を反転
					CData::SetGravity(CManager::GetData()->GetGravity() * -1.0f);
					CoverBlock(this)->SetMoveY(JUMP_HEIGHT * (Sign(CData::GetGravity() * -1.0f)));
				}
			}

			col.r = 0.0f;
			col.b = 0.0f;
		}
	}

	else
	{
		col.r = 0.0f;
		col.b = 0.0f;

		m_bUseCool = false;
		m_nTime = 0;
	}

	SetPositionCenter(GetPos(), GetSize());

	SetColor(col);
	m_pBg->SetColor(bgcol);
}

//=============================================================================
// ポリゴンの描画処理
//=============================================================================
void CGravityReverse::Draw(void)
{
	CScene2D::Draw();
}

CGravityReverse *CGravityReverse::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, LPDIRECT3DTEXTURE9 tex)
{
	CGravityReverse* pGravityReverse = new CGravityReverse;

	if (pGravityReverse != NULL)
	{
		pGravityReverse->Init(pos, move, size, tex);
	}

	return pGravityReverse;
}
//=============================================================================
//
// ゲームの背景 [gamebg.h]
// Author : 三橋錬
//
//=============================================================================
#include "gamebg.h"
#include "manager.h"
#include "renderer.h"
#include "stageload.h"
#include "player.h"
#include "effect.h"
#include "data.h"
#include "texture.h"
#include "objectbg.h"

CObjectBg *CGameBg::m_pObjectBg[] = {};
CEffect *CGameBg::m_pEffect[] = {};
float CGameBg::m_fTargetPosY[] = {};

//=============================================================================
// コンストラクタ
//=============================================================================
CGameBg::CGameBg(CScene::PRIORITY nPriority) : CScene2D(nPriority)
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CGameBg::~CGameBg()
{

}

//=============================================================================
// ポリゴンの初期化処理
//=============================================================================
HRESULT CGameBg::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, LPDIRECT3DTEXTURE9 tex)
{
	SetPos(pos);
	SetMove(move);
	SetSize(size);
	SetDeath(false);

	CScene2D::Init(tex);

	// チュートリアル用ポリゴンの初期化
	for (int nCnt = 0; nCnt < UI_MAX; nCnt++)
	{
		m_pObjectBg[nCnt] = NULL;
	}

	// エフェクトの初期化
	for (int nCnt = 0; nCnt < EFFECT_MAX; nCnt++)
	{
		m_pEffect[nCnt] = NULL;
	}

	// エフェクトを降らせるタイミング
	m_nTime = 0;

	D3DCOLORVALUE col;
	col.r = 255.0f;
	col.g = 255.0f;
	col.b = 255.0f;
	col.a = 0.0f;

	SetColor(col);

	return S_OK;
}

//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CGameBg::Uninit()
{
	CScene2D::Uninit();
}

//=============================================================================
// ポリゴンの更新処理
//=============================================================================
void CGameBg::Update()
{
	if (CData::GetPause() &&
		CData::GetNowGame())
	{
		m_nTime++;
		float grav = CData::GetGravity();

		// エフェクトの移動速度を重力に応じて変える
		float m_EffectSpeed = m_fEffectBaseSpeed * grav;

		// エフェクトのスポーン位置Y(0)
		float effectspawnY = 0.0f;

		// エフェクトのスポーン位置Xをランダムにする
		std::random_device rnd;
		std::mt19937 mt(rnd());

		// 青
		D3DCOLORVALUE col;
		col.r = 0.0f;
		col.g = 0.0f;
		col.b = 255.0f;
		col.a = 255.0f;

		D3DCOLORVALUE mincol;
		mincol.r = 0.0f;
		mincol.g = 0.0f;
		mincol.b = 0.0f;
		mincol.a = 0.0f;

		float gravcol = fabs(grav) - CPlayer::GetMinGrav();

		float gravsplit = CPlayer::GetMaxGrav() - CPlayer::GetMinGrav() - 0.2f;
		float gravsplitnum = 0.4f;

		//=============================================================================
		// 色の変更
		//=============================================================================
		if (gravcol < 1.05f)
		{
			// 水色にする
			col.g = 255.0f;
			gravsplit -= gravsplitnum;

			if (gravcol < 0.75f)
			{
				// 緑にする
				col.b = 0.0f;
				gravsplit -= gravsplitnum;

				if (gravcol < 0.45f)
				{
					// 黄色にする
					col.r = 255.0f;
					gravsplit -= gravsplitnum;

					if (gravcol < 0.15f)
					{
						// 赤にする
						col.g = 0.0f;
						gravsplit -= gravsplitnum;
					}
				}
			}
		}

		// 背景の色
		D3DCOLORVALUE colbg = col;
		colbg.a = 24.0f;

		SetColor(colbg);

		std::uniform_real_distribution<> randsize(15, 25);
		float sizerand = randsize(mt);

		//=============================================================================
		// エフェクト作成
		//=============================================================================
		if (m_nTime > (float)m_nEffectSpawnTime)
		{
			m_nTime = 0;

			for (int nCnt = 0; nCnt < EFFECT_MAX; nCnt++)
			{
				if (!m_pEffect[nCnt])
				{
					// エフェクトのスポーン位置Xをランダムに決める
					std::uniform_real_distribution<> randX(0.0f, SCREEN_WIDTH);

					// 重力が上向きならスポーン位置を変える
					if (CData::GetGravity() < 0.0f)
					{
						effectspawnY = SCREEN_HEIGHT;
					}

					// スポーン位置
					D3DXVECTOR3 effectspawn = D3DXVECTOR3((float)randX(mt), effectspawnY, 0.0f);

					// エフェクトの移動量をランダムに
					std::uniform_real_distribution<> randmove(1.0f, 2.0f);
					D3DXVECTOR3 effectmove = D3DXVECTOR3(0.0f, m_EffectSpeed * (float)randmove(mt), 0.0f);

					// 生成
					m_pEffect[nCnt] = CEffect::Create(effectspawn, effectmove, col, mincol, D3DXVECTOR3(sizerand, sizerand, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 9999, CTexture::GetTexture(CTexture::Tex_Effect));
					break;
				}

				else
				{
					// エフェクトが役目を果たしたら解放
					if (m_pEffect[nCnt]->GetDeath())
					{
						m_pEffect[nCnt] = NULL;
						continue;
					}
				}
			}
		}

		//=============================================================================
		// チュートリアル用ポリゴン作成
		//=============================================================================
		float PlayerPosX = CStageLoad::GetPlayer()->GetPos().x;

		if (CData::GetNextStage() == CData::Stage_Tutorial)
		{
			// 移動チュートリアル
			if (!m_pObjectBg[UI_WASD])
			{
				m_fTargetPosY[UI_WASD] = 450.0f;
				m_pObjectBg[UI_WASD] = CObjectBg::Create(D3DXVECTOR3(275.0f, SCREEN_HEIGHT + 250.0f, 0.0f), D3DXVECTOR3(0.0f, -10.0f, 0.0f), D3DXVECTOR3(400.0f, 225.0f, 0.0f), CTexture::GetTexture(CTexture::Tex_Tutorialwasd));
			}

			// ジャンプ
			if (!m_pObjectBg[UI_JUMP] && PlayerPosX >= 550.0f)
			{
				m_fTargetPosY[UI_JUMP] = 450.0f;
				m_pObjectBg[UI_JUMP] = CObjectBg::Create(D3DXVECTOR3(700.0f, SCREEN_HEIGHT + 250.0f, 0.0f), D3DXVECTOR3(0.0f, -10.0f, 0.0f), D3DXVECTOR3(400.0f, 225.0f, 0.0f), CTexture::GetTexture(CTexture::Tex_Tutorialjump));
			}

			// 重力反転
			if (!m_pObjectBg[UI_GRAVITY_REVERSE] && PlayerPosX >= 1250.0f)
			{
				m_fTargetPosY[UI_GRAVITY_REVERSE] = 250.0f;
				m_pObjectBg[UI_GRAVITY_REVERSE] = CObjectBg::Create(D3DXVECTOR3(1737.5f, SCREEN_HEIGHT + 250.0f, 0.0f), D3DXVECTOR3(0.0f, -10.0f, 0.0f), D3DXVECTOR3(400.0f, 225.0f, 0.0f), CTexture::GetTexture(CTexture::Tex_TutorialGravityReverse));
			}

			// 重力増加減少
			if (!m_pObjectBg[UI_GRAVITY_UP_DOWN] && PlayerPosX >= 2250.0f)
			{
				m_fTargetPosY[UI_GRAVITY_UP_DOWN] = 250.0f;
				m_pObjectBg[UI_GRAVITY_UP_DOWN] = CObjectBg::Create(D3DXVECTOR3(2750.0f, SCREEN_HEIGHT + 250.0f, 0.0f), D3DXVECTOR3(0.0f, -10.0f, 0.0f), D3DXVECTOR3(400.0f, 225.0f, 0.0f), CTexture::GetTexture(CTexture::Tex_TutorialGravityUpDown));
			}

			// ゴール
			if (!m_pObjectBg[UI_GOAL] && PlayerPosX >= 3350.0f)
			{
				m_fTargetPosY[UI_GOAL] = 700.0f;
				m_pObjectBg[UI_GOAL] = CObjectBg::Create(D3DXVECTOR3(3550.0f, SCREEN_HEIGHT + 250.0f, 0.0f), D3DXVECTOR3(0.0f, -10.0f, 0.0f), D3DXVECTOR3(400.0f, 225.0f, 0.0f), CTexture::GetTexture(CTexture::Tex_TutorialGoal));
			}

			for (int nCnt = 0; nCnt < UI_MAX; nCnt++)
			{
				if (m_pObjectBg[nCnt])
				{
					// 指定した位置までポリゴンを上にせり上げる
					if (m_pObjectBg[nCnt]->GetPos().y < m_fTargetPosY[nCnt])
					{
						m_pObjectBg[nCnt]->SetPosY(m_fTargetPosY[nCnt]);
						m_pObjectBg[nCnt]->SetMoveY(0.0f);
					}
				}
			}
		}
	}

	SetPositionCenter(GetPos(), GetSize());
}

//=============================================================================
// ポリゴンの描画処理
//=============================================================================
void CGameBg::Draw()
{
	if (CData::GetPause() &&
		CData::GetNowGame())
	{
		CScene2D::Draw();
	}
}

CGameBg *CGameBg::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, LPDIRECT3DTEXTURE9 tex)
{
	CGameBg* pBg = new CGameBg;

	if (pBg != NULL)
	{
		pBg->Init(pos, move, size, tex);
	}
	return pBg;
}
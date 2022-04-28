//=============================================================================
//
// スコア [score.cpp]
// Author : 
//
//=============================================================================
#include "score.h"
#include "manager.h"
#include "renderer.h"

#include "data.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CScore::CScore(CScene::PRIORITY nPriority) : CScene(nPriority)
{
	for (int nCnt = 0; nCnt < SCORE_DIGITS; nCnt++)	m_apNumber[nCnt] = 0;
	m_nScore = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CScore::~CScore()
{

}

//=============================================================================
// ポリゴンの初期化処理
//=============================================================================
HRESULT CScore::Init(void)
{
	for (int nCnt = 0; nCnt < SCORE_DIGITS; nCnt++)	m_apNumber[nCnt] = 0;
	m_nScore = 0;

	return S_OK;
}

//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CScore::Uninit(void)
{
	for (int nCnt = 0; nCnt < SCORE_DIGITS; nCnt++)
	{
		if (m_apNumber[nCnt] != NULL)
		{
			m_apNumber[nCnt]->Uninit();
			m_apNumber[nCnt] = NULL;
		}
	}
}

//=============================================================================
// ポリゴンの更新処理
//=============================================================================
void CScore::Update(void)
{
	CData *pData;
	pData = CManager::GetData();

	m_nScore = pData->GetScore();

	if (m_nScore > MAX_SCORE)
	{
		m_nScore = MAX_SCORE;
	}

	for (int nCnt = 0; nCnt < SCORE_DIGITS; nCnt++)
	{
		if (nCnt == 0)
		{
			m_apNumber[nCnt]->SetNumber(m_nScore / (int)powf(10, SCORE_DIGITS - 1));
		}
		else if (nCnt == SCORE_DIGITS - 1)
		{
			m_apNumber[nCnt]->SetNumber(m_nScore % 10);
		}
		else
		{
			m_apNumber[nCnt]->SetNumber(m_nScore % (int)powf(10.0f, SCORE_DIGITS - (float)nCnt) / (int)powf(10.0f, SCORE_DIGITS - 1.0f - (float)nCnt));
		}
	}
}

//=============================================================================
// ポリゴンの描画処理
//=============================================================================
void CScore::Draw(void)
{
	for (int nCnt = 0; nCnt < SCORE_DIGITS; nCnt++)
	{
		m_apNumber[nCnt]->Draw();
	}
}

void CScore::SetScore(int nScore)
{
	m_nScore = nScore;
}

CScore *CScore::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScore* pScore = new CScore;

	if (pScore != NULL)
	{
		pScore->Init();
		pScore->Set(pos, size);
	}
	return pScore;
}

void CScore::Set(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	m_pos = pos;
	m_size = size;

	for (int nCnt = 0; nCnt < SCORE_DIGITS; nCnt++)
	{
		m_apNumber[nCnt] = CNumber::Create(D3DXVECTOR3(pos.x + (size.x * nCnt) * 2.0f, pos.y, 0.0f), D3DXVECTOR3(size.x, size.y, 0.0f));
	}
}
//=============================================================================
//
// クリアタイム [time.cpp]
// Author : 三橋錬
//
//=============================================================================
#include "time.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "uibg.h"

#include "data.h"

CUIBg *CTime::m_pUIBg[] = {};
CNumber *CTime::m_apNumber[] = {};

//=============================================================================
// コンストラクタ
//=============================================================================
CTime::CTime(CScene::PRIORITY nPriority) : CScene2D(nPriority)
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CTime::~CTime()
{

}

//=============================================================================
// ポリゴンの初期化処理
//=============================================================================
HRESULT CTime::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	for (int nCnt = 0; nCnt < TIME_DIGITS; nCnt++)	m_apNumber[nCnt] = 0;

	CScene2D::Init(CTexture::GetTexture(CTexture::Tex_Number));

	for (int nCnt = 0; nCnt < TIME_DIGITS; nCnt++)
	{
		m_pUIBg[nCnt] = CUIBg::Create(D3DXVECTOR3(pos.x + (size.x * nCnt), pos.y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(size.x, size.y, 0.0f), CTexture::GetTexture(CTexture::Tex_Fade));
		m_pUIBg[nCnt]->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 64.0f));

		m_apNumber[nCnt] = CNumber::Create(D3DXVECTOR3(pos.x + (size.x * nCnt), pos.y, 0.0f), D3DXVECTOR3(size.x, size.y, 0.0f), CTexture::GetTexture(CTexture::Tex_Number));
	}

	int nTime = CData::GetTime();
	int nNum[TIME_DIGITS];

	int nScore1 = 10;
	int nScore2 = 1;

	for (int nCnt = 0; nCnt < TIME_DIGITS - 1; nCnt++)
	{
		nScore1 *= 10;
		nScore2 *= 10;
	}

	for (int nCnt = 0; nCnt < TIME_DIGITS; nCnt++)
	{
		nNum[nCnt] = nTime % nScore1 / nScore2;

		nScore1 /= 10;
		nScore2 /= 10;
	}

	for (int nCnt = 0; nCnt < TIME_DIGITS; nCnt++)
	{
		SetTexture(nNum[nCnt], D3DXVECTOR2(10.0f, 1.0f));
	}

	return S_OK;
}

//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CTime::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// ポリゴンの更新処理
//=============================================================================
void CTime::Update(void)
{
	int nTime = CData::GetTime();
	int nNum[TIME_DIGITS];

	int nScore1 = 10;
	int nScore2 = 1;

	for (int nCnt = 0; nCnt < TIME_DIGITS - 1; nCnt++)
	{
		nScore1 *= 10;
		nScore2 *= 10;
	}

	for (int nCnt = 0; nCnt < TIME_DIGITS; nCnt++)
	{
		nNum[nCnt] = nTime % nScore1 / nScore2;

		nScore1 *= 0.1f;
		nScore2 *= 0.1f;
	}

	for (int nCnt = 0; nCnt < TIME_DIGITS; nCnt++)
	{
		m_apNumber[nCnt]->SetTexture(nNum[nCnt], D3DXVECTOR2(10.0f, 1.0f));
	}
}

//=============================================================================
// ポリゴンの描画処理
//=============================================================================
void CTime::Draw(void)
{
	for (int nCnt = 0; nCnt < TIME_DIGITS; nCnt++)
	{
		m_pUIBg[nCnt]->Draw();
		m_apNumber[nCnt]->Draw();
	}
}

CTime *CTime::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CTime* pTime = new CTime;

	if (pTime != NULL)
	{
		pTime->Init(pos, size);
	}
	return pTime;
}
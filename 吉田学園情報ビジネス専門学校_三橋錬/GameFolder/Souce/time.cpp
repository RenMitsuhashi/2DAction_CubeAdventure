//=============================================================================
//
// �N���A�^�C�� [time.cpp]
// Author : �O���B
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
// �R���X�g���N�^
//=============================================================================
CTime::CTime(CScene::PRIORITY nPriority) : CScene2D(nPriority)
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTime::~CTime()
{

}

//=============================================================================
// �|���S���̏���������
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
// �|���S���̏I������
//=============================================================================
void CTime::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// �|���S���̍X�V����
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
// �|���S���̕`�揈��
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
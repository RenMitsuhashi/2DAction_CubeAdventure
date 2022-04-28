//=============================================================================
//
// ���S�񐔃J�E���g [deathcount.cpp]
// Author : �O���B
//
//=============================================================================
#include "deathcount.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "uibg.h"

#include "data.h"

CUIBg *CDeathCount::m_pUIBg[] = {};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CDeathCount::CDeathCount(CScene::PRIORITY nPriority) : CScene2D(nPriority)
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CDeathCount::~CDeathCount()
{

}

//=============================================================================
// �|���S���̏���������
//=============================================================================
HRESULT CDeathCount::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	for (int nCnt = 0; nCnt < DEATH_DIGITS; nCnt++)	m_apNumber[nCnt] = 0;

	CScene2D::Init(CTexture::GetTexture(CTexture::Tex_Number));

	for (int nCnt = 0; nCnt < DEATH_DIGITS; nCnt++)
	{
		m_pUIBg[nCnt] = CUIBg::Create(D3DXVECTOR3(pos.x + (size.x * nCnt), pos.y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(size.x, size.y, 0.0f), CTexture::GetTexture(CTexture::Tex_Fade));
		m_pUIBg[nCnt]->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 64.0f));
		
		m_apNumber[nCnt] = CNumber::Create(D3DXVECTOR3(pos.x + (size.x * nCnt), pos.y, 0.0f), D3DXVECTOR3(size.x, size.y, 0.0f), CTexture::GetTexture(CTexture::Tex_Number));
	}

	int nDeathCount = CData::GetDeathCount();
	int nNum[DEATH_DIGITS];

	int nScore1 = 10;
	int nScore2 = 1;

	for (int nCnt = 0; nCnt < DEATH_DIGITS; nCnt++)
	{
		nScore1 *= 10;
		nScore2 *= 10;
	}

	for (int nCnt = 0; nCnt < DEATH_DIGITS; nCnt++)
	{
		nNum[nCnt] = nDeathCount % nScore1 / nScore2;

		nScore1 /= 10;
		nScore2 /= 10;
	}

	for (int nCnt = 0; nCnt < DEATH_DIGITS; nCnt++)
	{
		SetTexture(nNum[nCnt], D3DXVECTOR2(10.0f, 1.0f));
	}

	return S_OK;
}

//=============================================================================
// �|���S���̏I������
//=============================================================================
void CDeathCount::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// �|���S���̍X�V����
//=============================================================================
void CDeathCount::Update(void)
{
	int nDeathCount = CData::GetDeathCount();
	int nNum[DEATH_DIGITS];

	int nScore1 = 10;
	int nScore2 = 1;

	for (int nCnt = 0; nCnt < DEATH_DIGITS - 1; nCnt++)
	{
		nScore1 *= 10;
		nScore2 *= 10;
	}

	for (int nCnt = 0; nCnt < DEATH_DIGITS; nCnt++)
	{
		nNum[nCnt] = nDeathCount % nScore1 / nScore2;

		nScore1 /= 10;
		nScore2 /= 10;
	}

	for (int nCnt = 0; nCnt < DEATH_DIGITS; nCnt++)
	{
		m_apNumber[nCnt]->SetTexture(nNum[nCnt], D3DXVECTOR2(10.0f, 1.0f));
	}
}

//=============================================================================
// �|���S���̕`�揈��
//=============================================================================
void CDeathCount::Draw(void)
{
	for (int nCnt = 0; nCnt < DEATH_DIGITS; nCnt++)
	{
		m_pUIBg[nCnt]->Draw();
		m_apNumber[nCnt]->Draw();
	}
}

CDeathCount *CDeathCount::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CDeathCount* pDeathCount = new CDeathCount;

	if (pDeathCount != NULL)
	{
		pDeathCount->Init(pos, size);
	}
	return pDeathCount;
}
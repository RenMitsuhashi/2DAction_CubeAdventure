//=============================================================================
//
// データ [data.cpp]
// Author : 三橋錬
//
//=============================================================================
#include "data.h"

CManager::MODE CData::m_NowScene = CManager::MODE_TITLE;
bool CData::m_bNowGame = false;
bool CData::m_bPause = false;
bool CData::m_bLive = false;
float CData::m_fGravity = 1.0f;
int CData::m_nNextStage = Stage_Tutorial;
int CData::m_nDeathCount = 0;
int CData::m_nTime = 0;
float CData::m_fMoveQuantity = 0;

//=============================================================================
// コンストラクタ
//=============================================================================
CData::CData()
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CData::~CData()
{

}

//=============================================================================
// リセット
//=============================================================================
void CData::DataReset()
{
	m_bNowGame = true;
	m_bPause = true;
	m_bLive = true;
	m_fGravity = 1.0f;
	m_nDeathCount = 0;
	m_nTime = 0;
}
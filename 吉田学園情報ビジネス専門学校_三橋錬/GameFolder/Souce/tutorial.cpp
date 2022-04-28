//=============================================================================
//
// チュートリアルシーン [tutorial.h]
// Author : 三橋錬
//
//=============================================================================
#include "tutorial.h"
#include "input.h"

#include "tutorialbg.h"
#include "cursor.h"
#include "player.h"
#include "normalblock.h"

CTutorialBg		*CTutorial::m_pBg = NULL;
CCursor			*CTutorial::m_pCursor = NULL;
CPlayer			*CTutorial::m_pPlayer = NULL;
CNormalBlock	*CTutorial::m_pNormalBlock = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CTutorial::CTutorial()
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CTutorial::~CTutorial()
{

}

HRESULT CTutorial::Init()
{
	//=============================================================================
	// テクスチャのロード
	//=============================================================================
	CTutorialBg::Load();
	CCursor::Load();
	CPlayer::Load();
	CNormalBlock::Load();

	//=============================================================================
	// 各種オブジェクトの生成
	//=============================================================================
	m_pBg = CTutorialBg::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));
	m_pCursor = CCursor::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(20, 20, 0.0f));
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(20, 20, 0.0f));
	m_pNormalBlock = CNormalBlock::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT - 10.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1000.0f, 20.0f, 0.0f));
	m_pNormalBlock = CNormalBlock::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2 + 320, 0.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXVECTOR3(300.0f, 20.0f, 0.0f));

	return S_OK;
}

void CTutorial::Uninit()
{
	CScene::ReleaseAll();

	CTutorialBg::Unload();
	CCursor::Unload();
	CPlayer::Unload();
	CNormalBlock::Unload();
}

void CTutorial::Update()
{

}

void CTutorial::Draw()
{

}
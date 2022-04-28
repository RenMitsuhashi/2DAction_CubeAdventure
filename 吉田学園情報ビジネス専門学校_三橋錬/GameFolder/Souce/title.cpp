//=============================================================================
//
// タイトルシーン [title.cpp]
// Author : 三橋錬
//
//=============================================================================
#include "title.h"
#include "scene.h"
#include "texture.h"
#include "screenbg.h"
#include "modeselect.h"
#include "sound.h"

CScreenBg *CTitle::m_pScreenBg[] = {};
CModeSelect *CTitle::m_pModeSelect = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CTitle::CTitle()
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CTitle::~CTitle()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CTitle::Init()
{
	m_pScreenBg[Title_Bg] = CScreenBg::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), CTexture::GetTexture(CTexture::Tex_BgTitle));
	m_pScreenBg[Title_Game] = CScreenBg::Create(D3DXVECTOR3(450.0f, SCREEN_HEIGHT / 2 + 150.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(300.0f, 75.0f, 0.0f), CTexture::GetTexture(CTexture::Tex_TitleUIGame));
	m_pScreenBg[Title_Build] =CScreenBg::Create(D3DXVECTOR3(450.0f, SCREEN_HEIGHT / 2 + 250.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(300.0f, 75.0f, 0.0f), CTexture::GetTexture(CTexture::Tex_TitleUIBuild));
	m_pScreenBg[Title_Quit] = CScreenBg::Create(D3DXVECTOR3(450.0f, SCREEN_HEIGHT / 2 + 350.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(300.0f, 75.0f, 0.0f), CTexture::GetTexture(CTexture::Tex_TitleUIQuit));

	D3DXVECTOR3 pos = m_pScreenBg[Title_Game]->GetPos();
	pos.x -= m_pScreenBg[Title_Game]->GetSize().x / 1.2f;

	m_pModeSelect = CModeSelect::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(75.0f, 75.0f, 0.0f), CTexture::GetTexture(CTexture::Tex_TitleModeSelect));

	CManager::GetSound()->Play(CSound::SOUND_LABEL_BGM_TITLE);
	CManager::GetSound()->ControllVoice(CSound::SOUND_LABEL_BGM_TITLE, 0.3f);
	CManager::GetSound()->ControllPitch(CSound::SOUND_LABEL_BGM_TITLE, 9.0f, 10.0f);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CTitle::Uninit()
{
	CScene::ReleaseAll();
}

//=============================================================================
// 更新処理
//=============================================================================
void CTitle::Update()
{

}

//=============================================================================
// 描画処理
//=============================================================================
void CTitle::Draw()
{

}
//=============================================================================
//
// ステージビルダーシーン [stagebuild.cpp]
// Author : 三橋錬
//
//=============================================================================
#include "stagebuild.h"
#include "scene.h"
#include "Stageload.h"
#include "cursor.h"
#include "number.h"
#include "texture.h"
#include "data.h"
#include "sound.h"

CCursor *CStageBuild::m_pCursor = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CStageBuild::CStageBuild()
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CStageBuild::~CStageBuild()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CStageBuild::Init()
{
	CStageLoad::LoadFile("data\\stage\\stage.csv");

	CData::SetNowGame(false);
	CData::SetPause(true);

	m_pCursor = CCursor::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(GetGrid().x, GetGrid().y, 0.0f), CTexture::GetTexture(NULL));

	CManager::GetSound()->Play(CSound::SOUND_LABEL_BGM_BUILD);
	CManager::GetSound()->ControllVoice(CSound::SOUND_LABEL_BGM_BUILD, 0.1f);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CStageBuild::Uninit()
{
	CScene::ReleaseAll();
}

//=============================================================================
// 更新処理
//=============================================================================
void CStageBuild::Update()
{

}

//=============================================================================
// 描画処理
//=============================================================================
void CStageBuild::Draw()
{

}
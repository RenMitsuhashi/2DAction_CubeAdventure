//=============================================================================
//
// ゲームシーン [game.cpp]
// Author : 三橋錬
//
//=============================================================================
#include "game.h"
#include "scene.h"
#include "Stageload.h"
#include "number.h"
#include "texture.h"
#include "light.h"
#include "planet.h"
#include "gamebg.h"
#include "data.h"
#include "sound.h"

CPlanet	*CGame::m_pPlanet = NULL;
CLight *CGame::m_pLight = NULL;
CGameBg *CGame::m_pGameBg = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CGame::CGame()
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CGame::~CGame()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CGame::Init()
{
	m_pLight = CLight::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(100.0f, -100.0f, 0.0f), 0);
	m_pPlanet = CPlanet::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), CTexture::GetTexture(CTexture::Tex_Planet));

	// ステージによって読み込むファイルを変更
	switch (CData::GetNextStage())
	{
	case CData::Stage_Tutorial:
		// チュートリアル
		CStageLoad::LoadFile("data\\stage\\stage_tutorial.csv");

		break;

	case CData::Stage_01:
		// ステージ1
		CStageLoad::LoadFile("data\\stage\\stage01.csv");

		break;

	case CData::Stage_Build:
		// ビルダーで作成したステージ
		CStageLoad::LoadFile("data\\stage\\stage.csv");

		break;

	default:

		break;
	}

	m_pGameBg = CGameBg::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), CTexture::GetTexture(CTexture::Tex_Fade));

	CManager::GetSound()->Play(CSound::SOUND_LABEL_BGM_GAME);
	CManager::GetSound()->ControllVoice(CSound::SOUND_LABEL_BGM_GAME, 0.3f);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CGame::Uninit()
{
	CScene::ReleaseAll();
}

//=============================================================================
// 更新処理
//=============================================================================
void CGame::Update()
{
	
}

//=============================================================================
// 描画処理
//=============================================================================
void CGame::Draw()
{

}
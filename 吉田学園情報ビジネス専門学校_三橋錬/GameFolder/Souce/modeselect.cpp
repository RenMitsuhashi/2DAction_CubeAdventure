//=============================================================================
//
// カーソル [modeselect.cpp]
// Author : 三橋錬
//
//=============================================================================
#include "modeselect.h"
#include "manager.h"
#include "renderer.h"
#include "keyboard.h"
#include "title.h"
#include "screenbg.h"
#include "fade.h"
#include "sound.h"
#include "data.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CModeSelect::CModeSelect(CScene::PRIORITY nPriority) : CScene2D(nPriority)
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CModeSelect::~CModeSelect()
{

}

//=============================================================================
// ポリゴンの初期化処理
//=============================================================================
HRESULT CModeSelect::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, LPDIRECT3DTEXTURE9 tex)
{
	SetPos(pos);
	SetMove(move);
	SetSize(size);
	SetDeath(false);

	CScene2D::Init(tex);

	m_nSelect = CTitle::Title_Game;

	return S_OK;
}

//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CModeSelect::Uninit()
{
	CScene2D::Uninit();
}

//=============================================================================
// ポリゴンの更新処理
//=============================================================================
void CModeSelect::Update()
{
	if (CFade::GetFade() == CFade::FADE_NONE)
	{
		// カーソルを上へ
		if (CManager::GetKeyboard()->GetTrigger(DIK_W) ||
			CManager::GetKeyboard()->GetTrigger(DIK_UP))
		{
			CManager::GetSound()->Play(CSound::SOUND_LABEL_SE_CURSOR);
			CManager::GetSound()->ControllVoice(CSound::SOUND_LABEL_SE_CURSOR, 0.3f);

			m_nSelect--;

			if (m_nSelect < CTitle::Title_Game)
			{
				m_nSelect = CTitle::Title_Quit;
			}
		}

		// カーソルを下へ
		if (CManager::GetKeyboard()->GetTrigger(DIK_S) ||
			CManager::GetKeyboard()->GetTrigger(DIK_DOWN))
		{
			CManager::GetSound()->Play(CSound::SOUND_LABEL_SE_CURSOR);
			CManager::GetSound()->ControllVoice(CSound::SOUND_LABEL_SE_CURSOR, 0.3f);

			m_nSelect++;

			if (m_nSelect > CTitle::Title_Quit)
			{
				m_nSelect = CTitle::Title_Game;
			}
		}

		for (int objCnt = CTitle::Title_Game; objCnt < CTitle::Title_Max; objCnt++)
		{
			// オブジェクトサイズを初期値に
			CTitle::GetScreenBg(objCnt)->SetSize(D3DXVECTOR3(300.0f, 75.0f, 0.0f));
		}
		// 選ばれたオブジェクトをちょっと大きく
		CTitle::GetScreenBg(m_nSelect)->SetSize(D3DXVECTOR3(350.0f, 100.0f, 0.0f));

		D3DXVECTOR3 pos = CTitle::GetScreenBg(m_nSelect)->GetPos();
		pos.x = GetPos().x;
		SetPositionCenter(pos, GetSize());

		// ENTERキーで確定
		if (CManager::GetKeyboard()->GetTrigger(DIK_SPACE) ||
			CManager::GetKeyboard()->GetTrigger(DIK_RETURN))
		{
			CManager::GetSound()->Play(CSound::SOUND_LABEL_SE_PRESS);
			CManager::GetSound()->ControllVoice(CSound::SOUND_LABEL_SE_PRESS, 0.5f);

			// シーン遷移
			switch (m_nSelect)
			{
			case CTitle::Title_Game:
				// ゲームシーン
				CManager::GetFade()->SetFade(CManager::MODE_GAME, 5);

				if (CManager::GetKeyboard()->GetPress(DIK_LSHIFT))
				{
					CData::SetNextStage(CData::Stage_Build);
				}

				break;

			case CTitle::Title_Build:
				// ビルダーシーン
				CManager::GetFade()->SetFade(CManager::MODE_BUILD, 5);

				break;

			case CTitle::Title_Quit:
				// ゲーム終了
				PostQuitMessage(0);
				break;

			default:
				break;
			}
		}
	}
}

//=============================================================================
// ポリゴンの描画処理
//=============================================================================
void CModeSelect::Draw()
{
	CScene2D::Draw();
}

CModeSelect *CModeSelect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, LPDIRECT3DTEXTURE9 tex)
{
	CModeSelect* pModeSelect = new CModeSelect;

	if (pModeSelect != NULL)
	{
		pModeSelect->Init(pos, move, size, tex);
	}

	return pModeSelect;
}
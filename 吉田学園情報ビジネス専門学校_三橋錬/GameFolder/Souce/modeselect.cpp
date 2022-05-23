//=============================================================================
//
// �J�[�\�� [modeselect.cpp]
// Author : �O���B
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
// �R���X�g���N�^
//=============================================================================
CModeSelect::CModeSelect(CScene::PRIORITY nPriority) : CScene2D(nPriority)
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CModeSelect::~CModeSelect()
{

}

//=============================================================================
// �|���S���̏���������
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
// �|���S���̏I������
//=============================================================================
void CModeSelect::Uninit()
{
	CScene2D::Uninit();
}

//=============================================================================
// �|���S���̍X�V����
//=============================================================================
void CModeSelect::Update()
{
	if (CFade::GetFade() == CFade::FADE_NONE)
	{
		// �J�[�\�������
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

		// �J�[�\��������
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
			// �I�u�W�F�N�g�T�C�Y�������l��
			CTitle::GetScreenBg(objCnt)->SetSize(D3DXVECTOR3(300.0f, 75.0f, 0.0f));
		}
		// �I�΂ꂽ�I�u�W�F�N�g��������Ƒ傫��
		CTitle::GetScreenBg(m_nSelect)->SetSize(D3DXVECTOR3(350.0f, 100.0f, 0.0f));

		D3DXVECTOR3 pos = CTitle::GetScreenBg(m_nSelect)->GetPos();
		pos.x = GetPos().x;
		SetPositionCenter(pos, GetSize());

		// ENTER�L�[�Ŋm��
		if (CManager::GetKeyboard()->GetTrigger(DIK_SPACE) ||
			CManager::GetKeyboard()->GetTrigger(DIK_RETURN))
		{
			CManager::GetSound()->Play(CSound::SOUND_LABEL_SE_PRESS);
			CManager::GetSound()->ControllVoice(CSound::SOUND_LABEL_SE_PRESS, 0.5f);

			// �V�[���J��
			switch (m_nSelect)
			{
			case CTitle::Title_Game:
				// �Q�[���V�[��
				CManager::GetFade()->SetFade(CManager::MODE_GAME, 5);

				if (CManager::GetKeyboard()->GetPress(DIK_LSHIFT))
				{
					CData::SetNextStage(CData::Stage_Build);
				}

				break;

			case CTitle::Title_Build:
				// �r���_�[�V�[��
				CManager::GetFade()->SetFade(CManager::MODE_BUILD, 5);

				break;

			case CTitle::Title_Quit:
				// �Q�[���I��
				PostQuitMessage(0);
				break;

			default:
				break;
			}
		}
	}
}

//=============================================================================
// �|���S���̕`�揈��
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
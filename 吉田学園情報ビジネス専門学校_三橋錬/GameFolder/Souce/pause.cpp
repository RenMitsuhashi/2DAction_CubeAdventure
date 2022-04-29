//=============================================================================
//
// �|�[�Y [pause.cpp]
// Author : �O���B
//
//=============================================================================
#include "main.h"
#include "pause.h"
#include "manager.h"
#include "renderer.h"
#include "sound.h"
#include "data.h"
#include "fade.h"
#include "keyboard.h"
#include "Stageload.h"
#include "uibg.h"
#include "player.h"
#include "texture.h"

int CPause::m_nSelect = Select_Resume_Save;
bool CPause::m_bNowSave = false;
CUIBg *CPause::m_pUIBg[] = {};

CPause::CPause(CScene::PRIORITY nPriority) : CScene2D(nPriority)
{

}

CPause::~CPause()
{

}

HRESULT CPause::Init(LPDIRECT3DTEXTURE9 tex)
{
	SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f));
	SetSize(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));

	CScene2D::Init(tex);

	m_nSelect = Select_Resume_Save;
	m_bNowSave = false;

	for (int nCnt = 0; nCnt < Pause_Max; nCnt++)
	{
		m_pUIBg[nCnt] = NULL;
	}

	return S_OK;
}

void CPause::Uninit(void)
{
	CScene2D::Uninit();
}

void CPause::Update(void)
{
	if ((!CData::GetPause() && CData::GetNowGame() && CData::GetNowScene() == CManager::MODE_GAME) ||
		(!CData::GetPause() && CData::GetNowScene() == CManager::MODE_BUILD))
	{
		// �I����UI�̊�{�ƂȂ�T�C�Y���w��
		D3DXVECTOR3 size = D3DXVECTOR3(SCREEN_WIDTH / 4.0f, SCREEN_HEIGHT / 8.0f, 0.0f);

		if (!m_pUIBg[Pause_Bg])
		{
			D3DCOLORVALUE col;
			col.r = 0.0f;
			col.g = 0.0f;
			col.b = 0.0f;
			col.a = 192.0f;

			m_pUIBg[Pause_Bg] = CUIBg::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), CTexture::GetTexture(CTexture::Tex_Fade));
			m_pUIBg[Pause_Bg]->SetColor(col);
		}

		// �ĊJ(�r���_�[�V�[���̏ꍇ�̓Z�[�u��)��UI��ݒ�
		if (!m_pUIBg[Pause_Resume_Save])
		{
			LPDIRECT3DTEXTURE9 texture = CTexture::GetTexture(CTexture::Tex_Pause_Resume);

			if (CData::GetNowScene() == CManager::MODE_BUILD)
			{
				texture = CTexture::GetTexture(CTexture::Tex_Pause_Save);
			}

			m_pUIBg[Pause_Resume_Save] = CUIBg::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - (SCREEN_WIDTH / 5.0f), SCREEN_HEIGHT / 2.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), size, texture);
		}

		// �^�C�g���֖߂邽�߂�UI��ݒ�
		if (!m_pUIBg[Pause_Title])
		{
			m_pUIBg[Pause_Title] = CUIBg::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f + (SCREEN_WIDTH / 5.0f), SCREEN_HEIGHT / 2.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), size, CTexture::GetTexture(CTexture::Tex_Pause_Title));
		}

		if (CFade::GetFade() == CFade::FADE_NONE)
		{
			// ��������
			if (CManager::GetKeyboard()->GetTrigger(DIK_A) ||
				CManager::GetKeyboard()->GetTrigger(DIK_LEFT))
			{
				CManager::GetSound()->Play(CSound::SOUND_LABEL_SE_CURSOR);
				CManager::GetSound()->ControllVoice(CSound::SOUND_LABEL_SE_CURSOR, 0.4f);

				m_nSelect--;

				if (m_nSelect < Select_Resume_Save)
				{
					m_nSelect = Select_Max - 1;
				}
			}

			// �E������
			if (CManager::GetKeyboard()->GetTrigger(DIK_D) ||
				CManager::GetKeyboard()->GetTrigger(DIK_RIGHT))
			{
				CManager::GetSound()->Play(CSound::SOUND_LABEL_SE_CURSOR);
				CManager::GetSound()->ControllVoice(CSound::SOUND_LABEL_SE_CURSOR, 0.4f);

				m_nSelect++;

				if (m_nSelect > Select_Max - 1)
				{
					m_nSelect = Select_Resume_Save;
				}
			}

			// �G���^�[�L�[
			if (CManager::GetKeyboard()->GetTrigger(DIK_RETURN))
			{
				CManager::GetSound()->Play(CSound::SOUND_LABEL_SE_ENTER);
				CManager::GetSound()->ControllVoice(CSound::SOUND_LABEL_SE_ENTER, 0.4f);

				switch (m_nSelect)
				{
				case Select_Resume_Save:

					// �r���h�V�[���Ȃ�Z�[�u���Ă���
					if (CData::GetNowScene() == CManager::MODE_BUILD &&
						!CData::GetNowGame())
					{
						CStageLoad::SaveFile();
					}

					// �|�[�Y������
					CData::SetPause(true);

					for (int nCnt = 0; nCnt < Pause_Max; nCnt++)
					{
						if (m_pUIBg[nCnt])
						{
							m_pUIBg[nCnt]->SetDeath(true);
							m_pUIBg[nCnt] = NULL;
						}
					}

					break;

				case Select_Title:
					// �^�C�g���֖߂�
					CManager::GetFade()->SetFade(CManager::MODE_TITLE, 5);

					break;

				default:

					break;
				}
			}

			// ESC�L�[������
			if (CManager::GetKeyboard()->GetTrigger(DIK_ESCAPE))
			{
				// �|�[�Y������
				CData::SetPause(true);

				for (int nCnt = 0; nCnt < Pause_Max; nCnt++)
				{
					if (m_pUIBg[nCnt])
					{
						m_pUIBg[nCnt]->SetDeath(true);
						m_pUIBg[nCnt] = NULL;
					}
				}
			}
		}

		// �I�𒆂�UI�������Ă���Ȃ�
		if (m_pUIBg[m_nSelect] && !m_pUIBg[m_nSelect]->GetDeath())
		{
			// UI����{�T�C�Y�ɖ߂��Ă���
			m_pUIBg[Pause_Resume_Save]->SetSize(size);
			m_pUIBg[Pause_Title]->SetSize(size);

			// �I�𒆂�UI��������Ƒ傫��
			m_pUIBg[m_nSelect]->SetSize(size * 1.2f);

			// �J�[�\����UI�ɍ��킹��
			SetPos(m_pUIBg[m_nSelect]->GetPos());
			SetSize(m_pUIBg[m_nSelect]->GetSize());
		}
	}

	// �|�[�Y���łȂ��Ȃ�
	else
	{
		if ((CData::GetNowScene() == CManager::MODE_BUILD && !CData::GetNowGame()) ||
			(CData::GetNowScene() == CManager::MODE_GAME && CData::GetNowGame()))
		{
			if (CStageLoad::GetPlayer())
			{
				if (!CStageLoad::GetPlayer()->GetDeath())
				{
					if (CManager::GetKeyboard()->GetTrigger(DIK_ESCAPE))
					{
						CManager::GetSound()->Play(CSound::SOUND_LABEL_SE_ENTER);
						CManager::GetSound()->ControllVoice(CSound::SOUND_LABEL_SE_ENTER, 0.4f);

						CData::SetPause(false);
					}
				}
			}
		}

		m_nSelect = Select_Resume_Save;
		m_bNowSave = false;
	}

	SetPositionCenter(GetPos(), GetSize());
}

void CPause::Draw(void)
{
	if (!CData::GetPause())
	{
		CScene2D::Draw();
	}
}

CPause *CPause::Create(LPDIRECT3DTEXTURE9 tex)
{
	CPause* pPause = new CPause;

	if (pPause != NULL)
	{
		pPause->Init(tex);
	}
	return pPause;
}
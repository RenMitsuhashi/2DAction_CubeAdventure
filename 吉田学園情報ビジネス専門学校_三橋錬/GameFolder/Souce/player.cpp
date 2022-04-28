//=============================================================================
//
// �v���C���[ [player.cpp]
// Author : �O���B
//
//=============================================================================
#include "player.h"
#include "manager.h"
#include "renderer.h"

#include "input.h"
#include "keyboard.h"
#include "gamepad.h"
#include "mouse.h"

#include "Stageload.h"
#include "sound.h"
#include "data.h"
#include "fade.h"
#include "effect.h"
#include "texture.h"
#include "uibg.h"
#include "deathcount.h"
#include "time.h"

const float CPlayer::m_fMoveGrav = 0.3f;
const float CPlayer::m_fMaxGrav = 1.6f;
const float CPlayer::m_fMinGrav = 0.4f;

CUIBg *CPlayer::m_pUIBg[] = {};
CDeathCount *CPlayer::m_pDeathCount = NULL;
CTime *CPlayer::m_pTime = NULL;

CEffect *CPlayer::m_pDeathEffect[] = {};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPlayer::CPlayer(CScene::PRIORITY nPriority) : CScene2D(nPriority)
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CPlayer::~CPlayer()
{

}

//=============================================================================
// �|���S���̏���������
//=============================================================================
HRESULT CPlayer::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, LPDIRECT3DTEXTURE9 tex)
{
	SetPos(pos);
	SetMove(move);
	SetSize(size);
	SetDeath(false);
	
	m_pDeathCount = NULL;
	m_pTime = NULL;

	CScene2D::Init(tex);

	for (int nCnt = 0; nCnt < Texture_Max; nCnt++)
	{
		m_pUIBg[nCnt] = NULL;
	}

	for (int nCnt = 0; nCnt < m_nDeathEffectCnt; nCnt++)
	{
		m_pDeathEffect[nCnt] = NULL;
	}

	return S_OK;
}

//=============================================================================
// �|���S���̏I������
//=============================================================================
void CPlayer::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// �|���S���̍X�V����
//=============================================================================
void CPlayer::Update(void)
{
	m_nType = Player_Normal;

	D3DCOLORVALUE col;
	col.r = 255.0f;
	col.g = 255.0f;
	col.b = 255.0f;
	col.a = 128.0f;

	// �S�[�����o
	if (m_bGoal)
	{
		Goal();
	}

	// �Q�[���v���C��
	if (CData::GetPause() &&
		CData::GetNowGame())
	{
		m_nFrame++;

		if (m_nFrame >= 60)
		{
			m_nFrame = 0;
			CData::AddTime();
		}

		// ���S���o
		if (m_bDeath)
		{
			Death();
		}

		else
		{
			m_bJump = true;
			col.a = 255.0f;

			//=============================================================================
			// ���������ꂽ
			//=============================================================================
			if (CManager::GetKeyboard()->GetPress(DIK_D))
			{
				m_nType = Player_Right;
				SetMoveX(GetMove().x + m_Speed.x * 2);
			}

			//=============================================================================
			// ���������ꂽ
			//=============================================================================
			else if (CManager::GetKeyboard()->GetPress(DIK_A))
			{
				m_nType = Player_Left;
				SetMoveX(GetMove().x - m_Speed.x * 2);
			}

			//=============================================================================
			// �ړ��ʂɐ�����������
			//=============================================================================
			if (GetMove().x > m_SpeedMax.x)		SetMoveX(m_SpeedMax.x);
			if (GetMove().x < -m_SpeedMax.x)	SetMoveX(-m_SpeedMax.x);

			if (GetMove().y > m_SpeedMax.y)		SetMoveY(m_SpeedMax.y);
			if (GetMove().z > m_SpeedMax.z)		SetMoveZ(m_SpeedMax.z);

			//=============================================================================
			// ��ʒ[�̐���
			//=============================================================================
			if (GetPos().x - GetSize().x / 2.0f < 0.0f)				// ��ʍ�
			{
				SetPosX(0.0f + GetSize().x / 2.0f);
			}

			if (GetPos().y + GetSize().y / 2.0f > SCREEN_HEIGHT &&
				CManager::GetData()->GetGravity() > 0.0f)			// ��ʉ�
			{
				SetPosY(SCREEN_HEIGHT - GetSize().y / 2.0f);
				SetDeath(true);

				return;
			}

			if (GetPos().y + GetSize().y / 2.0f < 0.0f &&
				CManager::GetData()->GetGravity() < 0.0f)			// ��ʏ�
			{
				SetPosY(0.0f + GetSize().y / 2.0f);
				SetDeath(true);

				return;
			}

			SetMoveY(GetMove().y + m_Speed.y * CData::GetGravity() / 0.6f);

			// �ύX����pos�𔽉f������
			SetPositionCenter(GetPos(), GetSize());

			// �����蔻��
			ColisionBlock();

			//=============================================================================
			// �S�[��
			//=============================================================================
			for (int nCnt = DIRECTION_NONE; nCnt < DIRECTION_MAX; nCnt++)
			{
				if (GetColision(nCnt) != NULL)
				{
					if (GetColision(nCnt)->GetobjType() == CStageLoad::OBJ_Goal)
					{
						// �Q�[���V�[���Ȃ烊�U���g�֑J��
						if (CData::GetNowScene() == CManager::MODE_GAME)
						{
							m_bGoal = true;
						}

						// �r���_�[�V�[���Ȃ�e�X�g�I��
						else
						{
							Reset();
						}
					}
				}
			}

			//=============================================================================
			// ���݃W�����v�\��(���ɑ������Ă��邩)
			//=============================================================================
			// �d�͂�������̎�
			if (GetColision(DIRECTION_UP) != NULL)
			{
				if (GetColision(DIRECTION_UP)->GetPriority() == PRIORITY_BLOCK)
				{
					if (CManager::GetData()->GetGravity() < 0.0f)
					{
						m_bJump = false;

						if (GetColision(DIRECTION_UP)->GetTargetPos() == D3DXVECTOR3(0.0f, 0.0f, 0.0f))
						{
							m_pLastStepblock = GetColision(DIRECTION_UP);
							m_fLastStepGravity = CData::GetGravity();
						}
					}
				}
			}

			// �d�͂��������̎�
			if (GetColision(DIRECTION_DOWN) != NULL)
			{
				if (GetColision(DIRECTION_DOWN)->GetPriority() == PRIORITY_BLOCK)
				{
					if (CManager::GetData()->GetGravity() > 0.0f)
					{
						m_bJump = false;

						if (GetColision(DIRECTION_DOWN)->GetTargetPos() == D3DXVECTOR3(0.0f, 0.0f, 0.0f))
						{
							m_pLastStepblock = GetColision(DIRECTION_DOWN);
							m_fLastStepGravity = CData::GetGravity();
						}
					}
				}
			}

			//=============================================================================
			// ���C
			//=============================================================================

			// ������
			if (GetMove().x < 0.0f)
			{
				m_nType = Player_Left;

				// �d�͂��������̎�
				if (GetColision(DIRECTION_DOWN) != NULL)
				{
					// �������Ă���u���b�N�������Ă�����
					if (GetColision(DIRECTION_DOWN)->GetPriority() == PRIORITY_BLOCK &&
						GetColision(DIRECTION_DOWN)->GetMove().x != 0.0f &&
						CManager::GetData()->GetGravity() > 0.0f)
					{
						SetMoveX(GetColision(DIRECTION_DOWN)->GetMove().x);
					}

					else
					{
						SetMoveX(GetMove().x + m_Speed.x);
					}
				}

				// �d�͂�������̎�
				else if (GetColision(DIRECTION_UP) != NULL)
				{
					// �������Ă���u���b�N�������Ă�����
					if (GetColision(DIRECTION_UP)->GetPriority() == PRIORITY_BLOCK &&
						GetColision(DIRECTION_UP)->GetMove().x != 0.0f &&
						CManager::GetData()->GetGravity() < 0.0f)
					{
						SetMoveX(GetColision(DIRECTION_UP)->GetMove().x);
					}

					else
					{
						SetMoveX(GetMove().x + m_Speed.x);
					}
				}

				// ���ɂ��������Ă��Ȃ����
				else
				{
					SetMoveX(GetMove().x + m_Speed.x);
				}

				// ��~
				if (GetMove().x > 0.0f)	SetMoveX(0.0f);
			}

			// �E����
			else if (GetMove().x > 0.0f)
			{
				m_nType = Player_Right;

				// �d�͂��������̎�
				if (GetColision(DIRECTION_DOWN) != NULL)
				{
					// �������Ă���u���b�N�������Ă�����
					if (GetColision(DIRECTION_DOWN)->GetPriority() == PRIORITY_BLOCK &&
						GetColision(DIRECTION_DOWN)->GetMove().x != 0.0f &&
						CManager::GetData()->GetGravity() > 0.0f)
					{
						SetMoveX(GetColision(DIRECTION_DOWN)->GetMove().x);
					}

					else
					{
						SetMoveX(GetMove().x - m_Speed.x);
					}
				}

				// �d�͂�������̎�
				else if (GetColision(DIRECTION_UP) != NULL)
				{
					// �������Ă���u���b�N�������Ă�����
					if (GetColision(DIRECTION_UP)->GetPriority() == PRIORITY_BLOCK &&
						GetColision(DIRECTION_UP)->GetMove().x != 0.0f &&
						CManager::GetData()->GetGravity() < 0.0f)
					{
						SetMoveX(GetColision(DIRECTION_UP)->GetMove().x);
					}

					else
					{
						SetMoveX(GetMove().x - m_Speed.x);
					}
				}

				// ���ɂ��������Ă��Ȃ����
				else
				{
					SetMoveX(GetMove().x - m_Speed.x);
				}

				// ��~
				if (GetMove().x < 0.0f)	SetMoveX(0.0f);
			}

			//=============================================================================
			// ��
			//=============================================================================
			if (GetColision(DIRECTION_UP) != NULL && GetColision(DIRECTION_DOWN) != NULL)
			{
				// �㉺�̃u���b�N�ɋ��܂ꂽ�玀
				if (GetColision(DIRECTION_UP)->GetPriority() == PRIORITY_BLOCK && GetColision(DIRECTION_DOWN)->GetPriority() == PRIORITY_BLOCK)
				{
					SetDeath(true);
				}
			}

			if (GetColision(DIRECTION_LEFT) != NULL && GetColision(DIRECTION_RIGHT) != NULL)
			{
				// ���E�̃u���b�N�ɋ��܂ꂽ�玀
				if (GetColision(DIRECTION_LEFT)->GetPriority() == PRIORITY_BLOCK && GetColision(DIRECTION_RIGHT)->GetPriority() == PRIORITY_BLOCK)
				{
					SetDeath(true);
				}
			}

			//=============================================================================
			// ��ʃX�N���[��
			//=============================================================================
			if (GetPos().x >= SCREEN_WIDTH / 4.0f)
			{
				CData::MoveQuantity(GetPos().x - GetPosold().x);
			}

			else
			{
				CData::ZeroMoveQuantity();
			}

			//=============================================================================
			// SPACE�������ꂽ(�W�����v)
			//=============================================================================
			if (CManager::GetKeyboard()->GetPress(DIK_SPACE) && !m_bJump)
			{
				// �d�͂��������Ȃ�
				if (CData::GetGravity() > 0)
				{
					SetMoveY(-JUMP_HEIGHT);
				}

				// �d�͂�������Ȃ�
				else
					SetMoveY(JUMP_HEIGHT);

				m_bJump = true;
				CManager::GetSound()->Play(CSound::SOUND_LABEL_SE_JUMP);
				CManager::GetSound()->ControllVoice(CSound::SOUND_LABEL_SE_JUMP, 0.1f);
				CManager::GetSound()->ControllPitch(CSound::SOUND_LABEL_SE_JUMP, 5.0f, 10.0f);
			}

			//=============================================================================
			// �d�͕ύX(WS�L�[)
			//=============================================================================
			// �d�͂��������Ȃ�

			bool bKey = false;

			if (CData::GetGravity() > 0)
			{
				// W�L�[�ŏd�͂��y������
				if (CManager::GetKeyboard()->GetTrigger(DIK_W))
				{
					bKey = true;
					CData::MoveGravity(-m_fMoveGrav);

					if (CData::GetGravity() < m_fMinGrav)	CData::SetGravity(m_fMinGrav);
				}

				// S�L�[�ŏd�͂��d������
				if (CManager::GetKeyboard()->GetTrigger(DIK_S))
				{
					bKey = true;
					CData::MoveGravity(m_fMoveGrav);

					if (CData::GetGravity() > m_fMaxGrav)	CData::SetGravity(m_fMaxGrav);
				}
			}

			// �d�͂�������Ȃ�
			else
			{
				// S�L�[�ŏd�͂��d������
				if (CManager::GetKeyboard()->GetTrigger(DIK_S))
				{
					bKey = true;
					CData::MoveGravity(m_fMoveGrav);

					if (CData::GetGravity() > -m_fMinGrav)	CData::SetGravity(-m_fMinGrav);
				}

				// W�L�[�ŏd�͂��y������
				if (CManager::GetKeyboard()->GetTrigger(DIK_W))
				{
					bKey = true;
					CData::MoveGravity(-m_fMoveGrav);

					if (CData::GetGravity() < -m_fMaxGrav)	CData::SetGravity(-m_fMaxGrav);
				}
			}

			if (bKey)
			{
				float grav = (fabs(CData::GetGravity()) - GetMinGrav()) * 4.0f;

				CManager::GetSound()->Play(CSound::SOUND_LABEL_SE_GRAVUPDOWN);
				CManager::GetSound()->ControllVoice(CSound::SOUND_LABEL_SE_GRAVUPDOWN, 0.7f);
				CManager::GetSound()->ControllPitch(CSound::SOUND_LABEL_SE_GRAVUPDOWN, 10.0f, 10.0f + grav);
			}
		}
	}

	// �Q�[���ҏW��
	else
	{
		SetPositionCenter(GetPos(), GetSize());
		
		CData::SetGravity(1.0f);
	}

	ScrollTexture(D3DXVECTOR3(m_fTexMove * m_nType, 0.0f, 0.0f));
	SetColor(col);
}

//=============================================================================
// �|���S���̕`�揈��
//=============================================================================
void CPlayer::Draw(void)
{
	if (!m_bDeath)
	{
		CScene2D::Draw();
	}
}

CPlayer *CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, LPDIRECT3DTEXTURE9 tex)
{
	CPlayer* pPlayer = new CPlayer;

	if (pPlayer != NULL)
	{
		pPlayer->Init(pos, move, size, tex);
	}
	return pPlayer;
}

void CPlayer::Reset()
{
	if (CData::GetNowScene() == CManager::MODE_GAME)
	{
		CData::MoveQuantity(m_pLastStepblock->GetPos().x - GetPosold().x);
	}

	else
	{
		CData::ZeroMoveQuantity();
	}

	ReturnTostartPosAll();
	SetDeath(false);
	CData::SetGravity(m_fLastStepGravity);

	if (CData::GetNowScene() == CManager::MODE_GAME)
	{
		// �d�͂��������̂Ƃ�
		if (CData::GetGravity() > 0.0f)
		{
			SetPosX(m_pLastStepblock->GetPos().x);
			SetPosY(m_pLastStepblock->GetPos().y - m_pLastStepblock->GetSize().y / 2 - GetSize().y / 2.0f);
		}

		// �d�͂�������̂Ƃ�
		if (CData::GetGravity() < 0.0f)
		{
			SetPosX(m_pLastStepblock->GetPos().x);
			SetPosY(m_pLastStepblock->GetPos().y + m_pLastStepblock->GetSize().y / 2 + GetSize().y / 2.0f);
		}
	}

	else
	{
		CData::ChangeNowGame();
	}
}

void CPlayer::Death()
{
	SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	for (int nCnt = 0; nCnt < m_nDeathEffectCnt; nCnt++)
	{
		if (m_pDeathEffect[nCnt] == NULL)
		{
			DeathEffectCreate(nCnt);
		}
	}

	m_nDeathTime++;

	if (m_nDeathTime > m_nDeathTimeMax)
	{
		ReverseDeath();
		m_nDeathTime = 0;

		Reset();

		if (CData::GetNowScene() == CManager::MODE_GAME)
		{
			CData::AddDeathCount();
		}

		for (int nCnt = 0; nCnt < m_nDeathEffectCnt; nCnt++)
		{
			m_pDeathEffect[nCnt] = NULL;
		}
	}
}

void CPlayer::DeathEffectCreate(int num)
{
	CManager::GetSound()->Play(CSound::SOUND_LABEL_SE_DEATH);
	CManager::GetSound()->ControllVoice(CSound::SOUND_LABEL_SE_DEATH, 0.5f);
	CManager::GetSound()->ControllPitch(CSound::SOUND_LABEL_BGM_TITLE, 10.0f, 5.0f);

	D3DCOLORVALUE coleffect;
	coleffect.r = 255.0f;
	coleffect.g = 255.0f;
	coleffect.b = 255.0f;
	coleffect.a = 255.0f;

	D3DCOLORVALUE mincoleffect;
	mincoleffect.r = 0.0f;
	mincoleffect.g = 0.0f;
	mincoleffect.b = 0.0f;
	mincoleffect.a = 2.0f;

	D3DXVECTOR3 minsize = D3DXVECTOR3(0.05f, 0.05f, 0.0f);

	D3DXVECTOR3 pos = GetPos();
	pos.x -= CData::GetMoveQuantity();

	D3DXVECTOR3 move;
	float speed = 5.0f;
	float pi = (float)M_PI;

	float fMoveDirection = 0.0f;
	fMoveDirection += 0.25f * (float)num;

	if (fMoveDirection > 1.0f)
	{
		fMoveDirection -= 1.0f;
	}

	if (num <= m_nDeathEffectCnt / 2)
	{
		pi *= -1;
	}

	if (fMoveDirection == 0.0f)
	{
		move.x = speed;
		move.y = speed;
	}

	if (fMoveDirection == 1.0f)
	{
		move.x = sinf(pi * Sign(pi) * 0.0f) * speed;
		move.y = cosf(pi * Sign(pi) * fMoveDirection) * speed;
	}

	else
	{
		move.x = sinf(pi * fMoveDirection) * speed;
		move.y = cosf(pi * fMoveDirection) * speed;
	}

	move.z = 0.0f;

	m_pDeathEffect[num] = CEffect::Create(pos, move, coleffect, mincoleffect, GetSize(), minsize, m_nDeathTimeMax, CTexture::GetTexture(CTexture::Tex_Effect));
}

void CPlayer::Goal()
{
	switch (m_nGoalCount)
	{
	case Goal_Display:
		CManager::GetSound()->Play(CSound::SOUND_LABEL_SE_GOALSHAKE);
		CManager::GetSound()->ControllVoice(CSound::SOUND_LABEL_SE_GOALSHAKE, 0.4f);

		CData::ChangeNowGame();
		m_nGoalCount++;
		m_pUIBg[StageClear] = CUIBg::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 200.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), CTexture::GetTexture(CTexture::Tex_GoalLogo));

		break;

	case Goal_Shake:
		m_nGoalTime++;

		if (m_nGoalTime < 16)
		{
			RandomShake(D3DXVECTOR3(5.5f, 5.5f, 0.0f));
		}

		if (m_nGoalTime > 96)
		{
			m_nGoalTime = 0;
			m_nGoalCount++;
		}

		break;

	case Goal_TimeDisplay:
		m_nGoalTime++;

		if (m_pUIBg[ClearTimeLogo] == NULL)
		{
			CManager::GetSound()->Play(CSound::SOUND_LABEL_SE_GOALLOGO);
			CManager::GetSound()->ControllVoice(CSound::SOUND_LABEL_SE_GOALLOGO, 0.5f);

			m_pUIBg[ClearTimeLogo] = CUIBg::Create(D3DXVECTOR3(500.0f, SCREEN_HEIGHT / 2 + 100.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(300.0f, 75.0f, 0.0f), CTexture::GetTexture(CTexture::Tex_Time));
		}

		if (m_nGoalTime > 32 && m_pTime == NULL)
		{
			CManager::GetSound()->Play(CSound::SOUND_LABEL_SE_GOALLOGO);
			CManager::GetSound()->ControllVoice(CSound::SOUND_LABEL_SE_GOALLOGO, 0.5f);

			m_pTime = CTime::Create(D3DXVECTOR3(1000.0f, SCREEN_HEIGHT / 2 + 100.0f, 0.0f), D3DXVECTOR3(35.0f, 75.0f, 0.0f));
		}

		if (m_nGoalTime > 96)
		{
			m_nGoalTime = 0;
			m_nGoalCount++;
		}

		break;

	case Goal_DeathCountDisplay:
		m_nGoalTime++;

		if (m_pUIBg[DeathCountLogo] == NULL)
		{
			CManager::GetSound()->Play(CSound::SOUND_LABEL_SE_GOALLOGO);
			CManager::GetSound()->ControllVoice(CSound::SOUND_LABEL_SE_GOALLOGO, 0.5f);

			m_pUIBg[DeathCountLogo] = CUIBg::Create(D3DXVECTOR3(500.0f, SCREEN_HEIGHT / 2 + 200.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(300.0f, 75.0f, 0.0f), CTexture::GetTexture(CTexture::Tex_Death));
		}

		if (m_nGoalTime > 32 && m_pDeathCount == NULL)
		{
			CManager::GetSound()->Play(CSound::SOUND_LABEL_SE_GOALLOGO);
			CManager::GetSound()->ControllVoice(CSound::SOUND_LABEL_SE_GOALLOGO, 0.5f);

			m_pDeathCount = CDeathCount::Create(D3DXVECTOR3(1000.0f, SCREEN_HEIGHT / 2 + 200.0f, 0.0f), D3DXVECTOR3(35.0f, 75.0f, 0.0f));
		}

		if (m_nGoalTime > 128)
		{
			m_nGoalTime = 0;
			m_nGoalCount++;
		}

		break;

	case Goal_PressEnterDisplay:
		if (m_pUIBg[PressEnterLogo] == NULL)
		{
			CManager::GetSound()->Play(CSound::SOUND_LABEL_SE_GOALSHAKE);
			CManager::GetSound()->ControllVoice(CSound::SOUND_LABEL_SE_GOALSHAKE, 0.4f);

			m_pUIBg[PressEnterLogo] = CUIBg::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 350.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(700.0f, 100.0f, 0.0f), CTexture::GetTexture(CTexture::Tex_PressEnter));
		}

		if (CManager::GetFade()->GetFade() == CFade::FADE_NONE)
		{
			if (CManager::GetKeyboard()->GetTrigger(DIK_RETURN))
			{
				CManager::GetSound()->Play(CSound::SOUND_LABEL_SE_ENTER);
				CManager::GetSound()->ControllVoice(CSound::SOUND_LABEL_SE_ENTER, 0.3f);

				if (CData::GetNextStage() == CData::Stage_Max - 1)
				{
					CManager::GetFade()->SetFade(CManager::MODE_TITLE, 2);
				}

				CData::AddNextStage();
				CManager::GetFade()->SetFade(CManager::MODE_GAME, 10);
			}
		}

		break;

	default:

		break;
	}
}
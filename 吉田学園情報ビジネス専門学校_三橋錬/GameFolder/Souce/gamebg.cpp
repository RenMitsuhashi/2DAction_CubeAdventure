//=============================================================================
//
// �Q�[���̔w�i [gamebg.h]
// Author : �O���B
//
//=============================================================================
#include "gamebg.h"
#include "manager.h"
#include "renderer.h"
#include "stageload.h"
#include "player.h"
#include "effect.h"
#include "data.h"
#include "texture.h"
#include "objectbg.h"

CObjectBg *CGameBg::m_pObjectBg[] = {};
CEffect *CGameBg::m_pEffect[] = {};
float CGameBg::m_fTargetPosY[] = {};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CGameBg::CGameBg(CScene::PRIORITY nPriority) : CScene2D(nPriority)
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CGameBg::~CGameBg()
{

}

//=============================================================================
// �|���S���̏���������
//=============================================================================
HRESULT CGameBg::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, LPDIRECT3DTEXTURE9 tex)
{
	SetPos(pos);
	SetMove(move);
	SetSize(size);
	SetDeath(false);

	CScene2D::Init(tex);

	// �`���[�g���A���p�|���S���̏�����
	for (int nCnt = 0; nCnt < UI_MAX; nCnt++)
	{
		m_pObjectBg[nCnt] = NULL;
	}

	// �G�t�F�N�g�̏�����
	for (int nCnt = 0; nCnt < EFFECT_MAX; nCnt++)
	{
		m_pEffect[nCnt] = NULL;
	}

	// �G�t�F�N�g���~�点��^�C�~���O
	m_nTime = 0;

	D3DCOLORVALUE col;
	col.r = 255.0f;
	col.g = 255.0f;
	col.b = 255.0f;
	col.a = 0.0f;

	SetColor(col);

	return S_OK;
}

//=============================================================================
// �|���S���̏I������
//=============================================================================
void CGameBg::Uninit()
{
	CScene2D::Uninit();
}

//=============================================================================
// �|���S���̍X�V����
//=============================================================================
void CGameBg::Update()
{
	if (CData::GetPause() &&
		CData::GetNowGame())
	{
		m_nTime++;
		float grav = CData::GetGravity();

		// �G�t�F�N�g�̈ړ����x���d�͂ɉ����ĕς���
		float m_EffectSpeed = m_fEffectBaseSpeed * grav;

		// �G�t�F�N�g�̃X�|�[���ʒuY(0)
		float effectspawnY = 0.0f;

		// �G�t�F�N�g�̃X�|�[���ʒuX�������_���ɂ���
		std::random_device rnd;
		std::mt19937 mt(rnd());

		// ��
		D3DCOLORVALUE col;
		col.r = 0.0f;
		col.g = 0.0f;
		col.b = 255.0f;
		col.a = 255.0f;

		D3DCOLORVALUE mincol;
		mincol.r = 0.0f;
		mincol.g = 0.0f;
		mincol.b = 0.0f;
		mincol.a = 0.0f;

		float gravcol = fabs(grav) - CPlayer::GetMinGrav();

		float gravsplit = CPlayer::GetMaxGrav() - CPlayer::GetMinGrav() - 0.2f;
		float gravsplitnum = 0.4f;

		//=============================================================================
		// �F�̕ύX
		//=============================================================================
		if (gravcol < 1.05f)
		{
			// ���F�ɂ���
			col.g = 255.0f;
			gravsplit -= gravsplitnum;

			if (gravcol < 0.75f)
			{
				// �΂ɂ���
				col.b = 0.0f;
				gravsplit -= gravsplitnum;

				if (gravcol < 0.45f)
				{
					// ���F�ɂ���
					col.r = 255.0f;
					gravsplit -= gravsplitnum;

					if (gravcol < 0.15f)
					{
						// �Ԃɂ���
						col.g = 0.0f;
						gravsplit -= gravsplitnum;
					}
				}
			}
		}

		// �w�i�̐F
		D3DCOLORVALUE colbg = col;
		colbg.a = 24.0f;

		SetColor(colbg);

		std::uniform_real_distribution<> randsize(15, 25);
		float sizerand = randsize(mt);

		//=============================================================================
		// �G�t�F�N�g�쐬
		//=============================================================================
		if (m_nTime > (float)m_nEffectSpawnTime)
		{
			m_nTime = 0;

			for (int nCnt = 0; nCnt < EFFECT_MAX; nCnt++)
			{
				if (!m_pEffect[nCnt])
				{
					// �G�t�F�N�g�̃X�|�[���ʒuX�������_���Ɍ��߂�
					std::uniform_real_distribution<> randX(0.0f, SCREEN_WIDTH);

					// �d�͂�������Ȃ�X�|�[���ʒu��ς���
					if (CData::GetGravity() < 0.0f)
					{
						effectspawnY = SCREEN_HEIGHT;
					}

					// �X�|�[���ʒu
					D3DXVECTOR3 effectspawn = D3DXVECTOR3((float)randX(mt), effectspawnY, 0.0f);

					// �G�t�F�N�g�̈ړ��ʂ������_����
					std::uniform_real_distribution<> randmove(1.0f, 2.0f);
					D3DXVECTOR3 effectmove = D3DXVECTOR3(0.0f, m_EffectSpeed * (float)randmove(mt), 0.0f);

					// ����
					m_pEffect[nCnt] = CEffect::Create(effectspawn, effectmove, col, mincol, D3DXVECTOR3(sizerand, sizerand, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 9999, CTexture::GetTexture(CTexture::Tex_Effect));
					break;
				}

				else
				{
					// �G�t�F�N�g����ڂ��ʂ���������
					if (m_pEffect[nCnt]->GetDeath())
					{
						m_pEffect[nCnt] = NULL;
						continue;
					}
				}
			}
		}

		//=============================================================================
		// �`���[�g���A���p�|���S���쐬
		//=============================================================================
		float PlayerPosX = CStageLoad::GetPlayer()->GetPos().x;

		if (CData::GetNextStage() == CData::Stage_Tutorial)
		{
			// �ړ��`���[�g���A��
			if (!m_pObjectBg[UI_WASD])
			{
				m_fTargetPosY[UI_WASD] = 450.0f;
				m_pObjectBg[UI_WASD] = CObjectBg::Create(D3DXVECTOR3(275.0f, SCREEN_HEIGHT + 250.0f, 0.0f), D3DXVECTOR3(0.0f, -10.0f, 0.0f), D3DXVECTOR3(400.0f, 225.0f, 0.0f), CTexture::GetTexture(CTexture::Tex_Tutorialwasd));
			}

			// �W�����v
			if (!m_pObjectBg[UI_JUMP] && PlayerPosX >= 550.0f)
			{
				m_fTargetPosY[UI_JUMP] = 450.0f;
				m_pObjectBg[UI_JUMP] = CObjectBg::Create(D3DXVECTOR3(700.0f, SCREEN_HEIGHT + 250.0f, 0.0f), D3DXVECTOR3(0.0f, -10.0f, 0.0f), D3DXVECTOR3(400.0f, 225.0f, 0.0f), CTexture::GetTexture(CTexture::Tex_Tutorialjump));
			}

			// �d�͔��]
			if (!m_pObjectBg[UI_GRAVITY_REVERSE] && PlayerPosX >= 1250.0f)
			{
				m_fTargetPosY[UI_GRAVITY_REVERSE] = 250.0f;
				m_pObjectBg[UI_GRAVITY_REVERSE] = CObjectBg::Create(D3DXVECTOR3(1737.5f, SCREEN_HEIGHT + 250.0f, 0.0f), D3DXVECTOR3(0.0f, -10.0f, 0.0f), D3DXVECTOR3(400.0f, 225.0f, 0.0f), CTexture::GetTexture(CTexture::Tex_TutorialGravityReverse));
			}

			// �d�͑�������
			if (!m_pObjectBg[UI_GRAVITY_UP_DOWN] && PlayerPosX >= 2250.0f)
			{
				m_fTargetPosY[UI_GRAVITY_UP_DOWN] = 250.0f;
				m_pObjectBg[UI_GRAVITY_UP_DOWN] = CObjectBg::Create(D3DXVECTOR3(2750.0f, SCREEN_HEIGHT + 250.0f, 0.0f), D3DXVECTOR3(0.0f, -10.0f, 0.0f), D3DXVECTOR3(400.0f, 225.0f, 0.0f), CTexture::GetTexture(CTexture::Tex_TutorialGravityUpDown));
			}

			// �S�[��
			if (!m_pObjectBg[UI_GOAL] && PlayerPosX >= 3350.0f)
			{
				m_fTargetPosY[UI_GOAL] = 700.0f;
				m_pObjectBg[UI_GOAL] = CObjectBg::Create(D3DXVECTOR3(3550.0f, SCREEN_HEIGHT + 250.0f, 0.0f), D3DXVECTOR3(0.0f, -10.0f, 0.0f), D3DXVECTOR3(400.0f, 225.0f, 0.0f), CTexture::GetTexture(CTexture::Tex_TutorialGoal));
			}

			for (int nCnt = 0; nCnt < UI_MAX; nCnt++)
			{
				if (m_pObjectBg[nCnt])
				{
					// �w�肵���ʒu�܂Ń|���S������ɂ���グ��
					if (m_pObjectBg[nCnt]->GetPos().y < m_fTargetPosY[nCnt])
					{
						m_pObjectBg[nCnt]->SetPosY(m_fTargetPosY[nCnt]);
						m_pObjectBg[nCnt]->SetMoveY(0.0f);
					}
				}
			}
		}
	}

	SetPositionCenter(GetPos(), GetSize());
}

//=============================================================================
// �|���S���̕`�揈��
//=============================================================================
void CGameBg::Draw()
{
	if (CData::GetPause() &&
		CData::GetNowGame())
	{
		CScene2D::Draw();
	}
}

CGameBg *CGameBg::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, LPDIRECT3DTEXTURE9 tex)
{
	CGameBg* pBg = new CGameBg;

	if (pBg != NULL)
	{
		pBg->Init(pos, move, size, tex);
	}
	return pBg;
}
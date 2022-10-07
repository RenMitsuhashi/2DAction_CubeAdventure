//=============================================================================
//
// �J�[�\�� [cursor.cpp]
// Author : �O���B
//
//=============================================================================
#include "cursor.h"
#include "manager.h"
#include "renderer.h"

#include "input.h"
#include "keyboard.h"
#include "gamepad.h"
#include "mouse.h"
#include "stagebuild.h"
#include "player.h"

#include "sound.h"
#include "data.h"
#include "tentativeobj.h"
#include "texture.h"
#include "fade.h"
#include "uibg.h"
#include "pause.h"

#include <assert.h>

CTargetCursor *CCursor::m_pTargetCursor = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CCursor::CCursor(CScene::PRIORITY nPriority) : CScene2D(nPriority)
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CCursor::~CCursor()
{

}

//=============================================================================
// �|���S���̏���������
//=============================================================================
HRESULT CCursor::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, LPDIRECT3DTEXTURE9 tex)
{
	CScene2D::Init(tex);

	SetPos(pos + GetGrid() / 2);
	SetMove(move);
	SetSize(size);
	SetDeath(false);

	m_nType = OBJ_NormalBlock;
	m_move = 0.0f;
	TargetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_stoptime = 0;

	m_nColisionType = OBJ_NULL;
	m_Colisionmove = 0.0f;
	m_Colisionstoptime = 0;

	m_pTargetCursor = CTargetCursor::Create(move, size, tex);

	m_col.r = 255.0f;
	m_col.g = 255.0f;
	m_col.b = 255.0f;
	m_col.a = 255.0f;

	m_Colisioncol.r = 255.0f;
	m_Colisioncol.g = 255.0f;
	m_Colisioncol.b = 255.0f;
	m_Colisioncol.a = 255.0f;

	CData::ZeroMoveQuantity();

	return S_OK;
}

//=============================================================================
// �|���S���̏I������
//=============================================================================
void CCursor::Uninit()
{
	CScene2D::Uninit();
}

//=============================================================================
// �|���S���̍X�V����
//=============================================================================
void CCursor::Update()
{
	m_nColisionType = OBJ_NULL;		// ���ݓ������Ă���I�u�W�F�N�g�̎��
	m_Colisionmove = 0.0f;			// ���ݓ������Ă���I�u�W�F�N�g�̈ړ���
	m_Colisionstoptime = 0;			// ���ݓ������Ă���I�u�W�F�N�g�̈ړ��܂ł̎���

	int tex = CTexture::Tex_NormalBlock - 1;

	D3DCOLORVALUE col;
	col.r = 255.0f;
	col.g = 255.0f;
	col.b = 255.0f;
	col.a = 255.0f;

	if (!CData::GetNowGame() &&
		CData::GetPause())
	{
		// �J�[�\����pos�̓}�E�X�̍��W����������
		D3DXVECTOR3 mouse = CManager::GetRenderer()->GetMousePos();
		D3DXVECTOR3 pos = D3DXVECTOR3(floorf(mouse.x / GetSize().x) * GetSize().x, floorf(mouse.y / GetSize().y) * GetSize().y, 0.0f);

		SetPositionCenter(pos + GetGrid() / 2, GetSize());

		SetPos(pos + GetGrid() / 2);

		// ��ʃX�N���[���ɑΉ�������
		SetPosX(pos.x + CData::GetMoveQuantity() + GetGrid().x / 2);

		//=============================================================================
		// �z�u����I�u�W�F�N�g��؂�ւ���
		//=============================================================================
		// ���L�[
		if (CManager::GetKeyboard()->GetTrigger(DIK_DOWN))
		{
			// �z�u����I�u�W�F�N�g�̎�ނ�؂�ւ�
			m_nType++;

			// �I�ׂ��ނ̌��E��˔j������
			if (m_nType == OBJ_TargetBlock)
			{
				// ��ԍŏ��̃I�u�W�F�N�g��m_nType�����炷
				m_nType = OBJ_NULL + 1;
			}

			// �I�΂ꂽ�I�u�W�F�N�g�̃e�N�X�`���ɕύX������
			BindTexture(CTexture::GetTexture(m_nType + tex));
		}

		// ��L�[
		if (CManager::GetKeyboard()->GetTrigger(DIK_UP))
		{
			// �z�u����I�u�W�F�N�g�̎�ނ�؂�ւ�
			m_nType--;

			// �I�ׂ��ނ̌��E��˔j������
			if (m_nType == OBJ_NULL)
			{
				// ��ԍŌ�̃I�u�W�F�N�g��m_nType�����炷
				m_nType = OBJ_TargetBlock - 1;
			}

			// �I�΂ꂽ�I�u�W�F�N�g�̃e�N�X�`���ɕύX������
			BindTexture(CTexture::GetTexture(m_nType + tex));
		}

		if (m_nType == OBJ_Goal)
		{
			// �S�[���p�̓e�N�X�`�����W�����炷
			SetTexture(0, D3DXVECTOR2(4.0f, 1.0f));
		}

		else if (m_nType == OBJ_Spiny)
		{
			// ���͌����ɂ���ăe�N�X�`�����W�����炷
			SetTexture(m_nSpinyDirection, D3DXVECTOR2(2.0f, 1.0f));
		}

		// �����������������͂�����ʂ�
		else
		{
			SetTexture(0, D3DXVECTOR2(1.0f, 1.0f));
		}

		//=============================================================================
		// ��ʃX�N���[��
		//=============================================================================
		// ���L�[
		if (CManager::GetKeyboard()->GetPress(DIK_LEFT))
		{
			CData::MoveQuantity(-GetGrid().x);
		}

		// �E�L�[
		if (CManager::GetKeyboard()->GetPress(DIK_RIGHT))
		{
			CData::MoveQuantity(GetGrid().x);
		}

		// (�Z�Z���v���X)�̑�����
		int mul = 1;

		if (CManager::GetKeyboard()->GetPress(DIK_LSHIFT))
		{
			mul *= 10;
		}

		if (CManager::GetKeyboard()->GetPress(DIK_LCONTROL))
		{
			mul *= -1;
		}

		//=============================================================================
		// m_move�̕ύX
		//=============================================================================
		// R�L�[
		if (CManager::GetKeyboard()->GetTrigger(DIK_R))
		{
			m_move += float(mul) / 10.0f;
		}

		// m_move�̌덷���Ԃ�
		m_move = roundf(m_move * 10.0f) / 10.0f;

		// �ő�l�A�ŏ��l�𒴉߂��Ȃ��悤����
		if (m_move > m_moveMax)
		{
			m_move = m_moveMax;
		}

		if (m_move < 0)
		{
			m_move = 0;
		}

		//=============================================================================
		// m_stoptime�̕ύX
		//=============================================================================
		// F�L�[
		if (CManager::GetKeyboard()->GetTrigger(DIK_F))
		{
			m_stoptime += mul;
		}

		// �ő�l�A�ŏ��l�𒴉߂��Ȃ��悤����
		if (m_stoptime > m_stopMax)
		{
			m_stoptime = m_stopMax;
		}

		if (m_stoptime < 0)
		{
			m_stoptime = 0;
		}

		//=============================================================================
		// m_col�̕ύX
		//=============================================================================
		if (CManager::GetKeyboard()->GetTrigger(DIK_Z))
		{
			m_col.r += mul;

			// �ő�l�A�ŏ��l�𒴉߂��Ȃ��悤����
			if (m_col.r > 255)
			{
				m_col.r = 255;
			}

			if (m_col.r < 0)
			{
				m_col.r = 0;
			}
		}

		if (CManager::GetKeyboard()->GetTrigger(DIK_X))
		{
			m_col.g += mul;

			// �ő�l�A�ŏ��l�𒴉߂��Ȃ��悤����
			if (m_col.g > 255)
			{
				m_col.g = 255;
			}

			if (m_col.g < 0)
			{
				m_col.g = 0;
			}
		}

		if (CManager::GetKeyboard()->GetTrigger(DIK_C))
		{
			m_col.b += mul;

			// �ő�l�A�ŏ��l�𒴉߂��Ȃ��悤����
			if (m_col.b > 255)
			{
				m_col.b = 255;
			}

			if (m_col.b < 0)
			{
				m_col.b = 0;
			}
		}

		if (CManager::GetKeyboard()->GetTrigger(DIK_V))
		{
			m_col.a += mul;

			// �ő�l�A�ŏ��l�𒴉߂��Ȃ��悤����
			if (m_col.a > 255)
			{
				m_col.a = 255;
			}

			if (m_col.a < 0)
			{
				m_col.a = 0;
			}
		}

		//=============================================================================
		// �I�u�W�F�N�g�̍폜
		//=============================================================================
		int TargetCount = 0;
		bool Cover = false;

		if (TargetPos.x != 0)
		{
			TargetCount = (int)TargetPos.x;
		}

		else if (TargetPos.y != 0)
		{
			TargetCount = (int)TargetPos.y;
		}

		// �����蔻��擾�p�̉��I�u�W�F�N�g�쐬
		CTentativeObj *ColisionObj = CTentativeObj::Create(GetPos() - GetGrid() / 2, D3DXVECTOR3(0.0f, 0.0f, 0.0f), GetSize() / 2.0f);

		for(int num = 0; num <= abs(TargetCount); num++)
		{
			CScene *scene = CoverMoveBlock(ColisionObj);
			// �����I�u�W�F�N�g�Ƃ��Ԃ����Ă�����
			if (scene != NULL)
			{
				if (scene->GetMove().x != 0)
				{
					m_Colisionmove = fabs(scene->GetMove().x);
				}

				else if (scene->GetMove().y != 0)
				{
					m_Colisionmove = fabs(scene->GetMove().y);
				}

				m_nColisionType = scene->GetobjType();
				m_Colisionstoptime = scene->GetStopTime();
				m_Colisioncol = scene->GetCol();

				Cover = true;
				break;
			}

			if (TargetPos.x != 0)
			{
				ColisionObj->SetPosX(ColisionObj->GetPos().x + float(Sign(TargetPos.x)) * GetGrid().x);
			}

			else if (TargetPos.y != 0)
			{
				ColisionObj->SetPosY(ColisionObj->GetPos().y + float(Sign(TargetPos.y)) * GetGrid().y);
			}
		}

		ColisionObj->Uninit();

		if (Cover)
		{
			col.g = 0.0f;
			col.b = 0.0f;
			col.a = 128.0f;

			// �E�N���b�N
			if (CManager::GetMouse()->GetPress(CMouse::DIM_R))
			{
				// �I�u�W�F�N�g���폜�A�c�ʂ𑝂₷
				CoverMoveBlock(ColisionObj)->SetDeath(true);
				plusQuantity(m_nColisionType);
			}
		}

		//=============================================================================
		// �I�u�W�F�N�g�̔z�u
		//=============================================================================
		else
		{
			col.a = 128.0f;

			// �g�O�Ȃ�z�u�͂ł��Ȃ�
			if (GetPos().x < 0.0f)
			{
				col.g = 0.0f;
				col.b = 0.0f;
			}

			else
			{
				// ���N���b�N
				if (CManager::GetMouse()->GetPress(CMouse::DIM_L))
				{
					if (m_nType == OBJ_Player)
					{
						if (GetQuantity(OBJ_Player) == 0)
						{
							plusQuantity(OBJ_Player);
						}

						PlayerReCreate();
					}

					D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

					if (TargetPos.x != 0)
					{
						move.x = m_move;
					}

					else if (TargetPos.y != 0)
					{
						move.y = m_move;
					}

					// �I�u�W�F�N�g��z�u����
					StageCreate(m_nType, D3DXVECTOR3((pos.x + CData::GetMoveQuantity()), pos.y, 0.0f), move, D3DXVECTOR3(TargetPos.x, TargetPos.y, 0.0f), m_stoptime, m_nSpinyDirection, m_col);
				}
			}
		}

		if (m_nType == OBJ_Spiny)
		{
			if (CManager::GetKeyboard()->GetTrigger(DIK_W))
			{
				m_nSpinyDirection--;

				if (m_nSpinyDirection < 0)
				{
					m_nSpinyDirection = 0;
				}
			}

			if (CManager::GetKeyboard()->GetTrigger(DIK_S))
			{
				m_nSpinyDirection++;

				if (m_nSpinyDirection > 1)
				{
					m_nSpinyDirection = 1;
				}
			}
		}

		if (m_nType == OBJ_NormalBlock)
		{
			if (TargetPos.x == 0.0f)
			{
				if (CManager::GetKeyboard()->GetTrigger(DIK_W))
				{
					TargetPos.y -= 1.0f;
				}

				if (CManager::GetKeyboard()->GetTrigger(DIK_S))
				{
					TargetPos.y += 1.0f;
				}
			}

			if (TargetPos.y == 0.0f)
			{
				if (CManager::GetKeyboard()->GetTrigger(DIK_A))
				{
					TargetPos.x -= 1.0f;
				}

				if (CManager::GetKeyboard()->GetTrigger(DIK_D))
				{
					TargetPos.x += 1.0f;
				}
			}
		}

		if (CManager::GetMouse()->GetTrigger(CMouse::DIM_W))
		{
			if (CoverMoveBlock(ColisionObj))
			{
				if (CoverMoveBlock(ColisionObj)->GetPriority() == CScene::PRIORITY_BLOCK)
				{
					float x = CoverMoveBlock(ColisionObj)->GetTargetPos().x / GetGrid().x;
					float y = CoverMoveBlock(ColisionObj)->GetTargetPos().y / GetGrid().y;

					TargetPos = D3DXVECTOR3(x, y, 0.0f);
				}

				m_move = m_Colisionmove;
				m_stoptime = m_Colisionstoptime;

				m_col = CoverMoveBlock(ColisionObj)->GetCol();
			}
		}

		if (CManager::GetKeyboard()->GetTrigger(DIK_SPACE))
		{
			TargetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			m_move = 0.0f;
			m_stoptime = 0;

			m_col.r = 255.0f;
			m_col.g = 255.0f;
			m_col.b = 255.0f;
			m_col.a = 255.0f;
		}

		// �Z�[�u��
		if (CPause::GetNowSave())
		{
			// �I�u�W�F�N�g���폜�A�c�ʂ𑝂₷
			SaveFile();
			m_nNowSave = 256;
		}
	}

	//=============================================================================
	// �S�I�u�W�F�N�g�������ʒu�ɖ߂��A�ݒu���[�h�ƃv���C���[�h�����ւ���
	//=============================================================================

	if (CData::GetPause() && CStageLoad::GetPlayer())
	{
		if (!CStageLoad::GetPlayer()->GetDeath())
		{
			// �G���^�[�L�[
			if (CManager::GetKeyboard()->GetTrigger(DIK_RETURN))
			{
				CData::ChangeNowGame();
				CData::ZeroMoveQuantity();
				ReturnTostartPosAll();
			}
		}
	}

	SetColor(col);
}

//=============================================================================
// �|���S���̕`�揈��
//=============================================================================
void CCursor::Draw()
{
	if (!CData::GetNowGame())
	{
		CScene2D::Draw();
		DrawObjInfo();
	}
}

CCursor *CCursor::Create(D3DXVECTOR3 speed, D3DXVECTOR3 size, LPDIRECT3DTEXTURE9 tex)
{
	CCursor* pCursor = new CCursor;

	if (pCursor != NULL)
	{
		pCursor->Init(CManager::GetRenderer()->GetMousePos(), speed, size, tex);
	}
	return pCursor;
}

//=============================================================================
// �I�u�W�F�N�g�̏ڍׂ�\��
//=============================================================================
void CCursor::DrawObjInfo()
{
	//=============================================================================
	// �z�u�\��̃I�u�W�F�N�g���
	//=============================================================================
	{
		string strType;

		switch (m_nType)
		{
		case OBJ_NormalBlock:
			strType = "�u���b�N";

			break;

		case OBJ_Player:
			strType = "�v���C���[";

			break;

		case OBJ_Goal:
			strType = "�S�[���I�u�W�F�N�g";

			break;

		case OBJ_Reverse:
			strType = "�d�͔��]�I�u�W�F�N�g";

			break;

		case OBJ_Spiny:
			strType = "���I�u�W�F�N�g";

			break;

		default:
			strType = "";

			break;
		}

		int recttop = SCREEN_HEIGHT / 16;
		RECT rect = { SCREEN_WIDTH - (SCREEN_WIDTH / 4), recttop, SCREEN_WIDTH, SCREEN_HEIGHT };
		RECT rectBg = rect;

		rectBg.left += 1;
		rectBg.top += 1;

		// �e�L�X�g�`��
		string str = "\n**********************\n\n";

		// �e�L�X�g�`��
		str += "���݂̃I�u�W�F�N�g�F" + strType + "\n�I�u�W�F�N�g�c�ʁF" + to_string(GetQuantity(m_nType)) + "\n";

		str += "\n**********************\n\n";
		
		if (m_nType == OBJ_NormalBlock)
		{
			// �e�L�X�g�`��
			str += "\n******�u���b�N�p******\n\n";

			str += "WASD�L�[�@�@: �ڕW�n�_�𓮂���\n\n";

			str += "R�L�[�@   �@: 1f���Ƃ̈ړ��������v���X(0.1f)\n";

			str += "F�L�[�@�@   : �Î~���Ԃ��v���X(1F)\n\n";

			str += "Z�L�[�@�@   : �J���[�l(��)���v���X\n";
			str += "X�L�[�@�@   : �J���[�l(��)���v���X\n";
			str += "C�L�[�@�@   : �J���[�l(��)���v���X\n";
			str += "V�L�[�@�@   : �J���[�l(�����x)���v���X\n\n";

			str += "(LSHIFT�L�[���������Ő��l��*10)\n";
			str += "(LCTRL�L�[���������Ő��l���}�C�i�X�ɂ���)\n\n";

			str += "�}�E�X�z�C�[���N���b�N�@: �u���b�N�̏ڍ׃R�s�[\n";
			str += "�X�y�[�X�L�[          �@: �u���b�N�̏ڍ׃��Z�b�g\n";

			str += "\n**********************\n\n";

			str += "�u���b�N�̖ڕW�n�_        : x=" + to_string(int(TargetPos.x)) + ", y=" + to_string(int(TargetPos.y)) + "\n";
			str += "�u���b�N��1f���Ƃ̈ړ�����: " + to_string(m_move) + "\n";
			str += "�u���b�N�̐Î~����        : " + to_string(m_stoptime) + "\n";

			str += "�J���[�l(��)              : " + to_string((int)m_col.r) + "\n";
			str += "�J���[�l(��)              : " + to_string((int)m_col.g) + "\n";
			str += "�J���[�l(��)              : " + to_string((int)m_col.b) + "\n";
			str += "�J���[�l(�����x)          : " + to_string((int)m_col.a) + "\n";

			str += "\n**********************\n\n";
		}

		string strBg = str;

		CManager::GetRenderer()->GetFont()->DrawText(NULL, strBg.c_str(), -1, &rectBg, DT_LEFT, D3DCOLOR_ARGB(0xff, 0x00, 0x00, 0x00));
		rect.top += CManager::GetRenderer()->GetFont()->DrawText(NULL, str.c_str(), -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
	}

	//=============================================================================
	// �G��Ă���I�u�W�F�N�g�̏��
	//=============================================================================
	{
		string strType;

		switch (m_nColisionType)
		{
		case OBJ_NormalBlock:
			strType = "�u���b�N";

			break;

		case OBJ_Player:
			strType = "�v���C���[";

			break;

		case OBJ_Goal:
			strType = "�S�[���I�u�W�F�N�g";

			break;

		case OBJ_Reverse:
			strType = "�d�͔��]�I�u�W�F�N�g";

			break;

		case OBJ_Spiny:
			strType = "���I�u�W�F�N�g";

			break;

		default:
			strType = "";

			break;
		}

		RECT rect = { 0, SCREEN_HEIGHT / 6, 350, 700 };
		RECT rectBg = rect;

		rectBg.left += 1;
		rectBg.top += 1;

		// �e�L�X�g�`��
		// �e�L�X�g�`��
		string str = "*******������@*******\n\n";

		str += "���N���b�N�@   : �u���b�N�z�u\n";
		str += "�E�N���b�N   �@: �u���b�N����\n";
		str += "���L�[�㉺   : �u���b�N�̎�ނ�ύX\n";
		str += "���L�[���E   : ��ʃX�N���[��\n";
		str += "�G���^�[�L�[   : �Q�[���̃e�X�g\n";
		str += "�G�X�P�[�v�L�[ : �|�[�Y\n";

		str += "\n**********************\n\n";

		str += "*****�G��Ă���I�u�W�F�N�g*****\n\n";

		str += "�I�u�W�F�N�g          �F" + strType + "\n";

		if (m_nColisionType == OBJ_NormalBlock)
		{
			str += "1f������̈ړ���      �F" + to_string(m_Colisionmove) + "\n";
			str += "�ړ����Ă���̐Î~���ԁF" + to_string(m_Colisionstoptime) + "\n";

			str += "�J���[�l(��)          �F" + to_string(m_Colisioncol.r) + "\n";
			str += "�J���[�l(��)          �F" + to_string(m_Colisioncol.g) + "\n";
			str += "�J���[�l(��)          �F" + to_string(m_Colisioncol.b) + "\n";
			str += "�J���[�l(�����x)      �F" + to_string(m_Colisioncol.a) + "\n";
		}

		str += "\n******************************\n\n";

		string strBg = str;

		CManager::GetRenderer()->GetFont()->DrawText(NULL, strBg.c_str(), -1, &rectBg, DT_LEFT, D3DCOLOR_ARGB(0xff, 0x00, 0x00, 0x00));
		rect.top += CManager::GetRenderer()->GetFont()->DrawText(NULL, str.c_str(), -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
	}

	//=============================================================================
	// [�Z�[�u��...]�\��
	//=============================================================================
	if(m_nNowSave > 0)
	{
		m_nNowSave--;

		string str = "�X�e�[�W���Z�[�u���܂���...";

		RECT rect = { 0, SCREEN_HEIGHT / 12, SCREEN_WIDTH, SCREEN_HEIGHT };
		RECT rectBg = rect;

		rectBg.left += 1;
		rectBg.top += 1;

		string strBg = str;

		CManager::GetRenderer()->GetFont()->DrawText(NULL, strBg.c_str(), -1, &rectBg, DT_LEFT, D3DCOLOR_ARGB(0xff, 0x00, 0x00, 0x00));
		rect.top += CManager::GetRenderer()->GetFont()->DrawText(NULL, str.c_str(), -1, &rect, DT_LEFT, D3DCOLOR_ARGB(m_nNowSave, 0xff, 0xff, 0xff));

		if (m_nNowSave < 0)
		{
			m_nNowSave = 0;
		}
	}
}
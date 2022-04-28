//=============================================================================
//
// �V�[������ [scene.cpp]
// Author : 
//
//=============================================================================
#include "scene.h"
#include "renderer.h"

CScene *CScene::m_pTop[] = {};
CScene *CScene::m_pBot[] = {};

int CScene::m_nNumAll = 0;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CScene::CScene(int nPriority)
{
	if (m_pTop[nPriority] == NULL)
	{
		m_pTop[nPriority] = this;				// this��擪�ɐݒ�
	}

	else
	{
		m_pBot[nPriority]->m_pNext = this;		// �Ō���I�u�W�F�N�g��m_pNext��this�ɐݒ�
		m_pPrev = m_pBot[nPriority];			// m_pPrev�ɍŌ���I�u�W�F�N�g��ݒ�
	}

	m_pNext = NULL;								// �������Ō���ɂȂ�̂�m_pNext��NULL�ɂ���
	m_pBot[nPriority] = this;					// �Ō���I�u�W�F�N�g��this�ɐݒ�

	m_nNumAll++;								// �|���S���̐���++
	m_nPriority = nPriority;					// �K�w��ݒ�

	m_TargetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nStopTime = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CScene::~CScene()
{

}

//=============================================================================
// �I�u�W�F�N�g��S�ď���
//=============================================================================
void CScene::ReleaseAll()
{
	for (int nPriority = PRIORITY_NONE; nPriority < PRIORITY_MAX; nPriority++)
	{
		CScene *UninitObj = m_pTop[nPriority];				// ���삷��I�u�W�F�N�g

		while (UninitObj != NULL)
		{
			if (UninitObj->GetPriority() != PRIORITY_FADE)
			{
				UninitObj->Uninit();
			}

			UninitObj = UninitObj->m_pNext;		// ���삷��I�u�W�F�N�g��m_pNext�ɂ���
		}
	}
}

//=============================================================================
// �I�u�W�F�N�g���ЂƂ���
//=============================================================================
void CScene::Release(int nPriority)
{
	//=============================================================================
	// m_pTop�Am_pBot�֘A�̏���
	//=============================================================================
	if (this == m_pTop[nPriority] &&
		this == m_pBot[nPriority])
	{
		m_pTop[nPriority] = NULL;
		m_pBot[nPriority] = NULL;
		m_pNext = NULL;
		m_pPrev = NULL;
	}

	else if (this == m_pTop[nPriority])
	{
		m_pTop[nPriority] = m_pNext;
		m_pPrev = NULL;
		m_pNext->m_pPrev = NULL;		// m_pPrev���Athis��m_pPrev�ɐݒ�
	}

	else if (this == m_pBot[nPriority])
	{
		m_pBot[nPriority] = m_pPrev;
		m_pNext = NULL;
		m_pPrev->m_pNext = NULL;		// m_pNext���Athis��m_pNext�ɐݒ�
	}

	else
	{
		//=============================================================================
		// ���I�u�W�F�N�g�ƑO�I�u�W�F�N�g������
		//=============================================================================
		m_pNext->m_pPrev = m_pPrev;		// this��m_pPrev���Am_pNext��m_pPrev�ɐݒ�
		m_pPrev->m_pNext = m_pNext;		// this��m_pNext���Am_pNext��m_pNext�ɐݒ�
	}

	m_nNumAll--;				//�|���S���̐���--
}

//=============================================================================
// �S�ẴI�u�W�F�N�g���X�V
//=============================================================================
void CScene::UpdateAll()
{
	for (int nPriority = PRIORITY_NONE; nPriority < PRIORITY_MAX; nPriority++)
	{
		CScene *UpdateObj = m_pTop[nPriority];				// ���삷��I�u�W�F�N�g

		while (UpdateObj)
		{
			if (UpdateObj->GetDeath())
			{
				CScene *UpdateObj2 = UpdateObj;		// UpdateObj���ꎞ�ۊǗp�ϐ��Ɋi�[
				UpdateObj->Uninit();				// UpdateObj���폜
				UpdateObj = UpdateObj2->m_pNext;	// ���삷��I�u�W�F�N�g��m_pNext�ɂ���
			}

			else
			{
				UpdateObj->SetPosold(UpdateObj->GetPos());
				UpdateObj->Update();
				

				UpdateObj = UpdateObj->m_pNext;		// ���삷��I�u�W�F�N�g��m_pNext�ɂ���
			}
		}
	}
}

//=============================================================================
// �S�ẴI�u�W�F�N�g��`��
//=============================================================================
void CScene::DrawAll()
{
	for (int nPriority = PRIORITY_NONE; nPriority < PRIORITY_MAX; nPriority++)
	{
		CScene *DrawObj = m_pTop[nPriority];				// ���삷��I�u�W�F�N�g

		while (DrawObj != NULL)
		{
			DrawObj->Draw();
			DrawObj = DrawObj->m_pNext;			// ���삷��I�u�W�F�N�g��m_pNext�ɂ���
		}
	}
}

//=============================================================================
// �I�u�W�F�N�g�������ʒu�ɖ߂�
//=============================================================================
void CScene::ReturnTostartPos(CScene *scene)
{
	CScene *ReturnObj = scene;				// ���삷��I�u�W�F�N�g

	if(ReturnObj != NULL)
	{
		if (ReturnObj->GetPriority() != PRIORITY_FADE)
		{
			ReturnObj->SetPos(ReturnObj->GetstartPos());
			ReturnObj->SetPosold(ReturnObj->GetstartPos());
			ReturnObj->SetMove(ReturnObj->GetstartMove());
		}
	}
}

//=============================================================================
// �I�u�W�F�N�g�������ʒu�ɖ߂�
//=============================================================================
void CScene::ReturnTostartPosAll()
{
	for (int nPriority = PRIORITY_NONE; nPriority < PRIORITY_MAX; nPriority++)
	{
		CScene *ReturnObj = m_pTop[nPriority];				// ���삷��I�u�W�F�N�g

		while (ReturnObj != NULL)
		{
			if (ReturnObj->GetPriority() != PRIORITY_FADE)
			{
				ReturnObj->SetPos(ReturnObj->GetstartPos());
				ReturnObj->SetPosold(ReturnObj->GetstartPos());
				ReturnObj->SetMove(ReturnObj->GetstartMove());

				for (int nCnt = 0; nCnt < DIRECTION_MAX; nCnt++)
				{
					ReturnObj->SetColision(NULL, nCnt);
				}
			}

			ReturnObj = ReturnObj->m_pNext;		// ���삷��I�u�W�F�N�g��m_pNext�ɂ���
		}
	}
}

//=============================================================================
// ���l�̕������擾����
//=============================================================================
int CScene::Sign(float num)
{
	// num��1�ȏ�Ȃ�1��Ԃ�
	if (num > 0)
	{
		return 1;
	}

	// num��-1�ȉ��Ȃ�1��Ԃ�
	if (num < 0)
	{
		return -1;
	}

	// num��0�Ȃ�0��Ԃ�
	return 0;
}

void CScene::RandomShake(D3DXVECTOR3 shakerand)
{
	std::random_device rnd;
	std::mt19937 mt(rnd());
	std::uniform_real_distribution<> randX(-shakerand.x, shakerand.x);
	std::uniform_real_distribution<> randY(-shakerand.y, shakerand.y);

	D3DXVECTOR3 rand;
	rand.x = (float)randX(mt);
	rand.y = (float)randY(mt);
	rand.z = 0.0f;

	for (int nPriority = PRIORITY_BGOBJECT; nPriority < PRIORITY_OBJMAX; nPriority++)
	{
		CScene *SetPosObj = m_pTop[nPriority];		// ���삷��I�u�W�F�N�g

		while (SetPosObj != NULL)
		{
			SetPosObj->SetPos(SetPosObj->GetPos() + rand);
			SetPosObj = SetPosObj->m_pNext;			// ���삷��I�u�W�F�N�g��m_pNext�ɂ���
		}
	}
}
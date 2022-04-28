//=============================================================================
//
// �V�[������ [scene2D.cpp]
// Author : �O���B
//
//=============================================================================
#include "scene2D.h"
#include "manager.h"
#include "renderer.h"
#include "stageload.h"
#include "player.h"
#include "data.h"
#include "normalblock.h"
#include "tentativeobj.h"
#include "texture.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CScene2D::CScene2D(CScene::PRIORITY nPriority) : CScene(nPriority)
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CScene2D::~CScene2D()
{

}

//=============================================================================
// �|���S���̏���������
//=============================================================================
HRESULT CScene2D::Init(LPDIRECT3DTEXTURE9 tex)
{
	SetPos(GetPos());
	SetstartPos(GetPos());

	SetMove(GetMove());
	SetstartMove(GetMove());

	SetSize(GetSize());
	SetDeath(false);

	SetobjType(GetobjType());

	BindTexture(tex);

	D3DCOLORVALUE col;
	col.r = 255.0f;
	col.g = 255.0f;
	col.b = 255.0f;
	col.a = 255.0f;

	// ���_����ݒ�
	LPDIRECT3DDEVICE9 pDevice;						//�f�o�C�X�̃|�C���^
	pDevice = CManager::GetRenderer()->GetDevice();	//�f�o�C�X���擾

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_2D *pVtx;					//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x			, m_pos.y			, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y			, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x			, m_pos.y + m_size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y + m_size.y, 0.0f);

	//rhw�̐ݒ�(1.0f�Œ�)
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA((int)col.r, (int)col.g, (int)col.b, (int)col.a);
	pVtx[1].col = D3DCOLOR_RGBA((int)col.r, (int)col.g, (int)col.b, (int)col.a);
	pVtx[2].col = D3DCOLOR_RGBA((int)col.r, (int)col.g, (int)col.b, (int)col.a);
	pVtx[3].col = D3DCOLOR_RGBA((int)col.r, (int)col.g, (int)col.b, (int)col.a);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

	SetPositionCenter(GetPos(), GetSize());

	return S_OK;
}

//=============================================================================
// �|���S���̏I������
//=============================================================================
void CScene2D::Uninit(void)
{
	//���_�o�b�t�@�j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	Release(GetPriority());
}

//=============================================================================
// �|���S���̍X�V����
//=============================================================================
void CScene2D::Update(void)
{
	
}

//=============================================================================
// �|���S���̕`�揈��
//=============================================================================
void CScene2D::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;						//�f�o�C�X�̃|�C���^
	pDevice = CManager::GetRenderer()->GetDevice();	//�f�o�C�X���擾

													// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetStreamSource(
		0,
		m_pVtxBuff,
		0,
		sizeof(VERTEX_2D));

	pDevice->SetFVF(FVF_VERTEX_2D);					//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetTexture(0, m_pTexture);				//�e�N�X�`���̐ݒ�

	// �|���S���̕`��
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,						//�v���~�e�B�u�̎��
		0,											//�J�n���钸�_�̃C���f�b�N�X
		2);											//�v���~�e�B�u�̐�
}



//=============================================================================
// �e�N�X�`���̊��蓖��
//=============================================================================
void CScene2D::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}

//=============================================================================
// �|�W�V�����̍X�V
//=============================================================================
void CScene2D::SetPositionDefault(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	m_pos = pos;
	m_size = size;
	float move = 0.0f;

	if (GetPriority() > PRIORITY_BG &&
		GetPriority() < PRIORITY_CURSOR)
	{
		move = CData::GetMoveQuantity();
	}

	VERTEX_2D *pVtx;								//���_���ւ̃|�C���^

													//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - move			, m_pos.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x - move + m_size.x	, m_pos.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - move			, m_pos.y + m_size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x - move + m_size.x	, m_pos.y + m_size.y, 0.0f);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

	SetPos(m_pos + GetMove());
	SetSize(m_size);
}

//=============================================================================
// �|�W�V�����̍X�V
//=============================================================================
void CScene2D::SetPositionCenter(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	m_pos = pos;
	m_size = size;
	float Quantity = 0.0f;

	if (CData::GetPause() &&
		CData::GetNowGame())
	{
		m_move = GetMove();
	}
	
	else
	{
		m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	if (GetPriority() > PRIORITY_BG &&
		GetPriority() < PRIORITY_OBJMAX)
	{
		Quantity = CData::GetMoveQuantity();
	}

	VERTEX_2D *pVtx;								//���_���ւ̃|�C���^

													//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - Quantity - m_size.x / 2, m_pos.y - m_size.y / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x - Quantity + m_size.x / 2, m_pos.y - m_size.y / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - Quantity - m_size.x / 2, m_pos.y + m_size.y / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x - Quantity + m_size.x / 2, m_pos.y + m_size.y / 2, 0.0f);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

	if (CData::GetNowGame())
	{
		SetPos(m_pos + m_move);
	}

	else	SetPos(GetstartPos());

	SetSize(m_size);
}

//=============================================================================
// �e�N�X�`���̍X�V
//=============================================================================
void CScene2D::SetTexture(int ptnAnim, D3DXVECTOR2 split)	//ptnAnim = ���݂̃p�^�[��, split = ���������邩
{
	Setptn(ptnAnim);

	D3DXVECTOR2 fSplit = D3DXVECTOR2(1.0f / split.x, 1.0f / split.y);

	VERTEX_2D *pVtx;										//���_���ւ̃|�C���^

															//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(fSplit.x * ptnAnim, fSplit.y * ptnAnim);
	pVtx[1].tex = D3DXVECTOR2(fSplit.x + (fSplit.x * ptnAnim), fSplit.y * ptnAnim);
	pVtx[2].tex = D3DXVECTOR2(fSplit.x * ptnAnim, fSplit.y + (fSplit.y * ptnAnim));
	pVtx[3].tex = D3DXVECTOR2(fSplit.x + (fSplit.x * ptnAnim), fSplit.y + (fSplit.y * ptnAnim));

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �e�N�X�`���X�N���[��
//=============================================================================
void CScene2D::ScrollTexture(D3DXVECTOR3 move)
{
	VERTEX_2D *pVtx;										//���_���ւ̃|�C���^

															//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f + move.x, 0.0f + move.y);
	pVtx[1].tex = D3DXVECTOR2(1.0f + move.x, 0.0f + move.y);
	pVtx[2].tex = D3DXVECTOR2(0.0f + move.x, 1.0f + move.y);
	pVtx[3].tex = D3DXVECTOR2(1.0f + move.x, 1.0f + move.y);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �F�̍X�V
//=============================================================================
void CScene2D::SetColor(D3DCOLORVALUE col)
{
	SetCol(col);
	VERTEX_2D *pVtx;										//���_���ւ̃|�C���^

															//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA((int)col.r, (int)col.g, (int)col.b, (int)col.a);
	pVtx[1].col = D3DCOLOR_RGBA((int)col.r, (int)col.g, (int)col.b, (int)col.a);
	pVtx[2].col = D3DCOLOR_RGBA((int)col.r, (int)col.g, (int)col.b, (int)col.a);
	pVtx[3].col = D3DCOLOR_RGBA((int)col.r, (int)col.g, (int)col.b, (int)col.a);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

// �Ή�����bool�l��Ԃ�
bool CScene2D::Colision(CScene *sceneA, CScene *sceneB)
{
	//=============================================================================
	// �ڐG��
	//=============================================================================
	if (sceneA->GetPos().x + sceneA->GetSize().x / 2.0f > sceneB->GetPos().x - sceneB->GetSize().x / 2.0f &&	// �I�u�W�F�N�g�̉E�[�Ƀu���b�N
		sceneA->GetPos().x - sceneA->GetSize().x / 2.0f < sceneB->GetPos().x + sceneB->GetSize().x / 2.0f &&	// �I�u�W�F�N�g�̍��[�Ƀu���b�N
		sceneA->GetPos().y + sceneA->GetSize().y / 2.0f > sceneB->GetPos().y - sceneB->GetSize().y / 2.0f &&	// �I�u�W�F�N�g�̉��[�Ƀu���b�N
		sceneA->GetPos().y - sceneA->GetSize().y / 2.0f < sceneB->GetPos().y + sceneB->GetSize().y / 2.0f)	// �I�u�W�F�N�g�̏�[�Ƀu���b�N
	{
		return true;
	}

	return false;
}

// ���ʂƂ���true��Ԃ�
void CScene2D::ColisionBlock()
{
	for (int num = PRIORITY_PLAYER; num < PRIORITY_OBJMAX; num++)
	{
		CScene *scene = GetTop(num);	// �u���b�N�̃I�u�W�F�N�g
		CScene *Col[DIRECTION_MAX] = {};

		while (scene != NULL)
		{
			float scene_left = scene->GetPos().x - scene->GetSize().x / 2.0f;
			float scene_right = scene->GetPos().x + scene->GetSize().x / 2.0f;
			float scene_top = scene->GetPos().y - scene->GetSize().y / 2.0f;
			float scene_bot = scene->GetPos().y + scene->GetSize().y / 2.0f;

			float sceneold_left = scene->GetPosold().x - scene->GetSize().x / 2.0f;
			float sceneold_right = scene->GetPosold().x + scene->GetSize().x / 2.0f;
			float sceneold_top = scene->GetPosold().y - scene->GetSize().y / 2.0f;
			float sceneold_bot = scene->GetPosold().y + scene->GetSize().y / 2.0f;

			float scenemoveX = scene->GetMove().x;
			float scenemoveY = scene->GetMove().y;

			for (int num2 = PRIORITY_BLOCK; num2 < PRIORITY_TARGETBLOCK; num2++)
			{
				if (num2 == PRIORITY_REVERSE)
				{
					continue;
				}

				CScene *scene2 = GetTop(num2);	// �u���b�N�̃I�u�W�F�N�g
				CScene *Col2[DIRECTION_MAX] = {};

				while (scene2 != NULL)
				{
					float scene2_left = scene2->GetPos().x - scene2->GetSize().x / 2.0f;
					float scene2_right = scene2->GetPos().x + scene2->GetSize().x / 2.0f;
					float scene2_top = scene2->GetPos().y - scene2->GetSize().y / 2.0f;
					float scene2_bot = scene2->GetPos().y + scene2->GetSize().y / 2.0f;

					float scene2old_left = scene2->GetPosold().x - scene2->GetSize().x / 2.0f;
					float scene2old_right = scene2->GetPosold().x + scene2->GetSize().x / 2.0f;
					float scene2old_top = scene2->GetPosold().y - scene2->GetSize().y / 2.0f;
					float scene2old_bot = scene2->GetPosold().y + scene2->GetSize().y / 2.0f;

					if (scene != scene2)
					{
						if (scene->GetPos().x - scene2->GetPos().x < fabs(CStageLoad::GetGrid().x * 4.0f) &&
							scene->GetPos().y - scene2->GetPos().y < fabs(CStageLoad::GetGrid().y * 4.0f))
						//=============================================================================
						// �ڐG��
						//=============================================================================
						if (Colision(scene, scene2))
						{
							// ������Փ�
							if (sceneold_top >= scene2old_bot)
							{
								// ���E����̔���œ������Ă��Ȃ���Α���
								if (!(scene_left + scenemoveX < scene2_right &&
									sceneold_left >= scene2old_right) &&

									!(scene_right + scenemoveX > scene2_left &&
									sceneold_right <= scene2old_left))
								{
									scene->SetPosY(scene->GetPos().y + (scene2_bot - scene_top));
									scene->SetMoveY(scene2->GetMove().y);

									Col[DIRECTION_UP] = scene2;
									Col2[DIRECTION_DOWN] = scene;
								}

								// �΂߂���Փ˂����ۂ̔���(X�������o��)
								else if (!scene->GetColision(DIRECTION_UP))
								{
									if (sceneold_left >= scene2old_right)
									{
										scene->SetPosX(scene->GetPos().x + (scene2_right - scene_left));
										scene->SetMoveX(scene2->GetMove().x);

										Col[DIRECTION_LEFT] = scene2;
										Col2[DIRECTION_RIGHT] = scene;
									}

									if (sceneold_right <= scene2old_left)
									{
										scene->SetPosX(scene->GetPos().x + (scene2_left - scene_right));
										scene->SetMoveX(scene2->GetMove().x);

										Col[DIRECTION_RIGHT] = scene2;
										Col2[DIRECTION_LEFT] = scene;
									}
								}
							}

							// �ォ��
							if (sceneold_bot <= scene2old_top)
							{
								// ���E����̔���œ������Ă��Ȃ���Α���
								if (!(scene_left + scenemoveX < scene2_right &&
									sceneold_left >= scene2old_right) &&

									!(scene_right + scenemoveX > scene2_left &&
									sceneold_right <= scene2old_left))
								{
									scene->SetPosY(scene->GetPos().y + (scene2_top - scene_bot));
									scene->SetMoveY(scene2->GetMove().y);

									Col[DIRECTION_DOWN] = scene2;
									Col2[DIRECTION_UP] = scene;
								}

								// �΂߂���Փ˂����ۂ̔���(X�������o��)
								else if(!scene->GetColision(DIRECTION_DOWN))
								{
									if (sceneold_left >= scene2old_right)
									{
										scene->SetPosX(scene->GetPos().x + (scene2_right - scene_left));
										scene->SetMoveX(scene2->GetMove().x);

										Col[DIRECTION_LEFT] = scene2;
										Col2[DIRECTION_RIGHT] = scene;
									}

									if (sceneold_right <= scene2old_left)
									{
										scene->SetPosX(scene->GetPos().x + (scene2_left - scene_right));
										scene->SetMoveX(scene2->GetMove().x);

										Col[DIRECTION_RIGHT] = scene2;
										Col2[DIRECTION_LEFT] = scene;
									}
								}
							}

							if (Colision(scene, scene2))
							{
								// �E����
								if (sceneold_left >= scene2old_right)
								{
									// �㉺����̔���œ������Ă��Ȃ���Α���
									if (!(scene_top + scenemoveY < scene2_bot &&
										sceneold_top >= scene2old_bot) &&

										!(scene_bot + scenemoveY > scene2_top &&
											sceneold_bot <= scene2old_top))
									{
										scene->SetPosX(scene->GetPos().x + (scene2_right - scene_left));
										scene->SetMoveX(scene2->GetMove().x);

										Col[DIRECTION_LEFT] = scene2;
										Col2[DIRECTION_RIGHT] = scene;
									}
								}

								// ������
								if (sceneold_right <= scene2old_left)
								{
									// �㉺����̔���œ������Ă��Ȃ���Α���
									if (!(scene_top + scenemoveY < scene2_bot &&
										sceneold_top >= scene2old_bot) &&

										!(scene_bot + scenemoveY > scene2_top &&
											sceneold_bot <= scene2old_top))
									{
										scene->SetPosX(scene->GetPos().x + (scene2_left - scene_right));
										scene->SetMoveX(scene2->GetMove().x);

										Col[DIRECTION_RIGHT] = scene2;
										Col2[DIRECTION_LEFT] = scene;
									}
								}
							}
						}
					}

					for (int nCnt = 0; nCnt < DIRECTION_MAX; nCnt++)
					{
						scene2->SetColision(Col2[nCnt], nCnt);
					}

					// ���삷��I�u�W�F�N�g��m_pNext�ɂ���
					scene2 = scene2->GetNext();
				}
			}

			for (int nCnt = 0; nCnt < DIRECTION_MAX; nCnt++)
			{
				if (nCnt == DIRECTION_UP || nCnt == DIRECTION_DOWN)
				{
					if (Col[nCnt] != NULL)
					{
						if ((CManager::GetData()->GetGravity() < 0.0f || CManager::GetData()->GetGravity() > 0.0f) &&
							Col[nCnt]->GetPriority() == PRIORITY_BLOCK &&
							Col[nCnt]->GetMove().x != 0.0f)
						{
							scene->SetMoveX(Col[nCnt]->GetMove().x);
						}
					}
				}

				scene->SetColision(Col[nCnt], nCnt);
			}

			// ���삷��I�u�W�F�N�g��m_pNext�ɂ���
			scene = scene->GetNext();
		}
	}
}

// �J�[�\���ƃu���b�N�����Ԃ����Ă�����true��Ԃ�
CScene *CScene2D::CoverBlock(CScene2D *scene)
{
	for (int nCnt = PRIORITY_BLOCK; nCnt < PRIORITY_OBJMAX; nCnt++)
	{
		CScene *SceneBlock = CScene::GetTop(nCnt);	// �u���b�N�̃I�u�W�F�N�g

		while (SceneBlock != NULL)
		{
			if (scene != SceneBlock)
			{
				//=============================================================================
				// �ڐG��
				//=============================================================================
				if (Colision(scene, SceneBlock))
				{
					return SceneBlock;
				}
			}

			// ���삷��I�u�W�F�N�g��m_pNext�ɂ���
			SceneBlock = SceneBlock->GetNext();
		}
	}

	return NULL;
}

// �J�[�\���ƃu���b�N�����Ԃ����Ă�����true��Ԃ�
CScene *CScene2D::CoverMoveBlock(CScene2D *scene)
{
	for (int nCnt = PRIORITY_BLOCK; nCnt < PRIORITY_OBJMAX; nCnt++)
	{
		CScene *SceneBlock = CScene::GetTop(nCnt);	// �u���b�N�̃I�u�W�F�N�g

		while (SceneBlock != NULL)
		{
			if (scene != SceneBlock)
			{
				int TargetCount = 0;
				D3DXVECTOR3 TargetPos = SceneBlock->GetTargetPos();

				if (TargetPos.x != 0)
				{
					TargetCount = (int)TargetPos.x / (int)CStageLoad::GetGrid().x;
				}

				else if (TargetPos.y != 0)
				{
					TargetCount = (int)TargetPos.y / (int)CStageLoad::GetGrid().y;
				}

				for (int num = 0; num <= abs(TargetCount); num++)
				{
					//=============================================================================
					// �ڐG��
					//=============================================================================
					if (Colision(scene, SceneBlock))
					{
						SceneBlock->SetPos(SceneBlock->GetstartPos());
						return SceneBlock;
					}

					if (TargetPos.x != 0)
					{
						SceneBlock->SetPosX(SceneBlock->GetstartPos().x + Sign(TargetCount) * (num + 1) * CStageLoad::GetGrid().x);
					}

					else if (TargetPos.y != 0)
					{
						SceneBlock->SetPosY(SceneBlock->GetstartPos().y + Sign(TargetCount) * (num + 1) * CStageLoad::GetGrid().y);
					}
				}

				SceneBlock->SetPos(SceneBlock->GetstartPos());
			}

			// ���삷��I�u�W�F�N�g��m_pNext�ɂ���
			SceneBlock = SceneBlock->GetNext();
		}
	}

	return NULL;
}

void CScene2D::PlayerReCreate()
{
	CScene *Player = CScene::GetTop(PRIORITY_PLAYER);	// �u���b�N�̃I�u�W�F�N�g

	while (Player != NULL)
	{
		Player->Uninit();
		Player = Player->GetNext();		// ���삷��I�u�W�F�N�g��m_pNext�ɂ���
	}
}

//=============================================================================
// �e�N�X�`���̃��[�h
//=============================================================================
HRESULT CScene2D::Load(const char *aTextureName)
{
	LPDIRECT3DDEVICE9 pDevice;						//�f�o�C�X�̃|�C���^
	pDevice = CManager::GetRenderer()->GetDevice();	//�f�o�C�X���擾

													// �e�N�X�`�����[�h
	D3DXCreateTextureFromFile(
		pDevice,
		aTextureName,
		&m_pTexture);

	return S_OK;
}
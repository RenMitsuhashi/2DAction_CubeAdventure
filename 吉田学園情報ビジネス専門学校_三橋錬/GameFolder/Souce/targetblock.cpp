//=============================================================================
//
// �ʏ�u���b�N [targetblock.cpp]
// Author : �O���B
//
//=============================================================================
#include "targetblock.h"
#include "manager.h"
#include "renderer.h"
#include "Stageload.h"
#include "data.h"
#include "tentativeobj.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTargetBlock::CTargetBlock(CScene::PRIORITY nPriority) : CScene2D(nPriority)
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTargetBlock::~CTargetBlock()
{

}

//=============================================================================
// �|���S���̏���������
//=============================================================================
HRESULT CTargetBlock::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXVECTOR3 targetpos, int stoptime, LPDIRECT3DTEXTURE9 tex)
{
	SetPos(pos);
	SetMove(move);
	SetSize(size);
	SetDeath(false);

	CScene2D::Init(tex);

	SetTargetPos(targetpos);
	SetStopTime(stoptime);

	return S_OK;
}

//=============================================================================
// �|���S���̏I������
//=============================================================================
void CTargetBlock::Uninit()
{
	CScene2D::Uninit();
}

//=============================================================================
// �|���S���̍X�V����
//=============================================================================
void CTargetBlock::Update()
{
	if (!CData::GetNowGame())
	{
		CTentativeObj *ColisionObj = CTentativeObj::Create(GetPos() + GetTargetPos(), GetMove(), GetSize());

		if (!CoverBlock(ColisionObj))
		{
			SetDeath(true);
		}

		ColisionObj->Uninit();
	}

	SetPositionCenter(GetPos(), GetSize());
}

//=============================================================================
// �|���S���̕`�揈��
//=============================================================================
void CTargetBlock::Draw()
{
	if (!CData::GetNowGame())
	{
		CScene2D::Draw();
	}
}

CTargetBlock *CTargetBlock::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXVECTOR3 targetpos, int stoptime, LPDIRECT3DTEXTURE9 tex)
{
	CTargetBlock* pTargetBlock = new CTargetBlock;

	if (pTargetBlock != NULL)
	{
		pTargetBlock->Init(pos, move, size, targetpos, stoptime, tex);

		pTargetBlock->SetTargetPos(targetpos);

		D3DCOLORVALUE col;
		col.r = 255.0f;
		col.g = 255.0f;
		col.b = 255.0f;
		col.a = 192.0f;

		pTargetBlock->SetColor(col);
	}

	return pTargetBlock;
}
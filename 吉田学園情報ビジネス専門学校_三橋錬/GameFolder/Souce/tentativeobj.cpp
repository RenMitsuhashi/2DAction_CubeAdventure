//=============================================================================
//
// ���I�u�W�F�N�g [tentativeobj.cpp]
// Author : �O���B
//
//=============================================================================
#include "tentativeobj.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTentativeObj::CTentativeObj(CScene::PRIORITY nPriority) : CScene2D(nPriority)
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTentativeObj::~CTentativeObj()
{

}

//=============================================================================
// �|���S���̏���������
//=============================================================================
HRESULT CTentativeObj::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size)
{
	SetPos(pos);
	SetMove(move);
	SetSize(size);
	SetDeath(false);

	CScene2D::Init(NULL);

	return S_OK;
}

//=============================================================================
// �|���S���̏I������
//=============================================================================
void CTentativeObj::Uninit()
{
	Release(GetPriority());
}

CTentativeObj *CTentativeObj::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size)
{
	CTentativeObj* pTentativeObj = new CTentativeObj;

	if (pTentativeObj != NULL)
	{
		pTentativeObj->Init(pos + GetGrid() / 2, move, size);
	}
	return pTentativeObj;
}
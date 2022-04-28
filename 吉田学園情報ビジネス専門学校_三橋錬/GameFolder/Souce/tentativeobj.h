//=============================================================================
//
// ���I�u�W�F�N�g [tentativeobj.h]
// Author : �O���B
//
//=============================================================================
#ifndef _TENTATIVEOBJ_H_
#define _TENTATIVEOBJ_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "scene2D.h"
#include "Stageload.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CTentativeObj : public CScene2D, public CStageLoad
{
public:
	CTentativeObj(CScene::PRIORITY nPriority = PRIORITY_NONE);
	~CTentativeObj();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size);
	void Uninit();

	static CTentativeObj *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size);

private:
	int m_nType;	// �ݒu���Ă���I�u�W�F�N�g�̃^�C�v
};

#endif
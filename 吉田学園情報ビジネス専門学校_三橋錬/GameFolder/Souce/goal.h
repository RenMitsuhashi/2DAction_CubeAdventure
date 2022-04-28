//=============================================================================
//
// �S�[�� [goal.h]
// Author : �O���B
//
//=============================================================================
#ifndef _GOAL_H_
#define _GOAL_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "scene2D.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CGoal : public CScene2D
{
public:
	CGoal(CScene::PRIORITY nPriority = PRIORITY_GOAL);
	~CGoal();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, LPDIRECT3DTEXTURE9 tex);
	void Uninit();
	void Update();
	void Draw();

	static CGoal *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, LPDIRECT3DTEXTURE9 tex);

private:
	int m_nTime;	// �e�N�X�`�����W�X�V�܂ł̃t���[����
	int m_nTexNum;	// ���݂̃e�N�X�`��X���W
	const int m_nTimeMax = 4;	// �e�N�X�`�����W�X�V�܂ł̃t���[����
	const int m_nTexMax = 4;	// �e�N�X�`���̕�����
};

#endif
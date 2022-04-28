//=============================================================================
//
// �J�[�\�� [cursor.h]
// Author : �O���B
//
//=============================================================================
#ifndef _CURSOR_H_
#define _CURSOR_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "scene2D.h"
#include "Stageload.h"
#include "targetcursor.h"

class CUIBg;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CCursor : public CScene2D, public CStageLoad
{
public:
	CCursor(CScene::PRIORITY nPriority = PRIORITY_CURSOR);
	~CCursor();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, LPDIRECT3DTEXTURE9 tex);
	void Uninit();
	void Update();
	void Draw();
	void DrawObjInfo();

	static CCursor *Create(D3DXVECTOR3 move, D3DXVECTOR3 size, LPDIRECT3DTEXTURE9 tex);

	D3DXVECTOR3 GetTargetPos() { return TargetPos; }
	int GetStopTime() { return m_stoptime; }

	int GetType() { return m_nType; }

private:
	int	m_nType;					// �ݒu����I�u�W�F�N�g�̃^�C�v
	D3DXVECTOR3 TargetPos;			// �ݒu����I�u�W�F�N�g�̈ړ��ڕW�n�_

	float m_move;					// �ݒu����I�u�W�F�N�g��1f������̈ړ���
	const float m_moveMax = 10.0f;	// ���̍ő�l(10.0f)

	int m_stoptime;					// �ݒu����I�u�W�F�N�g�̐Î~����
	const int m_stopMax = 180;		// ���̍ő�l(3�b)

	int	m_nColisionType;			// �G��Ă���I�u�W�F�N�g�̃^�C�v
	float m_Colisionmove;			// �G��Ă���I�u�W�F�N�g��1f������̈ړ���
	int m_Colisionstoptime;			// �G��Ă���I�u�W�F�N�g�̐Î~����
	D3DCOLORVALUE m_Colisioncol;	// �G��Ă���I�u�W�F�N�g�̐F

	int m_nSpinyDirection = 0;		// ���̕���

	int m_nNowSave = 0;				// �Z�[�u�������f

	static CTargetCursor *m_pTargetCursor;
	D3DCOLORVALUE m_col;			// �u���b�N�̐F
};

#endif
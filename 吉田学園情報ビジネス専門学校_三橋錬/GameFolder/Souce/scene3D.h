//=============================================================================
//
// �V�[��3D���� [scene3D.h]
// Author : �O���B
//
//=============================================================================
#ifndef _SCENE3D_H_
#define _SCENE3D_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)	//���_�t�H�[�}�b�g

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
struct VERTEX_3D
{
	D3DXVECTOR3 pos;	// ���_���W
	D3DXVECTOR3 nor;	// �@���x�N�g��
	D3DCOLOR col;		// ���_�J���[
	D3DXVECTOR2 tex;	// �e�N�X�`�����W
};

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CScene3D : public CScene
{
public:
	CScene3D(PRIORITY nPriority = PRIORITY_NONE);
	~CScene3D();

	HRESULT Init(LPDIRECT3DTEXTURE9 tex);
	void Uninit();
	void Update();
	void Draw();

	HRESULT Load(const char *aModelName);

	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);	// �e�N�X�`�����蓖��

	D3DXMATRIX GetMatrix() const			{ return m_mtxWorld; }
	void SetMatrix(const D3DXMATRIX& mtx)	{ m_mtxWorld = mtx; }

	D3DXVECTOR3 GetRot() const				{ return m_rot; }
	void SetRot(const D3DXVECTOR3& rot)		{ m_rot = rot; }
	void SetRotOld(const D3DXVECTOR3& rot)	{ m_rotold = rot; }

private:
	D3DXVECTOR3			m_pos;					// �|���S���̈ʒu
	D3DXVECTOR3			m_rot;					// ����
	D3DXVECTOR3			m_rotold;				// ����

	D3DXMATRIX			m_mtxWorld;				// ���[���h�}�g���b�N�X
	LPD3DXMESH			m_pMesh;				// ���b�V��(���_���)�ւ̃|�C���^
	LPD3DXBUFFER		m_pBuffMat;				// �}�e���A���i�ގ����j�ւ̃|�C���^
	DWORD				m_nNumMat;				// �}�e���A���̐�
	LPDIRECT3DTEXTURE9	m_aTexture[4] = {};		// �e�N�X�`��
};

#endif
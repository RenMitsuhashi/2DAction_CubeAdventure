//=============================================================================
//
// �V�[��2D���� [scene2D.h]
// Author : �O���B
//
//=============================================================================
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)	// ���_�t�H�[�}�b�g

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
struct VERTEX_2D
{
	D3DXVECTOR3 pos;	// ���_���W
	float rhw;			// 1.0f�Œ�
	D3DCOLOR col;		// ���_�J���[
	D3DXVECTOR2 tex;	// �e�N�X�`�����W
};

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CScene2D : public CScene
{
public:
	enum Direction
	{
		DIRECTION_NONE,
		DIRECTION_UP,
		DIRECTION_LEFT,
		DIRECTION_DOWN,
		DIRECTION_RIGHT,
		DIRECTION_MAX
	};

	CScene2D(PRIORITY nPriority = PRIORITY_NONE);
	virtual ~CScene2D();

	virtual HRESULT Init(LPDIRECT3DTEXTURE9 tex);
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();

	HRESULT Load(const char *aTextureName);

	void SetPositionDefault(D3DXVECTOR3 pos, D3DXVECTOR3 size);		// �ʒu�X�V
	void SetPositionCenter(D3DXVECTOR3 pos, D3DXVECTOR3 size);		// �ʒu�X�V

	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);					// �e�N�X�`�����蓖��

	void SetTexture(int ptnAnim, D3DXVECTOR2 split);				// �e�N�X�`������
	void ScrollTexture(D3DXVECTOR3 move);							// �e�N�X�`���X�N���[��

	void SetColor(D3DCOLORVALUE col);

	void ColisionBlock();

	CScene *CoverBlock(CScene2D *scene);
	CScene *CoverMoveBlock(CScene2D *scene);

	void PlayerReCreate();

private:
	D3DXVECTOR3	m_pos;		// �|���S���̈ʒu
	D3DXVECTOR3	m_move;		// �|���S���̈ړ���
	D3DXVECTOR3	m_size;		// �|���S���̃T�C�Y

	bool Colision(CScene *sceneA, CScene *sceneB);

protected:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9		m_pTexture = NULL;		// �e�N�X�`���ւ̃|�C���^
};

#endif
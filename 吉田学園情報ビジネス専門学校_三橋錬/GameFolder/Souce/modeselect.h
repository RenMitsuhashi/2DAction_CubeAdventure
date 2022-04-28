//=============================================================================
//
// �J�[�\�� [modeselect.h]
// Author : �O���B
//
//=============================================================================
#ifndef _MODESELECT_H_
#define _MODESELECT_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "scene2D.h"
#include "title.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CModeSelect : public CScene2D
{
public:
	CModeSelect(CScene::PRIORITY nPriority = PRIORITY_CURSOR);
	~CModeSelect();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, LPDIRECT3DTEXTURE9 tex);
	void Uninit();
	void Update();
	void Draw();

	static CModeSelect *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, LPDIRECT3DTEXTURE9 tex);

private:
	int m_nSelect;	// ����I��ł��邩
};

#endif
//=============================================================================
//
// �|���S�� [uibg.h]
// Author : �O���B
//
//=============================================================================
#ifndef _UIBG_H_
#define _UIBG_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "bg.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CUIBg : public CBg
{
public:
	CUIBg(CScene::PRIORITY nPriority = CScene::PRIORITY_UIBG);
	~CUIBg();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, LPDIRECT3DTEXTURE9 tex);
	void Uninit();
	void Update();
	void Draw();

	static CUIBg *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, LPDIRECT3DTEXTURE9 tex);

private:

};

#endif
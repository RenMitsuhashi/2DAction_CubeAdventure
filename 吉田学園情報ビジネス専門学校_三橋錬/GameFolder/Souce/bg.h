//=============================================================================
//
// �w�i [bg.h]
// Author : �O���B
//
//=============================================================================
#ifndef _BG_H_
#define _BG_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "scene2D.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CBg : virtual public CScene2D
{
public:
	CBg(CScene::PRIORITY nPriority = CScene::PRIORITY_BG);
	~CBg();

	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 speed, D3DXVECTOR3 size, LPDIRECT3DTEXTURE9 tex) = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

private:
};

#endif
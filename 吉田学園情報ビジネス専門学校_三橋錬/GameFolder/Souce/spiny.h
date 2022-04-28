//=============================================================================
//
// �Ƃ� [spiny.h]
// Author : �O���B
//
//=============================================================================
#ifndef _SPINY_H_
#define _SPINY_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "scene2D.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CSpiny : public CScene2D
{
public:
	CSpiny(CScene::PRIORITY nPriority = PRIORITY_SPINY);
	~CSpiny();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, int ptn, LPDIRECT3DTEXTURE9 tex);
	void Uninit();
	void Update();
	void Draw();

	static CSpiny *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, int ptn, LPDIRECT3DTEXTURE9 tex);

private:

};

#endif
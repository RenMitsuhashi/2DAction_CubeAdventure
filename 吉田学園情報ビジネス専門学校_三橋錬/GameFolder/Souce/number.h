//=============================================================================
//
// ���� [number.h]
// Author : �O���B
//
//=============================================================================
#ifndef _NUMBER_H_
#define _NUMBER_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "scene2D.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CNumber : public CScene2D
{
public:
	CNumber(CScene::PRIORITY nPriority = CScene::PRIORITY_UI);
	~CNumber();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, LPDIRECT3DTEXTURE9 tex);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CNumber *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, LPDIRECT3DTEXTURE9 tex);

private:

};

#endif
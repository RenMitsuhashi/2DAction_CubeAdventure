//=============================================================================
//
// �|���S�� [screenbg.h]
// Author : �O���B
//
//=============================================================================
#ifndef _SCREENBG_H_
#define _SCREENBG_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "bg.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CScreenBg : public CBg
{
public:
	CScreenBg(CScene::PRIORITY nPriority = CScene::PRIORITY_BG);
	~CScreenBg();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, LPDIRECT3DTEXTURE9 tex);
	void Uninit();
	void Update();
	void Draw();

	static CScreenBg *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, LPDIRECT3DTEXTURE9 tex);

private:

};

#endif
//=============================================================================
//
// �G�t�F�N�g [effect.h]
// Author : �O���B
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "Scene2D.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CEffect : public CScene2D
{
public:
	CEffect(CScene::PRIORITY nPriority = PRIORITY_EFFECT);
	~CEffect();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DCOLORVALUE color, D3DCOLORVALUE mincolor, D3DXVECTOR3 size, D3DXVECTOR3 minsize, int life, LPDIRECT3DTEXTURE9 tex);
	void Uninit();
	void Update();
	void Draw();

	static CEffect *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DCOLORVALUE color, D3DCOLORVALUE mincolor, D3DXVECTOR3 size, D3DXVECTOR3 minsize, int life, LPDIRECT3DTEXTURE9 tex);

protected:
	int m_nLife;

private:
	D3DCOLORVALUE m_Color;		// �J���[�l
	D3DCOLORVALUE m_MinColor;	// ���炷�J���[�l
	D3DXVECTOR3 m_MinSize;		// ���炷�T�C�Y�l
};

#endif

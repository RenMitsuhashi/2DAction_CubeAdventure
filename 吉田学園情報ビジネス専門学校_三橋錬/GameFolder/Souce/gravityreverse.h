//=============================================================================
//
// �d�͔��] [gravityreverse.h]
// Author : �O���B
//
//=============================================================================
#ifndef _GRAVITYREVERSE_H_
#define _GRAVITYREVERSE_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "scene2D.h"

class CObjectBg;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CGravityReverse : public CScene2D
{
public:
	CGravityReverse(CScene::PRIORITY nPriority = PRIORITY_REVERSE);
	~CGravityReverse();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, LPDIRECT3DTEXTURE9 tex);
	void Uninit();
	void Update();
	void Draw();

	static CGravityReverse *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, LPDIRECT3DTEXTURE9 tex);

	CObjectBg *GetBg() { return m_pBg; }

private:
	bool m_bUseCool;			// �N�[���^�C������
	int m_nTime;				// �ēx�g�p�\�ɂȂ�܂ł̃t���[����
	const int m_nTimeMax = 255;	// �ēx�g�p�\�ɂȂ�܂ł̃t���[����

	CObjectBg *m_pBg = NULL;
};

#endif
//=============================================================================
//
// ���C�g���� [light.h]
// Author : �O���B
//
//=============================================================================
#ifndef _LIGHT_H_
#define _LIGHT_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"

#define MAX_LIGHT (2)
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CLight
{
public:
	CLight();
	~CLight();

	HRESULT Init();
	void Uninit();
	void Update();

	static CLight *Create(D3DXVECTOR3 pos, D3DXCOLOR col, D3DXVECTOR3 vec, int nCnt);

private:
	void Set(D3DXVECTOR3 pos, D3DXCOLOR col, D3DXVECTOR3 vec, int nCnt);

	D3DLIGHT9 m_light[MAX_LIGHT];
};

#endif
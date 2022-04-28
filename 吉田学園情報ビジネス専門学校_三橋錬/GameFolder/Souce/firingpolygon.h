//=============================================================================
//
// �e���˃|���S�� [firingpolygon.h]
// Author : �O���B
//
//=============================================================================
#ifndef _FIRINGPOLYGON_H_
#define _FIRINGPOLYGON_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "scene.h"
#include "scene2D.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CFiringPolygon : public CScene2D
{
public:
	CFiringPolygon(CScene::PRIORITY nPriority = PRIORITY_UI);
	~CFiringPolygon();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CFiringPolygon *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size);
	static HRESULT Load();
	static void Unload();

private:
	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size);

	static LPDIRECT3DTEXTURE9		m_pTexture;		// �e�N�X�`���ւ̃|�C���^
	int								nTime;			// �O�ՃN�[���^�C��
	const int						nTimeMax = 16;	// �O�ՃN�[���^�C���̏���l
};

#endif
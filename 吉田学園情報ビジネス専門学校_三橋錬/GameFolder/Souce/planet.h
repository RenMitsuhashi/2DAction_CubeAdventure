//=============================================================================
//
// �w�i�̘f�� [planet.h]
// Author : �O���B
//
//=============================================================================
#ifndef _PLANET_H_
#define _PLANET_H_


//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "scene3D.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CPlanet : public CScene3D
{
public:
	CPlanet(CScene::PRIORITY nPriority = CScene::PRIORITY_BG);
	~CPlanet();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, LPDIRECT3DTEXTURE9 tex);
	void Uninit();
	void Update();
	void Draw();

	static CPlanet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, LPDIRECT3DTEXTURE9 tex);

private:
};

#endif
//=============================================================================
//
// 背景の惑星 [planet.h]
// Author : 三橋錬
//
//=============================================================================
#ifndef _PLANET_H_
#define _PLANET_H_


//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "scene3D.h"

//*****************************************************************************
// クラス定義
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
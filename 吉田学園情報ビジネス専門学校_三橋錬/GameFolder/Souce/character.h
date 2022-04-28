//=============================================================================
//
// キャラクター [character.h]
// Author : 三橋錬
//
//=============================================================================
#ifndef _CHARACTER_H_
#define _CHARACTER_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "scene2D.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CCharacter : virtual public CScene2D
{
public:
	CCharacter(CScene::PRIORITY nPriority = PRIORITY_NONE);
	~CCharacter();

	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, LPDIRECT3DTEXTURE9 tex) = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	
private:

};

#endif
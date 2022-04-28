//=============================================================================
//
// ゲームの背景 [gamebg.h]
// Author : 三橋錬
//
//=============================================================================
#ifndef _GAMEBG_H_
#define _GAMEBG_H_

#define EFFECT_MAX (256)

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CEffect;
class CObjectBg;

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "bg.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CGameBg : public CBg
{
public:
	enum TUTORIAL_UI
	{
		UI_WASD = 0,
		UI_JUMP,
		UI_GRAVITY_REVERSE,
		UI_GRAVITY_UP_DOWN,
		UI_GOAL,
		UI_MAX
	};

	CGameBg(CScene::PRIORITY nPriority = CScene::PRIORITY_BG);
	~CGameBg();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, LPDIRECT3DTEXTURE9 tex);
	void Uninit();
	void Update();
	void Draw();

	static CGameBg *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, LPDIRECT3DTEXTURE9 tex);

	static void *GetObjectBg(int num) { return m_pObjectBg[num]; }

private:
	static CEffect *m_pEffect[EFFECT_MAX];
	const float m_fEffectBaseSpeed = 1.0f;
	const int m_nEffectSpawnTime = 32;
	int m_nTime;

	static CObjectBg *m_pObjectBg[UI_MAX];
	static float m_fTargetPosY[UI_MAX];
};

#endif
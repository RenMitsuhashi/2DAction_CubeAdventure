//=============================================================================
//
// フェード [fade.h]
// Author : 三橋錬
//
//=============================================================================
#ifndef _FADE_H_
#define _FADE_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "scene2D.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CFade : public CScene2D
{
public:
	enum FADE
	{
		FADE_NONE = 0,
		FADE_IN,
		FADE_OUT,
		FADE_MAX
	};

	CFade::CFade(CScene::PRIORITY nPriority = PRIORITY_FADE);
	CFade::~CFade();

	HRESULT Init(CManager::MODE modeNext, LPDIRECT3DTEXTURE9 tex);
	void Uninit();
	void Update();
	void Draw();

	static CFade *Create(CManager::MODE modeNext, LPDIRECT3DTEXTURE9 tex);

	void SetFade(CManager::MODE mode, int speed)
	{
		if (m_fade == FADE_NONE)
		{
			m_fadeSpeed = speed;
			m_modeNext = mode;
			m_fade = FADE_OUT;
		}
	}

	static FADE GetFade(void) { return m_fade; }

private:
	int					m_fadeSpeed;	// フェードの速さ
	static FADE			m_fade;			// フェードの状態
	CManager::MODE		m_modeNext;		// 次の画面
	float				m_Alphafade;	// 透明度
};

#endif
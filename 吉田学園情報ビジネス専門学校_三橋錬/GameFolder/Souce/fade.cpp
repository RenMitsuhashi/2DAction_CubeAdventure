//=============================================================================
//
// フェード [fade.cpp]
// Author : 三橋錬
//
//=============================================================================
#include "main.h"
#include "fade.h"
#include "manager.h"
#include "renderer.h"
#include "sound.h"
#include "stageload.h"

CFade::FADE CFade::m_fade = FADE_NONE;

CFade::CFade(CScene::PRIORITY nPriority) : CScene2D(nPriority)
{

}

CFade::~CFade()
{

}

HRESULT CFade::Init(CManager::MODE modeNext, LPDIRECT3DTEXTURE9 tex)
{
	SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f));
	SetSize(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));
	m_modeNext = modeNext;
	m_Alphafade = 0.0f;

	CScene2D::Init(tex);

	return S_OK;
}

void CFade::Uninit(void)
{
	CScene2D::Uninit();
}

void CFade::Update(void)
{
	if (m_fade != FADE_NONE)
	{
		if (m_fade == FADE_IN)
		{
			m_Alphafade -= m_fadeSpeed;

			if (m_Alphafade <= 0.0f)
			{
				m_Alphafade = 0.0f;
				m_fade = FADE_NONE;
			}
		}

		else if (m_fade == FADE_OUT)
		{
			m_Alphafade += m_fadeSpeed;

			if (m_Alphafade >= 255.0f)
			{
				CManager::GetSound()->Stop();

				m_Alphafade = 255.0f;
				m_fade = FADE_IN;
				CManager::SetMode(m_modeNext);
			}
		}
	}

	float fadecolor = 0.0f;

	if (m_modeNext == CManager::MODE_RESULT)
	{
		fadecolor = 255.0f;
	}

	D3DCOLORVALUE col;
	col.r = fadecolor;
	col.g = fadecolor;
	col.b = fadecolor;
	col.a = m_Alphafade;

	SetPositionCenter(GetPos(), GetSize());
	SetColor(col);
}

void CFade::Draw(void)
{
	CScene2D::Draw();
}

CFade *CFade::Create(CManager::MODE modeNext, LPDIRECT3DTEXTURE9 tex)
{
	CFade* pFade = new CFade;

	if (pFade != NULL)
	{
		pFade->Init(modeNext, tex);
	}
	return pFade;
}
//=============================================================================
//
// �t�F�[�h [fade.h]
// Author : �O���B
//
//=============================================================================
#ifndef _FADE_H_
#define _FADE_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "scene2D.h"

//*****************************************************************************
// �N���X��`
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
	int					m_fadeSpeed;	// �t�F�[�h�̑���
	static FADE			m_fade;			// �t�F�[�h�̏��
	CManager::MODE		m_modeNext;		// ���̉��
	float				m_Alphafade;	// �����x
};

#endif
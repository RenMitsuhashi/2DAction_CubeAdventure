//=============================================================================
//
// �Q�[���V�[�� [game.h]
// Author : �O���B
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CGravity;
class CLight;
class CPlanet;
class CGameBg;

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "manager.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CGame : public CManager
{
public:
	CGame();
	~CGame();

	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CLight				*GetLight()		{ return m_pLight; }
	static CPlanet				*GetPlanet()	{ return m_pPlanet; }
	static CGameBg				*GetGameBg()	{ return m_pGameBg; }

private:
	static CLight				*m_pLight;		// ���C�g�̃N���X
	static CPlanet				*m_pPlanet;		// �f���̃N���X
	static CGameBg				*m_pGameBg;		// �w�i�̃N���X
};

#endif
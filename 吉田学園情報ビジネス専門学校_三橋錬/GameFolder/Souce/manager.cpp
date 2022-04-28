//=============================================================================
//
// �}�l�[�W�� [manager.cpp]
// Author : �O���B
//
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "keyboard.h"
#include "mouse.h"
#include "gamepad.h"
#include "fade.h"
#include "sound.h"
#include "data.h"
#include "texture.h"

#include "title.h"
#include "game.h"
#include "stagebuild.h"
#include "result.h"

CRenderer		*CManager::m_pRenderer		= NULL;
CKeyboard		*CManager::m_pKeyboard		= NULL;
CMouse			*CManager::m_pMouse			= NULL;
CGamePad		*CManager::m_pGamepad		= NULL;

CTitle			*CManager::m_pTitle			= NULL;
CGame			*CManager::m_pGame			= NULL;
CStageBuild		*CManager::m_pStageBuild	= NULL;
CResult			*CManager::m_pResult		= NULL;

CData			*CManager::m_pData			= NULL;
CFade			*CManager::m_pFade			= NULL;
CSound			*CManager::m_pSound			= NULL;
CTexture		*CManager::m_pTexture		= NULL;

CManager::MODE	CManager::m_mode = CManager::MODE_TITLE;


//=============================================================================
// �R���X�g���N�^
//=============================================================================
CManager::CManager()
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CManager::~CManager()
{

}

HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	// �L�[�{�[�h�N���X
	m_pKeyboard = new CKeyboard;
	m_pKeyboard->Init(hInstance, hWnd);

	// �}�E�X�N���X
	m_pMouse = new CMouse;
	m_pMouse->Init(hInstance, hWnd);

	// �Q�[���p�b�h�N���X
	m_pGamepad = new CGamePad;
	m_pGamepad->Init(hInstance, hWnd);

	m_pRenderer = new CRenderer;
	m_pRenderer->Init(hWnd, bWindow);

	m_pSound = new CSound;
	m_pSound->Init(hWnd);

	m_pTexture = new CTexture;
	m_pTexture->Init();

	m_pData = new CData;

	m_pFade = new CFade;
	m_pFade->Init(m_mode, CTexture::GetTexture(CTexture::Tex_Fade));
	SetMode(m_mode);

	return S_OK;
}

void CManager::Uninit()
{
	CScene::ReleaseAll();

	//�����_���[��Uninit
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();

		delete m_pRenderer;
		m_pRenderer = NULL;
	}
	
	// �L�[�{�[�h��Uninit
	if (m_pKeyboard != NULL)
	{
		m_pKeyboard->Uninit();

		delete m_pKeyboard;
		m_pKeyboard = NULL;
	}

	// �}�E�X��Uninit
	if (m_pMouse != NULL)
	{
		m_pMouse->Uninit();

		delete m_pMouse;
		m_pMouse = NULL;
	}

	// �Q�[���p�b�h��Uninit
	if (m_pGamepad != NULL)
	{
		m_pGamepad->Uninit();

		delete m_pGamepad;
		m_pGamepad = NULL;
	}

	//�T�E���h�N���X��Uninit
	if (m_pSound != NULL)
	{
		m_pSound->Uninit();

		delete m_pSound;
		m_pSound = NULL;
	}

	// �f�[�^��Uninit
	if (m_pData != NULL)
	{
		delete m_pData;
		m_pData = NULL;
	}

	// �t�F�[�h��Uninit
	if (m_pFade != NULL)
	{
		delete m_pFade;
		m_pFade = NULL;
	}

	// �e�N�X�`����Uninit
	if (m_pTexture != NULL)
	{
		m_pTexture->Uninit();

		delete m_pTexture;
		m_pTexture = NULL;
	}
}

void CManager::Update()
{
	if (m_pKeyboard != NULL)
	{
		m_pKeyboard->Update();
	}

	if (m_pMouse != NULL)
	{
		m_pMouse->Update();
	}

	if (m_pGamepad != NULL)
	{
		m_pGamepad->Update();
	}

	//�����_���[��Update
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Update();
	}
}

void CManager::Draw()
{
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Draw();
	}
}

void CManager::SetMode(MODE mode)
{
	CScene::ReleaseAll();

	//*****************************************************************************
	// ���܂ł̃V�[����Uninit
	//*****************************************************************************
	switch (m_mode)
	{
	case MODE_TITLE:
		m_pTitle->Uninit();
		m_pTitle = NULL;

		break;

	case MODE_BUILD:
		m_pStageBuild->Uninit();
		m_pStageBuild = NULL;

		break;

	case MODE_GAME:
		m_pGame->Uninit();
		m_pGame = NULL;

		break;

	case MODE_RESULT:
		m_pResult->Uninit();
		m_pResult = NULL;

		break;

	default:
		break;
	}

	//*****************************************************************************
	// �g���V�[����Init
	//*****************************************************************************
	CData::DataReset();

	CManager::GetSound()->Stop();

	switch (mode)
	{
	case MODE_TITLE:
		CData::SetNextStage(CData::Stage_Tutorial);
		m_pTitle->Init();
		break;

	case MODE_BUILD:
		m_pStageBuild->Init();
		break;

	case MODE_GAME:
		m_pGame->Init();
		break;

	case MODE_RESULT:
		m_pResult->Init();
		break;

	default:
		break;
	}

	m_mode = mode;
	CData::SetNowScene(mode);
}

CGamePad *CManager::GetGamepad()
{
	if (m_pGamepad->GetGamePad())
	{
		return m_pGamepad;
	}

	else
	{
		return NULL;
	}
}
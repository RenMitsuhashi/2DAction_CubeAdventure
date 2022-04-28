//=============================================================================
//
// �e�N�X�`�� [texture.cpp]
// Author : �O���B
//
//=============================================================================
#include "texture.h"
#include "manager.h"
#include "renderer.h"

LPDIRECT3DTEXTURE9	CTexture::m_pTexture[] = {};

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CTexture::CTexture()
{

}

//=============================================================================
// �f�t�H���g�f�X�g���N�^
//=============================================================================
CTexture::~CTexture()
{

}

//=============================================================================
// �e�N�X�`���̐���
//=============================================================================
void CTexture::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// ����
	D3DXCreateTextureFromFile(pDevice,
		"data\\texture\\white.png",
		&m_pTexture[Tex_None]);

	// ���e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\texture\\����.png",
		&m_pTexture[Tex_Test]);

	// �t�F�[�h�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\texture\\white.png",
		&m_pTexture[Tex_Fade]);

	// �����e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\texture\\number.png",
		&m_pTexture[Tex_Number]);

	// �ۂ��G�t�F�N�g�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\texture\\effect000.png",
		&m_pTexture[Tex_Effect]);

	// �w�i�e�N�X�`���^�C�g���p�̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\texture\\title\\bg.png",
		&m_pTexture[Tex_BgTitle]);

	// ���S�̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\texture\\title\\logo.png",
		&m_pTexture[Tex_TitleLogo]);

	// �Q�[���V�[���J�ڗp�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\texture\\title\\game.png",
		&m_pTexture[Tex_TitleUIGame]);

	// �r���_�[�V�[���J�ڗp�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\texture\\title\\build.png",
		&m_pTexture[Tex_TitleUIBuild]);

	// �Q�[���I���p�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\texture\\title\\quit.png",
		&m_pTexture[Tex_TitleUIQuit]);

	// �V�[���I��p�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\texture\\title\\arrow.png",
		&m_pTexture[Tex_TitleModeSelect]);

	// �w�i�e�N�X�`���Q�[���p�̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\texture\\black.png",
		&m_pTexture[Tex_BgGame]);

	// �w�i�e�N�X�`���Q�[���p�̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\texture\\game\\bg\\tutorial_wasd.png",
		&m_pTexture[Tex_Tutorialwasd]);

	// �`���[�g���A���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\texture\\game\\bg\\tutorial_jump.png",
		&m_pTexture[Tex_Tutorialjump]);

	// �`���[�g���A���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\texture\\game\\bg\\tutorial_gravity.png",
		&m_pTexture[Tex_TutorialGravityReverse]);

	// �`���[�g���A���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\texture\\game\\bg\\tutorial_gravityupdown.png",
		&m_pTexture[Tex_TutorialGravityUpDown]);

	// �`���[�g���A���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\texture\\game\\bg\\tutorial_goal.png",
		&m_pTexture[Tex_TutorialGoal]);

	// ���S�̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\texture\\game\\bg\\stageclear.png",
		&m_pTexture[Tex_GoalLogo]);

	// ���S�̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\texture\\game\\bg\\time.png",
		&m_pTexture[Tex_Time]);

	// ���S�̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\texture\\game\\bg\\death.png",
		&m_pTexture[Tex_Death]);

	// ���S�̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\texture\\game\\bg\\pressenter.png",
		&m_pTexture[Tex_PressEnter]);

	// ���S�̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\texture\\game\\bg\\pause_resume.png",
		&m_pTexture[Tex_Pause_Resume]);

	// ���S�̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\texture\\game\\bg\\pause_save.png",
		&m_pTexture[Tex_Pause_Save]);

	// ���S�̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\texture\\game\\bg\\pause_title.png",
		&m_pTexture[Tex_Pause_Title]);

	// ���S�̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\texture\\game\\bg\\pause_cursor.png",
		&m_pTexture[Tex_Pause_Cursor]);

	// �w�i�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\texture\\game\\object\\gravity_bg.png",
		&m_pTexture[Tex_BgGravity]);

	// �d�͔��]�̔w�i�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\texture\\game\\object\\gravityreversebg.png",
		&m_pTexture[Tex_BgReverse]);

	// �w�i�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\texture\\game\\bg\\planet.bmp",
		&m_pTexture[Tex_Planet]);

	// �u���b�N�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\texture\\white.png",
		&m_pTexture[Tex_NormalBlock]);

	// �v���C���[�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\texture\\game\\player.png",
		&m_pTexture[Tex_Player]);

	// �d�͔��]�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\texture\\game\\object\\gravityreversegage.png",
		&m_pTexture[Tex_Reverse]);

	// �S�[���e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\texture\\game\\object\\goal.png",
		&m_pTexture[Tex_Goal]);

	// ���e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\texture\\game\\object\\spiny.png",
		&m_pTexture[Tex_Spiny]);
}

//=============================================================================
// �I��
//=============================================================================
void CTexture::Uninit(void)
{
	for (int nCntTexture = 0; nCntTexture < Tex_Max; nCntTexture++)
	{
		//�e�N�X�`���̔j��
		if (m_pTexture[nCntTexture] != NULL)
		{
			m_pTexture[nCntTexture]->Release();
			m_pTexture[nCntTexture] = NULL;
		}
	}
}
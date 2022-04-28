//=============================================================================
//
// �e�N�X�`�� [texture.h]
// Author : �O���B
//
//=============================================================================
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CTexture
{
public:
	enum TexType
	{
		Tex_None = 0,		// �e�N�X�`������
		Tex_Test,			// ���e�N�X�`��
		Tex_Fade,			// �t�F�[�h�p�e�N�X�`��
		Tex_Number,			// �����e�N�X�`��
		Tex_Effect,			// �ۂ��G�t�F�N�g�e�N�X�`��

		Tex_BgTitle,		// �^�C�g���̔w�i
		Tex_TitleLogo,
		Tex_TitleUIGame,
		Tex_TitleUIBuild,
		Tex_TitleUIQuit,
		Tex_TitleModeSelect,

		Tex_BgGame,			// �w�i�e�N�X�`���Q�[���p
		Tex_Tutorialwasd,
		Tex_Tutorialjump,
		Tex_TutorialGravityReverse,
		Tex_TutorialGravityUpDown,
		Tex_TutorialGoal,

		Tex_GoalLogo,
		Tex_Time,
		Tex_Death,
		Tex_PressEnter,

		Tex_Pause_Resume,
		Tex_Pause_Save,
		Tex_Pause_Title,
		Tex_Pause_Cursor,

		Tex_BgGravity,		// �w�i�e�N�X�`��
		Tex_BgReverse,		// �d�͔��]�̔w�i�e�N�X�`��
		Tex_Planet,			// �f��
		Tex_BgMax,			// �w�i�e�N�X�`���̍ő�

		Tex_NormalBlock,	// �u���b�N�e�N�X�`��
		Tex_Player,			// �v���C���[�e�N�X�`��

		Tex_Reverse,		// �d�͔��]�̃e�N�X�`��
		Tex_Goal,			// �S�[���̃e�N�X�`��
		Tex_Spiny,			// ���e�N�X�`��

		Tex_TargetBlock,
		Tex_ObjMax,			// �I�u�W�F�N�g�̍ő�

		Tex_Max,			// �e�N�X�`���̍ő吔
	};

	CTexture();
	~CTexture();

	void Init();	// �e�N�X�`���̐���
	void Uninit();	// �I��

	static LPDIRECT3DTEXTURE9 GetTexture(int Type) { return m_pTexture[Type]; }	// �e�N�X�`���̊��蓖��(�e�N�X�`���̎��) { return �I�񂾃e�N�X�`����Ԃ� }

private:
	static LPDIRECT3DTEXTURE9	m_pTexture[Tex_Max];	// �e�N�X�`��
};

#endif
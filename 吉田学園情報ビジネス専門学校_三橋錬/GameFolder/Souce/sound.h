//*****************************************************************************
//
// �T�E���h���� [sound.h]
// Author : �O���B
//
//*****************************************************************************
#ifndef _SOUND_H_
#define _SOUND_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CSound
{
public:
	CSound();
	~CSound();

	// �T�E���h�t�@�C��
	enum SOUND_LABEL
	{
		SOUND_LABEL_BGM_TITLE,		// BGM�^�C�g��ok
		SOUND_LABEL_BGM_BUILD,		// BGM�r���_�[ok
		SOUND_LABEL_BGM_GAME,		// BGM�Q�[��ok

		SOUND_LABEL_SE_JUMP,		// �W�����vok
		SOUND_LABEL_SE_REVERSE,		// �d�͔��]ok
		SOUND_LABEL_SE_GRAVUPDOWN,	// �d��updownok
		SOUND_LABEL_SE_DEATH,		// ��

		SOUND_LABEL_SE_GOALSHAKE,	// �S�[��ok
		SOUND_LABEL_SE_GOALLOGO,	// �e�탍�S�\��ok

		SOUND_LABEL_SE_CURSOR,		// �J�[�\��ok
		SOUND_LABEL_SE_ENTER,		// ����ok
		SOUND_LABEL_SE_PRESS,		// �^�C�g���ŃG���^�[�L�[����ok

		SOUND_LABEL_MAX
	};

	HRESULT Init(HWND hWnd);
	void Uninit(void);
	HRESULT Play(SOUND_LABEL label);
	void Stop(SOUND_LABEL label);
	void Stop(void);

	// ���ʒ���
	void ControllVoice(SOUND_LABEL label, float fVolume) { m_apSourceVoice[label]->SetVolume(fVolume); }

	// �s�b�`����
	void ControllPitch(SOUND_LABEL label, float sourceRate, float targetRate) { m_apSourceVoice[label]->SetFrequencyRatio(sourceRate / targetRate); }

private:
	// �p�����[�^�\����
	typedef struct
	{
		char *m_filename;			// �t�@�C����
		int m_nCntLoop;				// ���[�v�J�E���g
	} PARAM;

	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	IXAudio2 *m_pXAudio2 = NULL;								// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice *m_pMasteringVoice = NULL;			// �}�X�^�[�{�C�X
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX] = {};	// �\�[�X�{�C�X
	BYTE *m_apDataAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^�T�C�Y
																
	static PARAM m_aParam[SOUND_LABEL_MAX];						// �e�����f�ނ̃p�����[�^
};

#endif
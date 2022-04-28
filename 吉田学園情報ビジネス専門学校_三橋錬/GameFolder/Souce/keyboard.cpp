//=============================================================================
//
// �L�[�{�[�h���͏��� [keyboard.h]
// Author : �O���B
//
//=============================================================================
#include "keyboard.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CKeyboard::CKeyboard()
{
	m_pDevice = NULL;

	// �L�[���̃N���A
	memset(&m_aKeyState[0], 0, sizeof(m_aKeyState));
	memset(&m_aKeyStateRelease[0], 0, sizeof(m_aKeyStateRelease));
	memset(&m_aKeyStateTrigger[0], 0, sizeof(m_aKeyStateTrigger));
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CKeyboard::~CKeyboard()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	// DirectInit�I�u�W�F�N�g�̐���
	CInput::Init(hInstance);

	// ���̓f�o�C�X�̐���
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	// �������[�h��ݒ�
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
	m_pDevice->Acquire();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CKeyboard::Uninit()
{
	CInput::Uninit();
}
//=============================================================================
// �X�V����
//=============================================================================
void CKeyboard::Update()
{
	if (m_pDevice)
	{
		BYTE aKeyState[NUM_KEY_MAX];
		int nCntKey;

		// ���̓f�o�C�X����f�[�^���擾����
		if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
		{
			for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
			{
				m_aKeyStateTrigger[nCntKey] = m_aKeyState[nCntKey] ^ aKeyState[nCntKey] & aKeyState[nCntKey];
				m_aKeyStateRelease[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & m_aKeyState[nCntKey];

				m_aKeyState[nCntKey] = aKeyState[nCntKey]; // �L�[�{�[�h�̓��͏��ۑ�
			}
		}
		else
		{
			m_pDevice->Acquire();
		}
	}
}

// �����L�[�������ꂽ��
int CKeyboard::GetAnyKey() const
{
	int nCntKey;
	for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
	{
		if ((m_aKeyStateTrigger[nCntKey] & 0x80) != 0 && (m_aKeyStateRelease[nCntKey] & 0x80) == 0)
		{
			return true;
		}
	}
	return false;
}

// ����̃L�[�������ꂽ��
int CKeyboard::GetKey(int nKey) const
{
	if ((m_aKeyStateTrigger[nKey] & 0x80) != 0 && (m_aKeyStateRelease[nKey] & 0x80) == 0)
	{
		return true;
	}
	return false;
}
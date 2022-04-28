//=============================================================================
//
// ���C�g���� [light.cpp]
// Author : �O���B
//
//=============================================================================
#include "light.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CLight::CLight()
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CLight::~CLight()
{

}

//=============================================================================
// �|���S���̏���������
//=============================================================================
HRESULT CLight::Init()
{
	for (int nCnt = 0; nCnt < MAX_LIGHT; nCnt++)
	{
		LPDIRECT3DDEVICE9 pDevice;	// �f�o�C�X�̃|�C���^
		D3DXVECTOR3 vecDir;			// �ݒ�p�����x�N�g��

		pDevice = CManager::GetRenderer()->GetDevice();     // �f�o�C�X���擾����

		// ���C�g���N���A����
		ZeroMemory(&m_light[nCnt], sizeof(D3DLIGHT9));

		// ���C�g�̎�ނ�ݒ�
		m_light[nCnt].Type = D3DLIGHT_DIRECTIONAL; // �Ό�����

		// ���C�g�̈ʒu��ݒ�
		m_light[nCnt].Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// ���C�g�̊g�U��i�F�j��ݒ�
		m_light[nCnt].Diffuse = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

		// ���C�g�̕�����ݒ�
		vecDir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// ���K������
		D3DXVec3Normalize(&vecDir, &vecDir);

		// ������ݒ肷��
		m_light[nCnt].Direction = vecDir;

		// ���C�g��ݒ肷��
		pDevice->SetLight(nCnt, &m_light[nCnt]);

		// ���C�g��L���ɂ���
		pDevice->LightEnable(nCnt, TRUE);
	}

	return S_OK;
}

//=============================================================================
// �|���S���̏I������
//=============================================================================
void CLight::Uninit()
{

}

//=============================================================================
// �|���S���̍X�V����
//=============================================================================
void CLight::Update()
{
	
}

CLight *CLight::Create(D3DXVECTOR3 pos, D3DXCOLOR col, D3DXVECTOR3 vec, int nCnt)
{
	CLight *pLight = new CLight;

	if (pLight != NULL)
	{
		pLight->Init();
		pLight->Set(pos, col, vec, nCnt);
	}

	return pLight;
}

void CLight::Set(D3DXVECTOR3 pos, D3DXCOLOR col, D3DXVECTOR3 vec, int nCnt)
{
	LPDIRECT3DDEVICE9 pDevice;							// �f�o�C�X�̃|�C���^
	D3DXVECTOR3 vecDir;									// �ݒ�p�����x�N�g��

	pDevice = CManager::GetRenderer()->GetDevice();     // �f�o�C�X���擾����

														// ���C�g���N���A����
	ZeroMemory(&m_light[nCnt], sizeof(D3DLIGHT9));

	// ���C�g�̎�ނ�ݒ�
	m_light[nCnt].Type = D3DLIGHT_DIRECTIONAL;

	// ���C�g�̈ʒu��ݒ�
	m_light[nCnt].Position = pos;

	// ���C�g�̊g�U��i�F�j��ݒ�
	m_light[nCnt].Diffuse = col;

	// ���C�g�̕�����ݒ�
	vecDir = vec;

	// ���K������
	D3DXVec3Normalize(&vecDir, &vecDir);

	// ������ݒ肷��
	m_light[nCnt].Direction = vecDir;

	// ���C�g��ݒ肷��
	pDevice->SetLight(nCnt, &m_light[nCnt]);

	// ���C�g��L���ɂ���
	pDevice->LightEnable(nCnt, TRUE);
}
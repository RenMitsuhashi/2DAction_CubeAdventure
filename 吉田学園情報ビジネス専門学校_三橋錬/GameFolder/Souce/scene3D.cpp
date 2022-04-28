//=============================================================================
//
// �V�[������ [scene3D.cpp]
// Author : �O���B
//
//=============================================================================
#include "scene3d.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CScene3D::CScene3D(CScene::PRIORITY nPriority) : CScene(nPriority)
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CScene3D::~CScene3D()
{

}

//=============================================================================
// �|���S���̏���������
//=============================================================================
HRESULT CScene3D::Init(LPDIRECT3DTEXTURE9 tex)
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = CManager::GetRenderer()->GetDevice();     //�f�o�C�X���擾����

	SetPos(m_pos);
	SetPosold(m_pos);

	SetRot(m_rot);
	SetRotOld(m_rot);

	BindTexture(tex);

	return S_OK;
}

//=============================================================================
// �|���S���̏I������
//=============================================================================
void CScene3D::Uninit()
{
	//�e�N�X�`���̔j��
	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (m_pBuffMat != NULL)
	{
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}

	Release(GetPriority());
}

//=============================================================================
// �|���S���̍X�V����
//=============================================================================
void CScene3D::Update()
{
	
}

//=============================================================================
// �|���S���̕`�揈��
//=============================================================================
void CScene3D::Draw()
{
	LPDIRECT3DDEVICE9 pDevice;							// �f�o�C�X�̃|�C���^
	pDevice = CManager::GetRenderer()->GetDevice();		// �f�o�C�X���擾

	D3DXMATRIX mtxRot, mtxTrans;						// �v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;								// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;									// �}�e���A���f�[�^�ւ̃|�C���^

	// ���[���h�}�g���b�N�X������
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, GetPos().x, GetPos().y, GetPos().z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		for (int nCntTex = 0; nCntTex < (int)m_nNumMat; nCntTex++)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, m_aTexture[nCntTex]);
		}

		//���f��(�p�[�c)�̐ݒ�
		m_pMesh->DrawSubset(nCntMat);
	}

	//�ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//=============================================================================
// �e�N�X�`���̊��蓖��
//=============================================================================
void CScene3D::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		m_aTexture[nCnt] = pTexture;
	}
}

HRESULT CScene3D::Load(const char *aModelName)
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = CManager::GetRenderer()->GetDevice();     //�f�o�C�X���擾����

	D3DXLoadMeshFromX(aModelName,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_nNumMat,
		&m_pMesh);

	D3DXMATERIAL *pMat;

	//�}�e���A�����ɑ΂���|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	int nCntTex = 0;

	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCntMat].pTextureFilename,
				&m_aTexture[nCntTex]);
			nCntTex++;
		}
	}

	return S_OK;
}
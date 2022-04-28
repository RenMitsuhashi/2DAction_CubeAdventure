//=============================================================================
//
// �e���˃|���S�� [firingpolygon.cpp]
// Author : �O���B
//
//=============================================================================
#include "firingpolygon.h"
#include "manager.h"
#include "renderer.h"

#include "input.h"

#include "sound.h"
#include "mouse.h"

#include <assert.h>

LPDIRECT3DTEXTURE9	CFiringPolygon::m_pTexture = {};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CFiringPolygon::CFiringPolygon(CScene::PRIORITY nPriority) : CScene2D(nPriority)
{
	
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CFiringPolygon::~CFiringPolygon()
{

}

//=============================================================================
// �e�N�X�`���̃��[�h
//=============================================================================
HRESULT CFiringPolygon::Load()
{
	LPDIRECT3DDEVICE9 pDevice;						//�f�o�C�X�̃|�C���^
	pDevice = CManager::GetRenderer()->GetDevice();	//�f�o�C�X���擾

	D3DXCreateTextureFromFile(
		pDevice,
		"",
		&m_pTexture);

	return S_OK;
}

//=============================================================================
// �e�N�X�`���̔j��
//=============================================================================
void CFiringPolygon::Unload()
{
	//�e�N�X�`���j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// �|���S���̏���������
//=============================================================================
HRESULT CFiringPolygon::Init(void)
{
	CScene2D::Init();
	SetObjType(CScene::TYPE_NULL);

	return S_OK;
}

//=============================================================================
// �|���S���̏I������
//=============================================================================
void CFiringPolygon::Uninit(void)
{
	Release();
}

//=============================================================================
// �|���S���̍X�V����
//=============================================================================
void CFiringPolygon::Update(void)
{
	nTime--;

	if (nTime <= 0) { nTime = nTimeMax; }
}

//=============================================================================
// �|���S���̕`�揈��
//=============================================================================
void CFiringPolygon::Draw(void)
{
	CScene2D::Draw();
}

CFiringPolygon *CFiringPolygon::Create(D3DXVECTOR3 pos, D3DXVECTOR3 speed, D3DXVECTOR3 size)
{
	CFiringPolygon* pCursor = new CFiringPolygon;

	if (pCursor != NULL)
	{
		pCursor->Init();
		pCursor->Set(pos, speed, size);
	}
	return pCursor;
}

void CFiringPolygon::Set(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size)
{
	SetPos(pos);
	SetMove(move);
	SetSize(size);
	SetDeath(false);

	nTime = nTimeMax;

	CScene2D::BindTexture(m_pTexture);
	CScene2D::SetPositionCenter(GetPos(), GetSize());
}
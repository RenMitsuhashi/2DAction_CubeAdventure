//=============================================================================
//
// カメラ処理 [camera.cpp]
// Author : 三橋錬
//
//=============================================================================
#include "camera.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CCamera::CCamera()
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CCamera::~CCamera()
{

}

//=============================================================================
// ポリゴンの初期化処理
//=============================================================================
HRESULT CCamera::Init()
{
	LPDIRECT3DDEVICE9 pDevice;	// デバイスのポインタ
	pDevice = CManager::GetRenderer()->GetDevice();		// デバイスを取得する

	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_camera.mtxProjection);

	// プロジェクションマトリックス作成
	D3DXMatrixPerspectiveFovLH(&m_camera.mtxProjection, D3DXToRadian(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 10.0f, 25000.0f);

	// プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_camera.mtxProjection);

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_camera.mtxView);

	// ビューマトリックスの作成
	D3DXMatrixLookAtLH(&m_camera.mtxView, &m_camera.posV, &m_camera.posR, &m_camera.vecU);

	// ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_camera.mtxView);

	return S_OK;
}

//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CCamera::Uninit()
{

}

//=============================================================================
// ポリゴンの更新処理
//=============================================================================
void CCamera::Update()
{
	LPDIRECT3DDEVICE9 pDevice; //デバイスのポインタ
	pDevice = CManager::GetRenderer()->GetDevice();     //デバイスを取得する

	// カメラの制限(一周回ったら)
	if (m_camera.rot.y >= D3DX_PI)
	{
		m_camera.rot.y -= D3DX_PI * 2;
	}

	if (m_camera.rot.y < -D3DX_PI)
	{
		m_camera.rot.y += D3DX_PI * 2;
	}

	m_camera.posV.x = m_camera.posR.x - sinf(m_camera.rot.y) * m_camera.fLength;
	m_camera.posV.y = m_camera.posR.y + m_camera.fLength * (m_camera.rot.x + (4.0f / 10.0f));
	m_camera.posV.z = m_camera.posR.z - cosf(m_camera.rot.y) * m_camera.fLength;

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_camera.mtxView);

	// ビューマトリックスの作成
	D3DXMatrixLookAtLH(&m_camera.mtxView, &m_camera.posV, &m_camera.posR, &m_camera.vecU);

	// ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_camera.mtxView);
}

CCamera *CCamera::Create(D3DXVECTOR3 ref, float fDistance, D3DXVECTOR3 pos)
{
	CCamera *pCamera = new CCamera;

	if (pCamera != NULL)
	{
		pCamera->Init();
		pCamera->Set(ref, fDistance, pos);
	}
	return pCamera;
}

void CCamera::Set(D3DXVECTOR3 ref, float fDistance, D3DXVECTOR3 pos)
{
	m_camera.posV = ref;
	m_camera.posVDest = ref;

	m_camera.posR = pos;
	m_camera.posRDest = pos;

	m_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	m_camera.rot = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

	m_camera.fLength = fDistance;	// 多分距離
}

void CCamera::SetPosV(D3DXVECTOR3 pos)
{
	m_camera.posVDest = pos;
	m_camera.posV = pos;
}

void CCamera::SetPosR(D3DXVECTOR3 pos)
{
	m_camera.posRDest = pos;
	m_camera.posR = pos;
}

void CCamera::AddRotX(float fRotX)
{
	m_camera.rot.x += fRotX;

	// カメラ高さ制限
	if (m_camera.rot.x >= 1.5f)
	{
		m_camera.rot.x = 1.5f;
	}

	else if (m_camera.rot.x <= -1.4f)
	{
		m_camera.rot.x = -1.4f;
	}
}
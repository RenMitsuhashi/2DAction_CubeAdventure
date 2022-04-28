//=============================================================================
//
// ライト処理 [light.cpp]
// Author : 三橋錬
//
//=============================================================================
#include "light.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CLight::CLight()
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CLight::~CLight()
{

}

//=============================================================================
// ポリゴンの初期化処理
//=============================================================================
HRESULT CLight::Init()
{
	for (int nCnt = 0; nCnt < MAX_LIGHT; nCnt++)
	{
		LPDIRECT3DDEVICE9 pDevice;	// デバイスのポインタ
		D3DXVECTOR3 vecDir;			// 設定用方向ベクトル

		pDevice = CManager::GetRenderer()->GetDevice();     // デバイスを取得する

		// ライトをクリアする
		ZeroMemory(&m_light[nCnt], sizeof(D3DLIGHT9));

		// ライトの種類を設定
		m_light[nCnt].Type = D3DLIGHT_DIRECTIONAL; // 偏向光源

		// ライトの位置を設定
		m_light[nCnt].Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// ライトの拡散先（色）を設定
		m_light[nCnt].Diffuse = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

		// ライトの方向を設定
		vecDir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// 正規化する
		D3DXVec3Normalize(&vecDir, &vecDir);

		// 方向を設定する
		m_light[nCnt].Direction = vecDir;

		// ライトを設定する
		pDevice->SetLight(nCnt, &m_light[nCnt]);

		// ライトを有効にする
		pDevice->LightEnable(nCnt, TRUE);
	}

	return S_OK;
}

//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CLight::Uninit()
{

}

//=============================================================================
// ポリゴンの更新処理
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
	LPDIRECT3DDEVICE9 pDevice;							// デバイスのポインタ
	D3DXVECTOR3 vecDir;									// 設定用方向ベクトル

	pDevice = CManager::GetRenderer()->GetDevice();     // デバイスを取得する

														// ライトをクリアする
	ZeroMemory(&m_light[nCnt], sizeof(D3DLIGHT9));

	// ライトの種類を設定
	m_light[nCnt].Type = D3DLIGHT_DIRECTIONAL;

	// ライトの位置を設定
	m_light[nCnt].Position = pos;

	// ライトの拡散先（色）を設定
	m_light[nCnt].Diffuse = col;

	// ライトの方向を設定
	vecDir = vec;

	// 正規化する
	D3DXVec3Normalize(&vecDir, &vecDir);

	// 方向を設定する
	m_light[nCnt].Direction = vecDir;

	// ライトを設定する
	pDevice->SetLight(nCnt, &m_light[nCnt]);

	// ライトを有効にする
	pDevice->LightEnable(nCnt, TRUE);
}
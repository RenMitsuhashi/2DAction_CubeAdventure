//=============================================================================
//
// シーン処理 [scene3D.cpp]
// Author : 三橋錬
//
//=============================================================================
#include "scene3d.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CScene3D::CScene3D(CScene::PRIORITY nPriority) : CScene(nPriority)
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CScene3D::~CScene3D()
{

}

//=============================================================================
// ポリゴンの初期化処理
//=============================================================================
HRESULT CScene3D::Init(LPDIRECT3DTEXTURE9 tex)
{
	LPDIRECT3DDEVICE9 pDevice; //デバイスのポインタ
	pDevice = CManager::GetRenderer()->GetDevice();     //デバイスを取得する

	SetPos(m_pos);
	SetPosold(m_pos);

	SetRot(m_rot);
	SetRotOld(m_rot);

	BindTexture(tex);

	return S_OK;
}

//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CScene3D::Uninit()
{
	//テクスチャの破棄
	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}
	//頂点バッファの破棄
	if (m_pBuffMat != NULL)
	{
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}

	Release(GetPriority());
}

//=============================================================================
// ポリゴンの更新処理
//=============================================================================
void CScene3D::Update()
{
	
}

//=============================================================================
// ポリゴンの描画処理
//=============================================================================
void CScene3D::Draw()
{
	LPDIRECT3DDEVICE9 pDevice;							// デバイスのポインタ
	pDevice = CManager::GetRenderer()->GetDevice();		// デバイスを取得

	D3DXMATRIX mtxRot, mtxTrans;						// 計算用マトリックス
	D3DMATERIAL9 matDef;								// 現在のマテリアル保存用
	D3DXMATERIAL *pMat;									// マテリアルデータへのポインタ

	// ワールドマトリックス初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, GetPos().x, GetPos().y, GetPos().z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		for (int nCntTex = 0; nCntTex < (int)m_nNumMat; nCntTex++)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, m_aTexture[nCntTex]);
		}

		//モデル(パーツ)の設定
		m_pMesh->DrawSubset(nCntMat);
	}

	//保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

//=============================================================================
// テクスチャの割り当て
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
	LPDIRECT3DDEVICE9 pDevice; //デバイスのポインタ
	pDevice = CManager::GetRenderer()->GetDevice();     //デバイスを取得する

	D3DXLoadMeshFromX(aModelName,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_nNumMat,
		&m_pMesh);

	D3DXMATERIAL *pMat;

	//マテリアル情報に対するポインタを取得
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
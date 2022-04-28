//=============================================================================
//
// エフェクト [effect.cpp]
// Author : 三橋錬
//
//=============================================================================
#include "effect.h"
#include "manager.h"
#include "renderer.h"
#include "data.h"

//*****************************************************************************
//コンストラクタ
//*****************************************************************************
CEffect::CEffect(CScene::PRIORITY nPriority) : CScene2D(nPriority)
{
	
}

//*****************************************************************************
//デストラクタ
//*****************************************************************************
CEffect::~CEffect()
{

}

//*****************************************************************************
//初期化
//*****************************************************************************
HRESULT CEffect::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DCOLORVALUE color, D3DCOLORVALUE mincolor, D3DXVECTOR3 size, D3DXVECTOR3 minsize, int life, LPDIRECT3DTEXTURE9 tex)
{
	SetPos(pos);
	SetMove(move);
	SetSize(size);
	SetDeath(false);

	CScene2D::Init(tex);

	m_Color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_MinColor = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

	m_Color = color;
	SetColor(color);

	m_MinColor = mincolor;
	m_MinSize = minsize;
	m_nLife = life;

	return S_OK;
}

//*****************************************************************************
//終了
//*****************************************************************************
void CEffect::Uninit()
{
	CScene2D::Uninit();
}

//*****************************************************************************
//更新
//*****************************************************************************
void CEffect::Update()
{
	SetSize(GetSize() - m_MinSize);
	m_nLife--;		// ライフ減算

	// 画面外処理
	if (GetPos().x < 0 ||
		GetPos().x > SCREEN_WIDTH ||
		GetPos().y < 0 ||
		GetPos().y > SCREEN_HEIGHT)
	{
		SetDeath(true);
	}

	// 高さか幅が0になったら
	if (GetSize().x < 0 || GetSize().y < 0)
	{
		SetDeath(true);
	}

	// 寿命が0になったら
	if (m_nLife < 0)
	{
		SetDeath(true);
	}

	// カラー変更
	m_Color.r -= m_MinColor.r;
	m_Color.g -= m_MinColor.g;
	m_Color.b -= m_MinColor.b;
	m_Color.a -= m_MinColor.a;

	// カラーが0以下の時
	if (m_Color.r < 0)
	{
		m_Color.r = 0;
	}

	if (m_Color.g < 0)
	{
		m_Color.g = 0;
	}

	if (m_Color.b < 0)
	{
		m_Color.b = 0;
	}

	if (m_Color.a < 0)
	{
		m_Color.a = 0;
	}

	// カラーが255以上の時
	if (m_Color.r > 255)
	{
		m_Color.r = 255;
	}

	if (m_Color.g > 255)
	{
		m_Color.g = 255;
	}

	if (m_Color.b > 255)
	{
		m_Color.b = 255;
	}

	if (m_Color.a > 255)
	{
		m_Color.a = 255;
	}

	SetPositionCenter(GetPos(), GetSize());
	SetColor(m_Color);
}

//*****************************************************************************
// 描画
//*****************************************************************************
void CEffect::Draw()
{
	if (CData::GetPause() &&
		CData::GetNowGame())
	{
		// 頂点情報を設定
		LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();//デバイスの取得

		//Zテスト関係
		pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
		pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

		//加算合成関係
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

		//アルファテスト関係
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
		pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

		CScene2D::Draw();

		//Zテスト関係
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

		//アルファテスト関係
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
		pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);

		//通常合成に戻す(加算合成)
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}
}

CEffect *CEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DCOLORVALUE color, D3DCOLORVALUE mincolor, D3DXVECTOR3 size, D3DXVECTOR3 minsize, int life, LPDIRECT3DTEXTURE9 tex)
{
	CEffect* pEffect = new CEffect;

	if (pEffect != NULL)
	{
		pEffect->Init(pos, move, color, mincolor, size, minsize, life, tex);
	}
	return pEffect;
}
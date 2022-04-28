//=============================================================================
//
// レンダラー処理 [renderer.h]
// Author : 三橋錬
//
//=============================================================================
#ifndef _RENDERER_H_
#define _RENDERER_H_

// 前方宣言
class CCamera;

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CRenderer
{
public:
	CRenderer();
	~CRenderer();

	HRESULT Init(HWND hWnd, bool bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	LPDIRECT3DDEVICE9 GetDevice() const { return m_pD3DDevice; }
	D3DXVECTOR3 GetMousePos() const { return GetMouse(); }

	void SetWindowMode(bool tf, HWND hWnd);

	CCamera *GetCamera() { return m_pCamera; }
	LPD3DXFONT GetFont() { return m_pFont; }
	HWND GetWnd() { return m_hWnd; }

private:
	void DrawFPS(void);

	LPDIRECT3D9				m_pD3D = NULL;			// Direct3Dオブジェクト
	LPDIRECT3DDEVICE9		m_pD3DDevice = NULL;	// Deviceオブジェクト(描画に必要)
	D3DPRESENT_PARAMETERS	d3dpp;
	D3DDISPLAYMODE			d3ddm;

	static CCamera *m_pCamera;

	LPD3DXFONT				m_pFont = NULL;			// フォントへのポインタ
	HWND					m_hWnd = NULL;
};

#endif
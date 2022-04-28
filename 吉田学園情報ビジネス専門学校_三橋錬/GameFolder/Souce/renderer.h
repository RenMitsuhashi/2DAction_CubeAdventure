//=============================================================================
//
// �����_���[���� [renderer.h]
// Author : �O���B
//
//=============================================================================
#ifndef _RENDERER_H_
#define _RENDERER_H_

// �O���錾
class CCamera;

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// �N���X��`
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

	LPDIRECT3D9				m_pD3D = NULL;			// Direct3D�I�u�W�F�N�g
	LPDIRECT3DDEVICE9		m_pD3DDevice = NULL;	// Device�I�u�W�F�N�g(�`��ɕK�v)
	D3DPRESENT_PARAMETERS	d3dpp;
	D3DDISPLAYMODE			d3ddm;

	static CCamera *m_pCamera;

	LPD3DXFONT				m_pFont = NULL;			// �t�H���g�ւ̃|�C���^
	HWND					m_hWnd = NULL;
};

#endif
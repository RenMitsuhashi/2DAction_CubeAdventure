//=============================================================================
//
// マウス入力処理 [mouse.h]
// Author : 三橋錬
//
//=============================================================================
#include "mouse.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CMouse::CMouse()
{
	m_pDevice = NULL;
}

//=============================================================================
// デストラクタ
//=============================================================================
CMouse::~CMouse()
{

}


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CMouse::Init(HINSTANCE hInstance, HWND hWnd)
{
	// DirectInitオブジェクトの生成
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void **)&m_pInput, NULL)))
	{
		return E_FAIL;
	}

	// 入力デバイスの生成
	if (FAILED(m_pInput->CreateDevice(GUID_SysMouse, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	// データフォーマットを設定
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIMouse)))
	{
		return E_FAIL;
	}

	// 協調モードを設定
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	ShowCursor(true);

	// 処理を同期させる
	m_pDevice->Poll();

	// マウスへのアクセス権を獲得(入力制御開始)
	m_pDevice->Acquire();

	m_bMouse = true;
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CMouse::Uninit()
{
	CInput::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CMouse::Update()
{
	if (m_pDevice)
	{
		DIMOUSESTATE aMouseState;
		int nCntBut;
		// 入力デバイスからデータを取得する
		if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aMouseState), &aMouseState)))
		{
			for (nCntBut = 0; nCntBut < DIM_MAX; nCntBut++)
			{
				m_MouseStateTrigger.rgbButtons[nCntBut] = m_MouseState.rgbButtons[nCntBut] ^ aMouseState.rgbButtons[nCntBut] & aMouseState.rgbButtons[nCntBut];
				m_MouseStateRelease.rgbButtons[nCntBut] = (m_MouseState.rgbButtons[nCntBut] ^ aMouseState.rgbButtons[nCntBut]) & m_MouseState.rgbButtons[nCntBut];
				m_MouseState.rgbButtons[nCntBut] = aMouseState.rgbButtons[nCntBut]; //マウスの入力情報保存
			}
			m_MouseState.lX = aMouseState.lX;
			m_MouseState.lY = aMouseState.lY;
			m_MouseState.lZ = aMouseState.lZ;
		}
		else
		{
			m_pDevice->Acquire();
		}
	}
}

int CMouse::GetPress(MouseButton Button) const
{
	return m_MouseState.rgbButtons[Button] & 0x80;
}

int CMouse::GetTrigger(MouseButton Button) const
{
	if ((m_MouseStateTrigger.rgbButtons[Button] & 0x80) != 0 &&
		(m_MouseStateRelease.rgbButtons[Button] & 0x80) == 0)
	{
		return true;
	}
	return false;
}

int CMouse::GetRelease(MouseButton Button) const
{
	if ((m_MouseStateRelease.rgbButtons[Button] & 0x80) != 0 &&
		(m_MouseStateTrigger.rgbButtons[Button] & 0x80) == 0)
	{
		return true;
	}
	return false;
}
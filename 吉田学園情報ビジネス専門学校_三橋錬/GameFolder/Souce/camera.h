//=============================================================================
//
// カメラ処理 [camera.h]
// Author : 三橋錬
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CCamera
{
public:
	//カメラの構造体
	struct Camera
	{
		D3DXVECTOR3 posV;			// 現在の視点
		D3DXVECTOR3 posVDest;		// 目的の視点

		D3DXVECTOR3 posR;			// 現在の注視点
		D3DXVECTOR3 posRDest;		// 目的の注視点

		D3DXVECTOR3 vecU;			// 上方向ベクトル

		D3DXVECTOR3 rot;			// カメラの向き

		float fLength;

		D3DXMATRIX mtxProjection;	// プロジェクションマトリックス
		D3DXMATRIX mtxView;			// ビューマトリックス
	};

	CCamera();
	~CCamera();

	HRESULT Init();
	void Uninit();
	void Update();

	void SetRot()	{ m_camera.rot.y = atan2f(m_camera.posR.x - m_camera.posV.x, m_camera.posR.z - m_camera.posV.z); }

	float GetRotY() { return m_camera.rot.y; }
	float GetRotX()	{ return m_camera.rot.x; }

	void SetPosV(D3DXVECTOR3 pos);
	void SetPosR(D3DXVECTOR3 pos);

	D3DXVECTOR3 GetPosR()		{ return m_camera.posR; }
	D3DXVECTOR3 GetPosV()		{ return m_camera.posV; }

	void AddRotY(float fRotY)	{ m_camera.rot.y += fRotY; }
	void AddRotX(float fRotX);

	void ResetRot()				{ m_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f); }

	static CCamera *Create(D3DXVECTOR3 ref, float fDistance, D3DXVECTOR3 pos);

private:
	void Set(D3DXVECTOR3 ref, float fDistance, D3DXVECTOR3 pos);

	Camera m_camera;
};

#endif
//=============================================================================
//
// �J�������� [camera.h]
// Author : �O���B
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CCamera
{
public:
	//�J�����̍\����
	struct Camera
	{
		D3DXVECTOR3 posV;			// ���݂̎��_
		D3DXVECTOR3 posVDest;		// �ړI�̎��_

		D3DXVECTOR3 posR;			// ���݂̒����_
		D3DXVECTOR3 posRDest;		// �ړI�̒����_

		D3DXVECTOR3 vecU;			// ������x�N�g��

		D3DXVECTOR3 rot;			// �J�����̌���

		float fLength;

		D3DXMATRIX mtxProjection;	// �v���W�F�N�V�����}�g���b�N�X
		D3DXMATRIX mtxView;			// �r���[�}�g���b�N�X
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